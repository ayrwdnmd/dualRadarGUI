#include "basic_circular.h"

QString Basic_Circular::fileName = "";
bool Basic_Circular::stopped = 1;
bool Basic_Circular::playBack_stopped = 1;
// float Basic_Circular::frameLength = 50;
QVector<int> Basic_Circular::timeInterval;
QString Basic_Circular::configArr[16] = {"20","-20","30","0",               //0  maxXaxis, minXaxis, maxYaxis, minYaxis
                                         "8","8","39",                      //4  pointSize, fontSize, colWidth
                                         "1","5.2",                         //7  carWidth, carLength
                                         "HD camera","2","USB Camera","2",  //9  camera1, format1, camera2, format2
                                         "0","0","1"};                      //13 mode, chartViewUp, chartViewDown


Basic_Circular::Basic_Circular() {
}

QString Basic_Circular::getFileName()
{
    return Basic_Circular::fileName;
}
void Basic_Circular::setFileName()
{
    Basic_Circular::fileName = QDir::currentPath();
    Basic_Circular::fileName += "/data/data_";
    QDateTime dateTime(QDateTime::currentDateTime());
    QString time = dateTime.toString("yy-MM-dd-hh-mm-ss");
    Basic_Circular::fileName += QString("%1").arg(time);
}
void Basic_Circular::setFileName(QString name)
{
    Basic_Circular::fileName = name;
}

bool Basic_Circular::getStopped()
{
    return Basic_Circular::stopped;
}
void Basic_Circular::setStopped(bool stop)
{
    Basic_Circular::stopped = stop;
}

bool Basic_Circular::getPlayBack_stopped()
{
    return Basic_Circular::playBack_stopped;
}
void Basic_Circular::setPlayBack_stopped(bool stop)
{
    Basic_Circular::playBack_stopped = stop;
}

// float Basic_Circular::getFrameLength()
// {
//     return Basic_Circular::frameLength;
// }
// void Basic_Circular::setFrameLength(float length)
// {
//     Basic_Circular::frameLength = length;
// }

int Basic_Circular::getTimeInterval(int index)
{
    return Basic_Circular::timeInterval[index];
}
void Basic_Circular::append(int time)
{
    Basic_Circular::timeInterval.append(time);
}

QString Basic_Circular::getConfigArr(int index)
{
    return Basic_Circular::configArr[index];
}
void Basic_Circular::setConfigArr(int index, QString config)
{
    Basic_Circular::configArr[index] = config;
}
