#ifndef BASIC_CIRCULAR_H
#define BASIC_CIRCULAR_H

#include <QString>
#include <QDir>

// #include <QDesktopServices>
#include <QUrl>

class Basic_Circular
{
public:
    Basic_Circular();

    static QString getFileName();
    static void setFileName();
    static void setFileName(QString);

    static bool getStopped();
    static void setStopped(bool);

    static bool getPlayBack_stopped();
    static void setPlayBack_stopped(bool);

    // static float getFrameLength();
    // static void setFrameLength(float);

    // static int getTimeInterval();
    static int getTimeInterval(int index);
    static void append(int time);

    static QString getConfigArr(int index);
    static void setConfigArr(int index, QString config);

private:
    static QString fileName;            //文件保存路径
    static bool stopped;                //录制暂停标志
    static bool playBack_stopped;       //回放暂停标志
    // static float frameLength;           //一帧数据对应的视频长度，毫秒
    static QVector<int> timeInterval;   //回放时每次数据刷新的间隔,毫秒
    static QString configArr[16];       //保存配置的数组

};

#endif // BASIC_CIRCULAR_H
