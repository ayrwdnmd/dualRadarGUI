#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>
//摄像头所需头文件
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QImageCapture>
#include <QVideoWidget>
#include <QVideoSink>
#include <QDir>

#include <QDesktopServices>
#include <QUrl>
#include "basic_circular.h"
namespace Ui {
class newWindow;
}

class newWindow : public QWidget
{
    Q_OBJECT

public:
    explicit newWindow(QWidget *parent = nullptr);

    bool cameraPostion = 0; //摄像头位置

    //摄像头
    QList<QCameraDevice> list_cameras;
    QCamera * m_camera[2];
    QMediaCaptureSession my_captureSession[2];
    QMediaRecorder * recorder[2];
    bool camera_state = 0;
    void cameraStart();
    void clickStart();
    void cameraFiring(int cameraIndex, int formatIndex, int position);
    void recorderStart();
    void recoederChoose(int i);
    void recorderStop();

    ~newWindow();

signals:
    void s_clickStart();
    void newWindowStart();
    void newWindowStop();

private:
    Ui::newWindow *ui;
};

#endif // NEWWINDOW_H
