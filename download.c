/*
这个下载的思想就是利用http/https请求，将要下载的内容写入事先准备好的文件中
*/

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

//多平台适配
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define wait(x) Sleep(1000*x)
#define _getcwd() getcwd()
#else
#include <unistd.h>
#include <limit.h>
#define wait(x) Sleep(x)
#endif

// 写入回调：将接收到的数据写入文件
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    FILE *fp = (FILE *)stream;
    return fwrite(ptr, size, nmemb, fp);
}

//下载进度
int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
/*
dltotal:下载总大小
dlnow:已下载的大小
ultotal:上传总大小
ulnow:以上传的大小
*/
 {
    if (dltotal > 0) {
        printf("\r下载进度：%.2f%%", (double)dlnow / dltotal * 100);
        fflush(stdout);
    }
    return 0;
}


int main(int argc,char *argv[])//采用命令行传参的形式来下载指定的问价
{
    if(argc>3&&strcmp(argv[1],"download"))
    {
        CURL *curl;
        FILE *fp;
        CURLcode res;
        const char *url,*outfilename;
        url = argv[2];        //文件链接
        if(argv[3]!=NULL)
            outfilename = argv[3];         //输出文件名
        else
        {
            char cwd[MAX_PATH];
            outfilename=getcwd(cwd,sizeof(cwd));//如果用户没有输入地址，那么默认下载当前工作地址
            if(outfilename==NULL)
                printf("找不到路径\n");
        }

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) {
            fp = fopen(outfilename, "wb");  // 以二进制写打开文件
            if (!fp) {
                perror("文件打开失败");
                return 1;
            }

            curl_easy_setopt(curl, CURLOPT_URL, url);                     // 设置 URL
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);   // 设置写入函数
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);               // 把 FILE* 传给写入函数

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);//显示调试信息
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);//自动跟随重定向

            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);//开启显示下载进度
            curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);//设置显示下载进度


            res = curl_easy_perform(curl);                               // 执行下载
            if (res != CURLE_OK)
            {
                int retry = 3;
                while (retry-- > 0)     //失败重试
                {
                    CURLcode res = curl_easy_perform(curl);
                    if (res == CURLE_OK) break;
                    fprintf(stderr, "下载失败，重试中...\n");
                    wait(1);
                }
                printf("下载失败，请换源");
            }

            fclose(fp);
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();
        return 0;
    }
    else
    {
        printf("无效的命令");
    }
}

