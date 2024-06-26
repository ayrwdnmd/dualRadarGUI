#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QMediaDevices>
#include <QSettings>
#include <QDir>
#include "qbuttongroup.h"
#include "basic_circular.h"

namespace Ui {
class settingwindow;
}

class settingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit settingwindow(QWidget *parent = nullptr);

    void layout();
    void saveConfig();
    void loadConfig();

    QButtonGroup * modeGroup = new QButtonGroup(this);
    void showChartList(int mode);

    QList<QCameraDevice> list_cameras;
    void showCameraList();
    void showFormatList(int index, bool position);

    ~settingwindow();

signals:
    void selectCamera(int cameraIndex, int formatIndex, int position);
    void click_save();

private:
    Ui::settingwindow *ui;
};

#endif // SETTINGWINDOW_H
