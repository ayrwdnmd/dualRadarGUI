#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canthread.h"
#include "newwindow.h"
#include "settingwindow.h"
#include "basic_circular.h"
#include <QtCharts>
#include <QVideoWidget>

#include <QWidget>
#include <QMessageBox>
#include <QDir>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QKeyEvent>

//摄像头所需头文件
#include <QCamera>
#include <QCameraDevice>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QVideoSink>
#include <QSettings>

#include <QtMultimedia>
#include <QtMultimediaWidgets>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    //布局
    float max_Xaxis = 20;
    float min_Xaxis = -20;
    float max_Yaxis = 30;
    float min_Yaxis = 0;
    int PointSize = 8;      //点大小
    int FontSize = 8;       //字体大小
    int ColumnWidth = 39;   //列宽
    float half_of_car_width = 1;
    float car_lenght = 5.2;
    float pi = 3.14;
    int cameraIndex1 = -1;
    int cameraIndex2 = -1;
    int cameraFormat1 = -1;
    int cameraFormat2 = -1;
    // QString configArr[13] =   //创建数组保存所有设置
    //     {"20","-20","30","0","8","8","39","1","5.2","HD camera","2","USB Camera","2"};
    QValueAxis *axisBX = new QValueAxis();  //在坐标系上输出目标点
    QValueAxis *axisBY = new QValueAxis();
    QValueAxis *axisAX = new QValueAxis();
    QValueAxis *axisAY = new QValueAxis();
    QSerialPort *serial = new QSerialPort;
    void printCar();
    void printRod();
    void setAxis();
    void layout();
    void loadConfig();
    void changeSetting();

    //列表数据
    QFile *fr;      //以美观易读格式保存
    QFile *fp;      //以方便回放格式保存
    QFile *ftemp;   //以坐标系方式保存
    float perviousW = 0;    //上一帧的车轮脉冲,用于计算距离
    void output(frame_complete fl, frame_complete fr);
    int output_half(frame_complete f, bool filter, bool position, QScatterSeries * half_series);
    void refreshSeries(bool filter, QScatterSeries * series);
    void dataSave(frame_complete fc, bool position);
    void save_half(frame_complete fc, bool filter, bool position);
    void openFolder();
    void chartHide(bool filiter);
    void chartHeightSet();

    //回放目标点
    int currentID = -1;     //当前回放帧id
    UINT radarCnt = 1;      //安装的雷达数,1或2,影响回放时的跨度
    UINT startTime = 0;     //记录第一帧的系统时间，毫秒
    QTextStream *txtInput;  //txt文件
    struct double_frame
    {
        frame_complete fl;
        frame_complete fr;
    };//同时包含左右雷达数据的一帧
    double_frame read_frame;
    QVector<double_frame> allData;  //全部数据集合为一个数组
    void playBack_half(bool position, bool filter);
    void playBack_start();
    void playBack_next();
    void playBack_previous();
    void playBack_next_x();
    void playBack_previous_x();
    void playBack_designate();
    void dragSlider();

    //回放录像
    QMediaPlayer * player_pb0;
    QMediaPlayer * player_pb1;
    int cameraCount;  //摄像头数量,1或2
    void playBack_view();
    void playBack_view_half(UINT index, QVideoWidget *v);
    void view_play();
    void view_pause();
    void playBack_currentID();
    // void setDuration();

    //摄像头
    QList<QCameraDevice> list_cameras;
    QCamera * m_camera[2];
    QMediaCaptureSession my_captureSession[2];
    QMediaRecorder * recorder[2];
    bool camera_state = 0;
    void getCamera();
    void clickCamera();
    void cameraFiring(int i, int formatIndex, int position);
    void recorderStart();
    void recoederChoose(int i);
    void recorderStop();
    void cameraSet(int cameraIndex, int formatIndex, int position);

    //数据
    void clickStart(CANThread *canthread);
    void createFolder();
    void outVehicleStatus(frame_complete fl, frame_complete fr); //输出车身can信号
    void save_VehicleStatus(frame_complete fc);
    void playBack_time();
    void playBack_VehicleStatus(bool position);

    //蜂鸣器
    QMediaPlayer *audioPlayer;
    int pathStatus = 0;
    int audioPlayerStatus_l = 0;
    int audioPlayerStatus_r = 0;
    void buzzerOut(UINT ALERT_SIG, bool position);

    //打开新窗口
    // void openNewWindow(newWindow *configWindow);
    // void openSettingWindow(settingwindow *configWindow);

    ~MainWindow();

signals:
    void playBack_over();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
