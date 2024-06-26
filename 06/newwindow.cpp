#include "newwindow.h"
#include "ui_newwindow.h"

newWindow::newWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newWindow)
{
    ui->setupUi(this);
    list_cameras = QMediaDevices::videoInputs();
    connect(ui->pushButton_camera,&QPushButton::clicked,this,&newWindow::cameraStart);
    connect(ui->pushButton_start,&QPushButton::clicked,this,&newWindow::clickStart);
}

newWindow::~newWindow()
{
    delete ui;
}

//点击start按钮，打开录制
void newWindow::clickStart()
{
    if(Basic_Circular::getStopped() == 1)
    {
        emit s_clickStart();
        recorderStart();
        ui->pushButton_start->setText("stop");
        Basic_Circular::setStopped(0);
    }
    else
    {
        emit s_clickStart();
        recorderStop();
        ui->pushButton_start->setText("start");
        Basic_Circular::setStopped(1);
    }
}

//打开窗口后自动打开摄像头
void newWindow::cameraStart()
{
    int cameraIndex1 = 0,cameraIndex2 = 0;
    for(int i = 0; i < list_cameras.length(); i++)
    {
        if(list_cameras[i].description() == Basic_Circular::getConfigArr(9))
        {
            cameraIndex1 = i;
        }
        if(list_cameras[i].description() == Basic_Circular::getConfigArr(11))
        {
            cameraIndex2 = i;
        }
    }
    cameraFiring(cameraIndex1,Basic_Circular::getConfigArr(10).toInt(),0);
    cameraFiring(cameraIndex2,Basic_Circular::getConfigArr(12).toInt(),1);
}

//窗口开始显示摄像头内容
void newWindow::cameraFiring(int i, int formatIndex, int position)
{
    QVideoWidget * display_widget = (!position)?ui->display_widget2:ui->display_widget3;
    m_camera[position] = new QCamera(list_cameras[i]);
    my_captureSession[position].setCamera(m_camera[position]);
    my_captureSession[position].setVideoOutput(display_widget);
    QList<QCameraFormat> list_format = list_cameras[i].videoFormats();      //获取可用配置列表
    m_camera[position]->setCameraFormat(list_format[formatIndex]);          //选择配置，默认第3组配置
    m_camera[position]->start();
    my_captureSession[position].recorder();
    recorder[position] = new QMediaRecorder(m_camera[position]);
    my_captureSession[position].setRecorder(recorder[position]);
}

//开始录制，保存摄像头录像
void newWindow::recorderStart()
{
    if(recorder[0] != NULL)
        recoederChoose(0);
    if(recorder[1] != NULL)
        recoederChoose(1);
}

//保存摄像头录像
void newWindow::recoederChoose(int i)
{
    QString videoPath;
    videoPath = Basic_Circular::getFileName() + "/" + QString::number(i) + "video.mp4";
    recorder[i]->setOutputLocation(QUrl::fromLocalFile(videoPath));
    recorder[i]->setVideoBitRate(20);                       //帧数
    recorder[i]->setQuality(QMediaRecorder::NormalQuality); //质量
    recorder[i]->setVideoResolution(640,480);               //分辨率
    recorder[i]->record();
}

//结束录制，关闭两个摄像头
void newWindow::recorderStop()
{
    if(recorder[0] != NULL)
        recorder[0]->stop();
    if(recorder[1] != NULL)
        recorder[1]->stop();
}
