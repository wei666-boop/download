#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <curl/curl.h>
/*
start:下载的起始字节
end:下载的结束字节
thread_id:线程编号
filename:暂存文件名称
*/
typedef struct{
    const char *url;
    long start;
    long end;
    int thread_id;
    char filename[256];
}ThreadData;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *fp = (FILE *)stream;
    return fwrite(ptr, size, nmemb, fp);
}

//线程函数
void *download_range(void *arg)
{
    ThreadData *data=(ThreadData*)arg;
    CURL *curl=curl_easy_init();
    if(!curl)
    {
        fprintf(stderr,"线程 %d :curl 初识化失败\n");
        pthread_exit(NULL);
    }
    FILE *fp=fopen(data->filename,"wb");
    if(!fp)
    {
        fprintf(stderr, "线程 %d: 打开文件失败: %s\n", data->thread_id, data->filename);
        curl_easy_cleanup(curl);
        pthread_exit(NULL);
    }

    char range_header[64];
    snprintf(range_header, sizeof(range_header), "%ld-%ld", data->start, data->end);

    curl_easy_setopt(curl, CURLOPT_URL, data->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_RANGE, range_header);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "线程 %d: 下载失败: %s\n", data->thread_id, curl_easy_strerror(res));
    } else {
        printf("线程 %d: 下载完成 [%s]\n", data->thread_id, range_header);
    }

    fclose(fp);
    curl_easy_cleanup(curl);
    pthread_exit(NULL);
}

//获得文件大小
long get_file_size(const char *url) {
    CURL *curl = curl_easy_init();
    double filesize = 0.0;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);       // HEAD 请求
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);
            if ((res != CURLE_OK) || (filesize < 0.0)) {
                filesize = 0;
            }
        }
        curl_easy_cleanup(curl);
    }
    return (long)filesize;
}
//合并已下载好的文件
void merge_files(const char *output_filename, int num_parts) {
    FILE *fp_out = fopen(output_filename, "wb");
    if (!fp_out) {
        perror("合并文件失败");
        return;
    }

    char buffer[8192];
    for (int i = 0; i < num_parts; i++) {
        char part_filename[256];
        snprintf(part_filename, sizeof(part_filename), "part_%d.tmp", i);
        FILE *fp_in = fopen(part_filename, "rb");
        if (!fp_in) {
            perror("打开临时文件失败");
            fclose(fp_out);
            return;
        }
        size_t n;
        while ((n = fread(buffer, 1, sizeof(buffer), fp_in)) > 0) {
            fwrite(buffer, 1, n, fp_out);
        }
        fclose(fp_in);
        remove(part_filename);
    }
    fclose(fp_out);
}

int main(int argc, char *argv[]) {
    //做用户体验优化
    if (argc != 4) {
        printf("用法: %s <url> <线程数> <输出文件>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    int num_threads = atoi(argv[2]);
    const char *output_filename = argv[3];

    if (num_threads <= 0) {
        printf("线程数必须大于0\n");
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    long filesize = get_file_size(url);
    if (filesize <= 0) {
        printf("获取文件大小失败或文件为空\n");
        return 1;
    }
    printf("文件大小: %ld 字节\n", filesize);

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    ThreadData *thread_data = malloc(sizeof(ThreadData) * num_threads);

    long part_size = filesize / num_threads;
    long start = 0;
    long end = 0;

    for (int i = 0; i < num_threads; i++) {
        start = i * part_size;
        if (i == num_threads - 1) {
            end = filesize - 1;  // 最后一个线程下载剩余所有字节
        } else {
            end = start + part_size - 1;
        }

        thread_data[i].url = url;
        thread_data[i].start = start;
        thread_data[i].end = end;
        thread_data[i].thread_id = i;
        snprintf(thread_data[i].filename, sizeof(thread_data[i].filename), "part_%d.tmp", i);

        pthread_create(&threads[i], NULL, download_range, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    merge_files(output_filename, num_threads);
    printf("文件合并完成，保存为 %s\n", output_filename);

    free(threads);
    free(thread_data);

    curl_global_cleanup();
    return 0;
}
