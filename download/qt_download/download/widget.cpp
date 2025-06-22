#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <QDebug>
#include <QFileDialog>

int thread_Flag=0;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_download_button_clicked()
{
     QString url = ui->browse_line->text();//获得下载的网址
     QString filename = ui->save_line->text();//要保存的文件地址

     QProcess *process = new QProcess(this);//建立一个进程对象,就是当前这个函数
     QString program;
     //多平台通用机制
     #ifdef Q_OS_WIN
        if(thread_Flag==0)
            program = "downloade.exe";
        else
             program= "thread_download";
     #else
        if(thread_Flag==0)
            program = "./downloade";
        else
            program ="./thread_download";
     #endif

      QStringList arguments;
      arguments<<"download"<<url<<filename;//准备命令行参数

      process->setProgram(program);//设置程序路径
      process->setArguments(arguments);//设置参数
      process->start();//启动程序

      //将调试信息打印到控制台中
      connect(process,&QProcess::readyReadStandardOutput,[=](){
          QString output=process->readAllStandardOutput();
          ui->output->append(output);
      });

      //程序结束后的清理
      connect(process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
              [=](int code,QProcess::ExitStatus status){
          ui->output->append(QString("下载完成，退出码%d").arg(code));
          process->deleteLater();
      });


}

void Widget::on_savebutton_clicked()
{
    QString filepath=QFileDialog::getSaveFileName(this,tr("选择保存路径"),QDir::homePath());
    if(!filepath.isEmpty())
    {
        ui->save_line->setText(filepath);
    }
    else
        qDebug()<<"用户取消选择"<<endl;
}


void Widget::on_thread_stateChanged(int arg1)
{
    if(ui->thread->text()==0)
        thread_Flag-0;
    else
        thread_Flag=1;
}
