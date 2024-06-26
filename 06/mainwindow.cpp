#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    list_cameras = QMediaDevices::videoInputs();    //检测摄像头设备
    loadConfig();
    changeSetting();
    // layout();
    CANThread *canthread = new CANThread();
    newWindow *configWindow = new newWindow();
    settingwindow *s_window = new settingwindow();

    //用于uart串口通讯
    // foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    // {
    //     QSerialPort serial;
    //     serial.setPort(info);
    //     if(serial.open(QIODevice::ReadWrite))
    //     {
    //         qDebug()<<serial.portName();
    //         serial.close();
    //     }
    // }

    //设置串口名
    serial->setPortName("COM7");
    //打开串口
    serial->open(QIODevice::ReadWrite);
    //设置波特率
    serial->setBaudRate(3000000);
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(ui->pushButton_start,&QPushButton::clicked,canthread,[canthread,this](){
        clickStart(canthread);
    });

    connect(ui->pushButton_pb_start,&QPushButton::clicked,canthread,[canthread,this](){
        if(Basic_Circular::getPlayBack_stopped() == 1){
            Basic_Circular::setPlayBack_stopped(0);
            canthread->start();
            view_play();
            view_pause();
        }
        else{
            view_pause();
            Basic_Circular::setPlayBack_stopped(1);
        }
    });

    connect(this,&MainWindow::playBack_over,[](){
        Basic_Circular::setPlayBack_stopped(1);
    });

    connect(canthread,&CANThread::getCompleteFrame,this,&MainWindow::output);
    connect(canthread,&CANThread::saveSignal,this,&MainWindow::dataSave);
    connect(canthread,&CANThread::sleep_50,this,&MainWindow::playBack_start);

    connect(configWindow,&newWindow::s_clickStart,canthread,[canthread,this](){
        clickStart(canthread);
    });

    connect(s_window,&settingwindow::selectCamera,this,&MainWindow::cameraSet);
    connect(s_window,&settingwindow::click_save,this,&MainWindow::changeSetting);

    connect(ui->pushButton_camera,&QPushButton::clicked,this,&MainWindow::clickCamera);
    connect(ui->pushButton_dataPath,&QPushButton::clicked,this,&MainWindow::openFolder);
    connect(ui->pushButton_pb_next,&QPushButton::clicked,this,&MainWindow::playBack_next);
    connect(ui->pushButton_pb_previon,&QPushButton::clicked,this,&MainWindow::playBack_previous);
    connect(ui->pushButton_pb_forward,&QPushButton::clicked,this,&MainWindow::playBack_next_x);
    connect(ui->pushButton_pb_rewind,&QPushButton::clicked,this,&MainWindow::playBack_previous_x);
    connect(ui->pushButton_bk,&QPushButton::clicked,this,[this](){
        if(ui->chartView_bk->isHidden())
            ui->pushButton_bk->setText("bk hide");
        else
            ui->pushButton_bk->setText("bk show");
        chartHide(false);
    });
    connect(ui->pushButton_ak,&QPushButton::clicked,this,[this](){
        if(ui->chartView_ak->isHidden())
            ui->pushButton_ak->setText("ak hide");
        else
            ui->pushButton_ak->setText("ak show");
        chartHide(true);
    });

    connect(ui->pushButton_floating,&QPushButton::clicked,configWindow,[configWindow](){
        configWindow->show();
    });

    connect(ui->pushButton_setting,&QPushButton::clicked,s_window,[s_window](){
        s_window->show();
    });

    connect(ui->lineEdit_target,&QLineEdit::editingFinished,this,&MainWindow::playBack_designate);
    connect(ui->horizontalSlider,&QSlider::sliderReleased,this,&MainWindow::dragSlider);
}

MainWindow::~MainWindow()
{
    recorderStop();
    fr->close();
    fp->close();
    ftemp->close();
    player_pb0->stop();
    player_pb1->stop();
    audioPlayer->stop();
    audioPlayerStatus_l = 0;
    audioPlayerStatus_r = 0;
    delete ui;
}

//读取ini文件，加载设置
void MainWindow::loadConfig()
{
    QDir dir(QDir::currentPath());
    QString configFile = QDir::currentPath() + "/config";
    if(!dir.exists(configFile))
    {
        dir.mkdir(configFile);
    }
    configFile += "/config_init.ini";
    QSettings *configIniRead = new QSettings(configFile,QSettings::IniFormat);
    // QString configArr[13] =   //创建数组保存所有设置
    //     {"20","-20","30","0","8","8","39","1","5.2","0","2","1","2"};   //参数默认值
    if(configIniRead->value("/table/ColumnWidth").toFloat() != 0)
    {
        Basic_Circular::setConfigArr(0, configIniRead->value("/map/max_Xaxis").toString());
        Basic_Circular::setConfigArr(1, configIniRead->value("/map/min_Xaxis").toString());
        Basic_Circular::setConfigArr(2, configIniRead->value("/map/max_Yaxis").toString());
        Basic_Circular::setConfigArr(3, configIniRead->value("/map/min_Yaxis").toString());
        Basic_Circular::setConfigArr(4, configIniRead->value("/table/PointSize").toString());
        Basic_Circular::setConfigArr(5, configIniRead->value("/table/FontSize").toString());
        Basic_Circular::setConfigArr(6, configIniRead->value("/table/ColumnWidth").toString());
        Basic_Circular::setConfigArr(7, configIniRead->value("/car/width").toString());
        Basic_Circular::setConfigArr(8, configIniRead->value("/car/lenght").toString());
        Basic_Circular::setConfigArr(9, configIniRead->value("/camera/camera_1").toString());
        Basic_Circular::setConfigArr(10, configIniRead->value("/camera/format_1").toString());
        Basic_Circular::setConfigArr(11, configIniRead->value("/camera/camera_2").toString());
        Basic_Circular::setConfigArr(12, configIniRead->value("/camera/format_2").toString());
        Basic_Circular::setConfigArr(13, configIniRead->value("/mode/mode").toString());
        Basic_Circular::setConfigArr(14, configIniRead->value("/mode/chart_up").toString());
        Basic_Circular::setConfigArr(15, configIniRead->value("/mode/chart_down").toString());
    }
}

//设计布局
void MainWindow::layout()
{
    //可以将4个表的格式配置放进同一个函数中以提高代码复用性，但是考虑到可能要针对每个表做出不同调整，故先放着
    QTableWidgetItem *headerItem_l_b;
    QStringList headerText_Row_l_b;
    headerText_Row_l_b << "R" << "V" << "A" << "E" << "P";
    ui->table_l_bk->setHorizontalHeaderLabels(headerText_Row_l_b);
    ui->table_l_bk->setColumnCount(headerText_Row_l_b.count());
    for (int i=0;i<ui->table_l_bk->columnCount();i++)
    {
        headerItem_l_b=new QTableWidgetItem(headerText_Row_l_b.at(i));
        QFont font=headerItem_l_b->font();
        font.setBold(true);
        font.setPointSize(PointSize);
        headerItem_l_b->setFont(font);
        ui->table_l_bk->setHorizontalHeaderItem(i,headerItem_l_b);
        ui->table_l_bk->setColumnWidth(i, ColumnWidth);
    }
    ui->table_l_bk->setFont(QFont("song", FontSize));

    QTableWidgetItem *headerItem_l_a;
    QStringList headerText_Row_l_a;
    headerText_Row_l_a << "R" << "V" << "A" << "E" << "P";
    ui->table_l_ak->setHorizontalHeaderLabels(headerText_Row_l_a);
    ui->table_l_ak->setColumnCount(headerText_Row_l_a.count());
    for (int i=0;i<ui->table_l_ak->columnCount();i++)
    {
        headerItem_l_a=new QTableWidgetItem(headerText_Row_l_a.at(i));
        QFont font=headerItem_l_a->font();
        font.setBold(true);
        font.setPointSize(PointSize);
        headerItem_l_a->setFont(font);
        ui->table_l_ak->setHorizontalHeaderItem(i,headerItem_l_a);
        ui->table_l_ak->setColumnWidth(i, ColumnWidth);
    }
    ui->table_l_ak->setFont(QFont("song", FontSize));

    QTableWidgetItem *headerItem_r_b;
    QStringList headerText_Row_r_b;
    headerText_Row_r_b << "R" << "V" << "A" << "E" << "P";
    ui->table_r_bk->setHorizontalHeaderLabels(headerText_Row_r_b);
    ui->table_r_bk->setColumnCount(headerText_Row_r_b.count());
    for (int i=0;i<ui->table_r_bk->columnCount();i++)
    {
        headerItem_r_b=new QTableWidgetItem(headerText_Row_r_b.at(i));
        QFont font=headerItem_r_b->font();
        font.setBold(true);
        font.setPointSize(PointSize);
        headerItem_r_b->setFont(font);
        ui->table_r_bk->setHorizontalHeaderItem(i,headerItem_r_b);
        ui->table_r_bk->setColumnWidth(i, ColumnWidth);
    }
    ui->table_r_bk->setFont(QFont("song", FontSize));

    QTableWidgetItem *headerItem_r_a;
    QStringList headerText_Row_r_a;
    headerText_Row_r_a << "R" << "V" << "A" << "E" << "P";
    ui->table_r_ak->setHorizontalHeaderLabels(headerText_Row_r_a);
    ui->table_r_ak->setColumnCount(headerText_Row_r_a.count());       // 列数设置为与headerText_Row的列相等
    for (int i=0;i<ui->table_r_ak->columnCount();i++)
    {
        headerItem_r_a=new QTableWidgetItem(headerText_Row_r_a.at(i));      // headerText.at(i) 获取headerText的i行字符串
        QFont font=headerItem_r_a->font();                              // 获取原有字体设置
        font.setBold(true);                                         // 设置为粗体
        font.setPointSize(PointSize);                                       // 设置字体大小
        headerItem_r_a->setFont(font);                                  // 设置字体
        ui->table_r_ak->setHorizontalHeaderItem(i,headerItem_r_a);     // 设置表头单元格的Item
        ui->table_r_ak->setColumnWidth(i, ColumnWidth);
    }
    ui->table_r_ak->setFont(QFont("song", FontSize));

    //设置蜂鸣器音效
    audioPlayer = new QMediaPlayer;
    QString path = "C:/Qt/qtProject/can/06/audio/buzzer flash.mp3";
    audioPlayer->setSource(QUrl::fromLocalFile(path));
    audioPlayer->setLoops(-1);
    audioPlayer->setAudioOutput(new QAudioOutput);

    //设置坐标轴
    setAxis();
}

//设置坐标轴
void MainWindow::setAxis()
{
    ui->chartView_ak->chart()->removeAxis(axisAX);
    ui->chartView_ak->chart()->removeAxis(axisAY);
    ui->chartView_bk->chart()->removeAxis(axisBX);
    ui->chartView_bk->chart()->removeAxis(axisBY);

    axisAX->setRange(min_Xaxis, max_Xaxis);
    axisAY->setRange(min_Yaxis, max_Yaxis);
    axisBX->setRange(min_Xaxis, max_Xaxis);
    axisBY->setRange(min_Yaxis, max_Yaxis);

    if(Basic_Circular::getConfigArr(13).toInt() == 0)   //当使用LCA功能时，将坐标系反转，将x轴标签置于上方
    {
        axisAX->setReverse();
        axisAY->setReverse();
        axisBX->setReverse();
        axisBY->setReverse();
        ui->chartView_ak->chart()->addAxis(axisAX, Qt::AlignTop);
        ui->chartView_bk->chart()->addAxis(axisBX, Qt::AlignTop);
    }
    else
    {
        axisAX->setReverse(false);
        axisAY->setReverse(false);
        axisBX->setReverse(false);
        axisBY->setReverse(false);
        ui->chartView_ak->chart()->addAxis(axisAX, Qt::AlignBottom);
        ui->chartView_bk->chart()->addAxis(axisBX, Qt::AlignBottom);
    }
    ui->chartView_ak->chart()->addAxis(axisAY, Qt::AlignLeft);
    ui->chartView_bk->chart()->addAxis(axisBY, Qt::AlignLeft);
}

//根据设置，变更布局
void MainWindow::changeSetting()
{
    max_Xaxis = Basic_Circular::getConfigArr(0).toFloat();
    min_Xaxis = Basic_Circular::getConfigArr(1).toFloat();
    max_Yaxis = Basic_Circular::getConfigArr(2).toFloat();
    min_Yaxis = Basic_Circular::getConfigArr(3).toFloat();
    PointSize = Basic_Circular::getConfigArr(4).toInt();
    FontSize = Basic_Circular::getConfigArr(5).toInt();
    ColumnWidth = Basic_Circular::getConfigArr(6).toInt();
    half_of_car_width = Basic_Circular::getConfigArr(7).toFloat();
    car_lenght = Basic_Circular::getConfigArr(8).toFloat();

    for(int i = 0; i < list_cameras.length(); i++)
    {
        if(list_cameras[i].description() == Basic_Circular::getConfigArr(9))
        {
            cameraIndex1 = i;
            cameraFormat1 = Basic_Circular::getConfigArr(10).toInt();
        }
        if(list_cameras[i].description() == Basic_Circular::getConfigArr(11))
        {
            cameraIndex2 = i;
            cameraFormat2 = Basic_Circular::getConfigArr(12).toInt();
        }
    }
    if(Basic_Circular::getConfigArr(14).toInt() == 0)
        ui->chartView_bk->hide();
    else
        ui->chartView_bk->show();
    if(Basic_Circular::getConfigArr(15).toInt() == 0)
        ui->chartView_ak->hide();
    else
        ui->chartView_ak->show();
    chartHeightSet();

    //保存设置后变更布局
    layout();

    if(currentID != -1) //若正在播放录像，更改设置之后刷新图表
        playBack_designate();
}

//点击start
void MainWindow::clickStart(CANThread *canthread)
{
    if(Basic_Circular::getStopped() == 1){
        if(canthread->clicked_start())
        {
            Basic_Circular::setStopped(0);
            canthread->start();
            ui->pushButton_start->setText("stop");
            ui->pushButton_camera->setEnabled(false);
            createFolder();
            if(camera_state != 0)
                recorderStart();
        }
    }
    else{
        Basic_Circular::setStopped(1);
        ui->pushButton_start->setText("start");
        ui->pushButton_camera->setEnabled(true);
        if(camera_state != 0)
            recorderStop();
        fr->close();
        fp->close();
        ftemp->close();
    }
}

//输出数据到列表、地图
void MainWindow::output(frame_complete fl, frame_complete fr)
{
    bool left = 0;
    bool right = 1;
    bool bk = 0;
    bool ak = 1;
    QScatterSeries * series_l_b = new QScatterSeries();
    series_l_b->setMarkerSize(8);
    QScatterSeries * series_l_a = new QScatterSeries();
    series_l_a->setMarkerSize(8);
    QScatterSeries * series_r_b = new QScatterSeries();
    series_r_b->setMarkerSize(8);
    QScatterSeries * series_r_a = new QScatterSeries();
    series_r_a->setMarkerSize(8);

    outVehicleStatus(fl, fr);
    series_l_b->setName(QString::number(output_half(fl,bk,left,series_l_b)));
    series_l_a->setName(QString::number(output_half(fl,ak,left,series_l_a)));
    if(radarCnt == 2 || !Basic_Circular::getStopped())
    {
        series_r_b->setName(QString::number(output_half(fr,bk,right,series_r_b)));
        series_r_a->setName(QString::number(output_half(fr,ak,right,series_r_a)));
    }
    ui->chartView_ak->chart()->removeAllSeries();
    ui->chartView_bk->chart()->removeAllSeries();
    refreshSeries(bk,series_l_b);
    refreshSeries(ak,series_l_a);
    if(radarCnt == 2)
    {
        refreshSeries(bk,series_r_b);
        refreshSeries(ak,series_r_a);
    }

    switch(Basic_Circular::getConfigArr(13).toInt())
    {
    case 0:
        printCar();
        break;
    case 1:
        printRod();
        break;
    }
}
int MainWindow::output_half(frame_complete fc, bool filter, bool position, QScatterSeries * half_series)
{
    QTableWidget * half_table;
    track_measu_t half_farme[64];
    UINT cnt;
    if(filter)
    {
        cnt = fc.ak_cnt;
        memcpy(half_farme, &fc.ak, sizeof(track_measu_t) * 64);
        half_table = position?ui->table_r_ak:ui->table_l_ak;
    }
    else
    {
        cnt = fc.bk_cnt;
        memcpy(half_farme, &fc.bk, sizeof(track_measu_t) * 64);
        half_table = position?ui->table_r_bk:ui->table_l_bk;
    }
    half_table->clearContents();
    half_table->setRowCount(cnt);
    float x,y,z;
    for(UINT i = 0; i < cnt; i++)
    {
        half_table->setItem(i, 0, new QTableWidgetItem(QString::number(half_farme[i].range)));
        half_table->setItem(i, 1, new QTableWidgetItem(QString::number(half_farme[i].velocity)));
        half_table->setItem(i, 2, new QTableWidgetItem(QString::number(half_farme[i].angle)));
        half_table->setItem(i, 3, new QTableWidgetItem(QString::number(half_farme[i].angle_e)));
        half_table->setItem(i, 4, new QTableWidgetItem(QString::number(half_farme[i].SNR)));
        switch(Basic_Circular::getConfigArr(13).toInt())
        {
        case 0:     //LCA
            x = qSin(qPow(-1,position)*(45 - half_farme[i].angle) * pi / 180) * half_farme[i].range
                + qPow(-1,position) * half_of_car_width;
            y = qCos(qPow(-1,position)*(45 - half_farme[i].angle) * pi / 180) * half_farme[i].range
                + car_lenght;
            half_series->append(x,y);
            break;
        case 1:     //HDS
            x = qSin(half_farme[i].angle * pi / 180) * half_farme[i].range;
            y = qCos(half_farme[i].angle * pi / 180) * half_farme[i].range;
            z = qSin(half_farme[i].angle_e * pi / 180) * half_farme[i].range;
            if(Basic_Circular::getConfigArr(14 + filter).toInt() == 1)
            {
                half_series->append(x,y);
            }
            else if(Basic_Circular::getConfigArr(14 + filter).toInt() == 2)
            {
                half_series->append(z,y);
            }
            break;
        case 2:     //AUTODOOR
            x = qSin(half_farme[i].angle * pi / 180) * half_farme[i].range;
            y = qCos(half_farme[i].angle * pi / 180) * half_farme[i].range;
            half_series->append(x,y);
            break;
        }
    }
    buzzerOut(fc.ALERT_SIG,position);
    return fc.frame_number;
}
void MainWindow::refreshSeries(bool filter, QScatterSeries * half_series)
{
    QChartView * half_chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
    if(filter)
    {
        half_chart = ui->chartView_ak;
        axisX = axisAX;
        axisY = axisAY;
    }
    else
    {
        half_chart = ui->chartView_bk;
        axisX = axisBX;
        axisY = axisBY;
    }
    half_chart->chart()->addSeries(half_series);
    half_series->attachAxis(axisX);
    half_series->attachAxis(axisY);
}

//在坐标系中画出车辆位置大小
void MainWindow::printCar()
{
    QLineSeries *car[2];
    for(int i = 0; i < 2; i++)
    {
        car[i] = new QLineSeries();
        car[i]->append(half_of_car_width, 0);
        car[i]->append(half_of_car_width, car_lenght);
        car[i]->append(-half_of_car_width, car_lenght);
        car[i]->append(-half_of_car_width, 0);
        car[i]->append(half_of_car_width, 0);
    }
    car[0]->setName("BK");
    ui->chartView_bk->chart()->addSeries(car[0]);
    car[0]->attachAxis(axisBX);
    car[0]->attachAxis(axisBY);
    car[1]->setName("AK");
    ui->chartView_ak->chart()->addSeries(car[1]);
    car[1]->attachAxis(axisAX);
    car[1]->attachAxis(axisAY);
}

//画出限高杆报警位置
void MainWindow::printRod()
{
    QLineSeries *rod_0[2], *rod_1[2];
    for(int i = 0; i < 2; i++)
    {
        rod_0[i] = new QLineSeries();
        rod_0[i]->append(0.5, 0);
        rod_0[i]->append(0.5, 10);
        rod_0[i]->append(-0.5, 10);
        rod_0[i]->append(-0.5, 0);
        rod_0[i]->append(0.5, 0);

        rod_1[i] = new QLineSeries();
        rod_1[i]->append(0,0);
        rod_1[i]->append(0,10);
        rod_1[i]->append(2,10);
        rod_1[i]->append(2,0);
        rod_1[i]->append(0,0);
    }

    if(Basic_Circular::getConfigArr(14).toInt() == 1)
    {
        rod_0[0]->setName("hds bk");
        ui->chartView_bk->chart()->addSeries(rod_0[0]);
        rod_0[0]->attachAxis(axisBX);
        rod_0[0]->attachAxis(axisBY);
    }
    else
    {
        rod_1[0]->setName("hds bk");
        ui->chartView_bk->chart()->addSeries(rod_1[0]);
        rod_1[0]->attachAxis(axisBX);
        rod_1[0]->attachAxis(axisBY);
    }

    if(Basic_Circular::getConfigArr(15).toInt() == 1)
    {
        rod_0[1]->setName("hds ak");
        ui->chartView_ak->chart()->addSeries(rod_0[1]);
        rod_0[1]->attachAxis(axisAX);
        rod_0[1]->attachAxis(axisAY);
    }
    else
    {
        rod_1[1]->setName("hds ak");
        ui->chartView_ak->chart()->addSeries(rod_1[1]);
        rod_1[1]->attachAxis(axisAX);
        rod_1[1]->attachAxis(axisAY);
    }
}

//隐藏地图
void MainWindow::chartHide(bool filiter)
{
    QChartView *tempChart = (filiter)?ui->chartView_ak:ui->chartView_bk;
    if(tempChart->isHidden())
        tempChart->show();
    else
        tempChart->hide();

    chartHeightSet();
}

//确保图表长度正常
void MainWindow::chartHeightSet()
{
    if((!ui->chartView_ak->isHidden()) && (!ui->chartView_bk->isHidden()))
    {
        ui->chartView_ak->setMaximumHeight(380);
        ui->chartView_bk->setMaximumHeight(380);
    }
    else
    {
        ui->chartView_ak->setMaximumHeight(760);
        ui->chartView_bk->setMaximumHeight(760);
    }
}

//保存数据到文档
void MainWindow::dataSave(frame_complete fc, bool position)
{
    bool bk = 0;
    bool ak = 1;
    save_half(fc,bk,position);
    save_half(fc,ak,position);
}
void MainWindow::save_half(frame_complete fc, bool filter, bool position)
{
    track_measu_t half_farme[64];
    UINT cnt;
    fr->write("frameNumber: ");
    fr->write(QString::number(fc.frame_number).toStdString().c_str());   //输出当前帧编号
    if(filter)
    {
        cnt = fc.ak_cnt;
        memcpy(half_farme, &fc.ak, sizeof(track_measu_t) * 64);
        // ftemp->write("ak\n");
        if(position)
        {
            fr->write("    right   ak      cnt: ");
            fp->write("frameHead right ak\n");
        }
        else
        {
            fr->write("    left    ak      cnt: ");
            fp->write("frameHead left ak\n");
        }
    }
    else
    {
        cnt = fc.bk_cnt;
        memcpy(half_farme, &fc.bk, sizeof(track_measu_t) * 64);
        ftemp->write("bk\n");
        if(position)
        {
            fr->write("    right   bk      cnt: ");
            fp->write("frameHead right bk\n");
        }
        else
        {
            fr->write("    left    bk      cnt: ");
            fp->write("frameHead left bk\n");
        }
        //在bk的开头保存系统时间
        QDateTime dateTime(QDateTime::currentDateTime());
        QString time = dateTime.toString("hh mm ss zzz");
        time += "\n";
        fp->write(time.toStdString().c_str());
    }
    fr->write(QString::number(cnt).toStdString().c_str());
    if(!filter)
        save_VehicleStatus(fc);
    fp->write(QString::number(fc.frame_number).toStdString().c_str());
    fp->write(" ");
    fp->write(QString::number(cnt).toStdString().c_str());
    fp->write(" ");
    fp->write(QString::number(fc.ALERT_SIG).toStdString().c_str());
    fp->write("\n");

    QString range_s,velocity_s,angle_s,angle_e_s,SNR_s,line_s,i_s,x,y,z,w;
    const char *line_c;
    // const char *line_c_p;
    //输出表头
    fr->write("\nid range velocity angle angle_e snr\n");
    for(UINT i = 0; i < cnt; i++)
    {
        range_s = QString::number(half_farme[i].range, 'f', 2);
        velocity_s = QString::number(half_farme[i].velocity, 'f', 2);
        angle_s = QString::number(half_farme[i].angle, 'f', 2);
        angle_e_s = QString::number(half_farme[i].angle_e, 'f', 2);
        SNR_s = QString::number(half_farme[i].SNR, 'f', 2);
        i_s = QString::number(i);
        line_s = i_s + "\t  " + range_s + "\t  " + velocity_s + "\t  " + angle_s + "\t  " + angle_e_s + "\t  " + SNR_s + "\n";
        line_c = line_s.toStdString().c_str();
        fr->write(line_c);
        line_s = i_s + " " + range_s + " " + velocity_s + " " + angle_s + " " + angle_e_s + " " + SNR_s + "\n";
        line_c = line_s.toStdString().c_str();
        fp->write(line_c);
        if(!filter)
        {
            if(perviousW == 0)
                perviousW = fc.VS.Speed;
            x = QString::number((half_farme[i].range * sin(half_farme[i].angle * pi / 180)), 'f', 2);
            y = QString::number((half_farme[i].range * cos(half_farme[i].angle * pi / 180)), 'f', 2);
            z = QString::number((half_farme[i].range * sin(half_farme[i].angle_e * pi / 180)), 'f', 2);
            w = QString::number(((fc.VS.Speed - perviousW) * 7.2 / 300), 'f', 2);
            perviousW = fc.VS.Speed;
            line_s = "ID: " + QString::number(i) + "\t X: "+ x + "\t Y: " + y + "\t Z: " + z + " \t W: " + w + "\n";
            line_c = line_s.toStdString().c_str();
            if(half_farme[i].angle_e < 70 && half_farme[i].angle_e > -70)
                ftemp->write(line_c);
        }
    }

    fr->write("\n");
    fp->write("frameEnd\n");
}

//点击camera按钮，打开摄像头(连接的摄像头数量不等于摄像头设备数list_camera.length())
void MainWindow::clickCamera()
{
    list_cameras = QMediaDevices::videoInputs();
    if(camera_state == 0)
    {
        if(cameraFormat1 == -1 && cameraFormat2 == -1)
        {
            QMessageBox msgBox;
            msgBox.setText("打开摄像头失败");
            msgBox.exec();
            return;
        }
        camera_state = 1;
        if(cameraFormat1 != -1)
            cameraFiring(cameraIndex1,cameraFormat1,0);
        if(cameraFormat2 != -1)
            cameraFiring(cameraIndex2,cameraFormat2,1);
    }
    else
    {
        if(cameraFormat1 != -1)
        {
            m_camera[0]->stop();
            // ui->display_widget0->setEnabled(false);
        }
        if(cameraFormat2 != -1)
            m_camera[1]->stop();
        camera_state = 0;
    }
}

//窗口开始显示摄像头内容
void MainWindow::cameraFiring(int i, int formatIndex, int position)
{
    QVideoWidget * display_widget = (!position)?ui->display_widget0:ui->display_widget1;
    if(list_cameras.length() <= i)
    {
        camera_state = 0;
        QMessageBox msgBox;
        msgBox.setText("打开摄像头失败");
        msgBox.exec();
        return;
    }
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
void MainWindow::recorderStart()
{
    if(recorder[0] != NULL)
        recoederChoose(0);
    if(recorder[1] != NULL)
        recoederChoose(1);
}

//保存摄像头录像
void MainWindow::recoederChoose(int i)
{
    QString videoPath;
    videoPath = Basic_Circular::getFileName() + "/" + QString::number(i) + "video.mp4";
    recorder[i]->setOutputLocation(QUrl::fromLocalFile(videoPath));
    recorder[i]->setQuality(QMediaRecorder::VeryLowQuality); //质量 LowQuality低，VeryLowQuality极低
    recorder[i]->setVideoResolution(640,480);               //分辨率
    recorder[i]->setVideoBitRate(20);                       //帧数
    recorder[i]->record();
}

//结束录制，关闭两个摄像头
void MainWindow::recorderStop()
{
    if(recorder[0] != NULL)
        recorder[0]->stop();
    if(recorder[1] != NULL)
        recorder[1]->stop();
}

//修改摄像头配置
void MainWindow::cameraSet(int cameraIndex, int formatIndex, int position)
{
    camera_state = 1;
    list_cameras = QMediaDevices::videoInputs();
    cameraFiring(cameraIndex,formatIndex,position);
}

//创建文件夹以保存数据
void MainWindow::createFolder()
{
    QDir dir(QDir::currentPath());
    Basic_Circular::setFileName();

    QString str = QDir::currentPath();
    str += "/data";
    if(!dir.exists(str))
    {
        dir.mkdir(str);
    }
    if(!dir.exists(Basic_Circular::getFileName()))
    {
        dir.mkdir(Basic_Circular::getFileName());
    }
    QString readName = Basic_Circular::getFileName() + "/read.txt";
    QString playBackName = Basic_Circular::getFileName() + "/playBack.txt";
    QString ftempName = Basic_Circular::getFileName() + "/temp.txt";
    fr = new QFile(readName);
    fp = new QFile(playBackName);
    ftemp = new QFile(ftempName);
    fr->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
    fp->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
    ftemp->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
}

//打开文件夹读取数据
void MainWindow::openFolder()
{
    //打开文件
    QFileDialog * fd = new QFileDialog(this);
    fd->setWindowTitle("选择数据文件");
    fd->setNameFilter("playBack.txt");
    fd->setViewMode(QFileDialog::Detail);
    QString filePath = "";
    QStringList list_str;
    if(fd->exec() == QDialog::Accepted)
    {
        list_str = fd->selectedFiles();
        filePath = list_str[0];
    }
    if(filePath == "")  //如果没用选择文件，则返回
        return;
    ui->textEdit_dataPath->setText(filePath);
    Basic_Circular::setFileName(filePath.chopped(13));    //保存文件夹地址
    QFile fb(filePath);
    if(!fb.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << ("打开文件失败");
    }
    txtInput = new QTextStream(&fb);
    ui->chartView_ak->chart()->removeAllSeries();   //重新选择文件之后清空坐标系
    ui->chartView_bk->chart()->removeAllSeries();
    ui->table_l_ak->setRowCount(0);
    ui->table_l_bk->setRowCount(0);
    ui->table_r_ak->setRowCount(0);
    ui->table_r_bk->setRowCount(0);

    //读取视频
    playBack_view();
    currentID = 0;

    //读取数据
    allData.clear();    //清空数据数组，否则无法重新选择文件
    QString lineStr;
    QStringList strList;
    bool position, filter;
    UINT handle = 0;
    while(!txtInput->atEnd())
    {
        lineStr = txtInput->readLine();
        strList = lineStr.split(" ");
        QStringListIterator it(strList);

        QString _str = it.next();
        if(_str == "frameHead")
        {
            position = (it.next() == "left")?0:1;
            if(position)    //单雷达时，CANID默认为左，仅在双雷达情况下会出现右
                radarCnt = 2;
            filter = (it.next() == "bk")?0:1;
            if(!filter)
            {
                playBack_time();
                playBack_VehicleStatus(position);
            }
            playBack_half(position,filter);
            handle++;
        }
        if(handle == (radarCnt * 2))
        {
            allData.append(read_frame);
            handle = 0;
        }

    }
    ui->horizontalSlider->setMaximum(allData.size() - 1);
    ui->pushButton_pb_start->setEnabled((allData.size() == 0)?false:true);
}

//打开视频
void MainWindow::playBack_view()
{
    QDir *dir = new QDir(Basic_Circular::getFileName());
    QStringList filter;
    filter<<"*.mp4";
    dir->setNameFilters(filter); //过滤文件类型
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    cameraCount = fileInfo->count();  //文件个数
    switch(cameraCount)
    {
    case 1:
        playBack_view_half(0,ui->display_widget0);
        break;
    case 2:
        playBack_view_half(0,ui->display_widget0);
        playBack_view_half(1,ui->display_widget1);
        break;
    }
}

//读取视频到video widget
void MainWindow::playBack_view_half(UINT index, QVideoWidget *v)
{
    QString viewPath = Basic_Circular::getFileName() + "/" + QString::number(index) + "video.mp4";
    QMediaPlayer * player = new QMediaPlayer();
    player->setSource(QUrl::fromLocalFile(viewPath));
    player->setVideoOutput(v);
    if(!index)
    {
        player_pb0 = player;
    }
    else
    {
        player_pb1 = player;
    }
}

//播放视频
void MainWindow::view_play()
{
    switch(cameraCount)
    {
    case 1:
        player_pb0->play();
        break;
    case 2:
        player_pb0->play();
        player_pb1->play();
        break;
    }
}

//暂停视频
void MainWindow::view_pause()
{
    switch(cameraCount)
    {
    case 1:
        player_pb0->pause();
        break;
    case 2:
        player_pb0->pause();
        player_pb1->pause();
        break;
    }
    // qDebug() << player_pb0->position();
    // qDebug() << player_pb1->position();
}

//播放当前帧所对应的视频
void MainWindow::playBack_currentID()
{
    int timeIndex = currentID;
    if(radarCnt == 2)
    {
        timeIndex *= 2; //所有雷达的帧时间保存在同一全局数组中，使用双雷达时索引需要翻倍
    }
    int currentTime = Basic_Circular::getTimeInterval(timeIndex);
    switch(cameraCount)
    {
    case 1:
        player_pb0->setPosition(currentTime);
        break;
    case 2:
        player_pb0->setPosition(currentTime);
        player_pb1->setPosition(currentTime);
        break;
    }
}

//获取视频时长，此用于函数求每帧间隔时间的平均值，现在改用系统时间，可以获得准确的间隔时间
// void MainWindow::setDuration()
// {
//     if(Basic_Circular::getFrameLength() != 50)
//         return;
//     int duration = 0;
//     float frameLength;
//     switch(cameraCount)
//     {
//     case 1:
//         duration = player_pb0->duration();
//         break;
//     case 2:
//         duration = player_pb0->duration() + player_pb1->duration();
//         duration /= 2;
//         break;
//     }
//     frameLength = (float)qRound(
//                       100 * (float)duration / allData.size()
//                       ) / 100;
//     Basic_Circular::setFrameLength(frameLength);
// }

//将txt文件中的数据读取到全局变量
void MainWindow::playBack_half(bool position, bool filter)
{
    track_measu_t f[64];
    memset(f,0,sizeof(track_measu_t)*64);

    QString lineStr;
    QStringList strList;
    int frame_number,cnt,ALERT_SIG;

    //读取此帧的第一行：帧编号，目标数，报警情况
    lineStr = txtInput->readLine();
    strList = lineStr.split(" ");
    QStringListIterator it(strList);
    frame_number = it.next().toInt();
    cnt = it.next().toInt();
    ALERT_SIG = it.next().toInt();
    for(int i = 0; i < cnt; i++)
    {
        //读取目标数据
        lineStr = txtInput->readLine();
        strList = lineStr.split(" ");
        QStringListIterator it(strList);
        f[i].target_number =  it.next().toInt();
        f[i].range = it.next().toFloat();
        f[i].velocity = it.next().toFloat();
        f[i].angle = it.next().toFloat();
        f[i].angle_e = it.next().toFloat();
        f[i].SNR = it.next().toFloat();
    }

    lineStr = txtInput->readLine();
    if(lineStr != "frameEnd")
        qDebug() << "目标丢失";

    if(position)
    {
        read_frame.fr.frame_number = frame_number;
        read_frame.fr.ALERT_SIG = ALERT_SIG;
        if(filter)
        {
            read_frame.fr.ak_cnt = cnt;
            memcpy(read_frame.fr.ak,f,sizeof(track_measu_t) *64);
        }
        else
        {
            read_frame.fr.bk_cnt = cnt;
            memcpy(read_frame.fr.bk,f,sizeof(track_measu_t) *64);
        }
    }
    else
    {
        read_frame.fl.frame_number = frame_number;
        read_frame.fl.ALERT_SIG = ALERT_SIG;
        if(filter)
        {
            read_frame.fl.ak_cnt = cnt;
            memcpy(read_frame.fl.ak,f,sizeof(track_measu_t) *64);
        }
        else
        {
            read_frame.fl.bk_cnt = cnt;
            memcpy(read_frame.fl.bk,f,sizeof(track_measu_t) *64);
        }
    }
}

//开始回放
void MainWindow::playBack_start()
{
    //用于uart串口通讯
    // QByteArray buf;
    // char BUF1[2048] = {};
    // buf = serial->readAll();
    // if(!buf.isEmpty())
    // {
    //     QString str;
    //     str=QString(buf);
    //     ui->textEdit->clear();
    //     ui->textEdit->append(str);
    //     // qDebug()<<"str:"<<str;
    //     snprintf(BUF1,2000,"%s", str.toUtf8().data());//left(index + 2)
    //     qDebug()<<"BUF1"<<BUF1;
    // }
    // buf.clear();

    currentID++;
    if(currentID == allData.size())
    {
        currentID--;
        emit playBack_over();
        currentID = 0;
        return;
    }
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    ui->horizontalSlider->setValue(currentID);
    playBack_currentID();
}

//显示下一帧
void MainWindow::playBack_next()
{
    if(currentID >= (allData.size() - 1))
        return;
    currentID++;
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    ui->horizontalSlider->setValue(currentID);
    playBack_currentID();
}

//显示下十帧
void MainWindow::playBack_next_x()
{
    if((currentID + 11) >= allData.size())
        currentID = allData.size() - 1;
    else
        currentID += 10;
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    ui->horizontalSlider->setValue(currentID);
    playBack_currentID();
}

//显示上一帧
void MainWindow::playBack_previous()
{
    if(currentID <= 0)
        return;
    currentID--;
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    ui->horizontalSlider->setValue(currentID);
    playBack_currentID();
}

//显示上十帧
void MainWindow::playBack_previous_x()
{
    if((currentID - 10) <= 0)
        currentID = 0;
    else
        currentID -=10;
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    ui->horizontalSlider->setValue(currentID);
    playBack_currentID();
}

//显示指定帧
void MainWindow::playBack_designate()
{
    UINT target = ui->lineEdit_target->text().toInt();
    currentID = (target < allData.size())?target:(allData.length() - 1);    //若输入帧ID超出范围，则改为范围内的最大值
    output(allData[currentID].fl,allData[currentID].fr);
    ui->horizontalSlider->setValue(currentID);
    ui->lineEdit_target->setText(QString::number(currentID));
    playBack_currentID();
}

//拖动滑块，显示指定帧
void MainWindow::dragSlider()
{
    currentID = ui->horizontalSlider->value();
    output(allData[currentID].fl,allData[currentID].fr);
    ui->lineEdit_target->setText(QString::number(currentID));
    playBack_currentID();
}

//打开新窗口,若主窗口已打开摄像头，会导致新窗口无法打开摄像头,尝试在此函数中析构摄像头对象
// void MainWindow::openNewWindow(newWindow *configWindow)
// {
//     // list_cameras
//     // QCamera * m_camera[2];
//     // QMediaCaptureSession my_captureSession[2];
//     // QMediaRecorder * recorder[2];
//     // if(m_camera[0] != NULL)
//     //     qDebug() << "-";
//     configWindow->show();
// }

//打开设置窗口
// void MainWindow::openSettingWindow(settingwindow *configWindow)
// {
//     configWindow->show();
// }

//读取每一帧信号输出的系统时间
void MainWindow::playBack_time()
{
    QString lineStr = txtInput->readLine();
    QStringList strList = lineStr.split(" ");
    QStringListIterator it(strList);
    int time_h = it.next().toInt();
    int time_m = it.next().toInt();
    int time_s = it.next().toInt();
    int time_z = it.next().toInt();
    int time = ((time_h * 60 + time_m) * 60 + time_s) * 1000 + time_z;
    if(startTime == 0)
        startTime = time;
    time -= startTime;
    Basic_Circular::append(time);
}

//输出车辆状态信息
void MainWindow::outVehicleStatus(frame_complete fl, frame_complete fr)
{
    // float speedInKmH = ((fl.VS.Speed - perviousW) * 7.2 / 300);
    float speedInKmH = fl.VS.Speed;
    QString carState = "velocity = " + (QString::number(speedInKmH));
    switch(fl.VS.sysfuncmode)
    {
    case 0:
        carState += "\nsysfuncmode = IDLE";
        break;
    case 1:
        carState += "\nsysfuncmode = DOA";
        break;
    case 2:
        carState += "\nsysfuncmode = LCA";
        break;
    case 3:
        carState += "\nsysfuncmode = RCTA";
        break;
    }
    carState += "\ndoorStatus    Left: " + (QString::number(fl.VS.doorStatusLeft))
                + "    Right: " + (QString::number(fr.VS.doorStatusRight));
    switch(fl.VS.Gear)
    {
    case 0:
        carState += "\nGear = P";
        break;
    case 1:
        carState += "\nGear = R";
        break;
    case 2:
        carState += "\nGear = N";
        break;
    case 3:
        carState += "\nGear = D";
        break;
    }
    carState += "\nTurnSignalStatus    Left" + (QString::number(fr.VS.ExtrLtgStsTurnIndrLe))
                + "    Right:" + (QString::number(fr.VS.ExtrLtgStsTurnIndrRi));
    ui->textEdit->setText(carState);
}

//保存车辆状态信息
void MainWindow::save_VehicleStatus(frame_complete fc)
{
    QString line_r = "",line_p = "";
    //以便于阅读的方式保存
    line_r += "\nspeed = " + QString::number(fc.VS.Speed);
    switch(fc.VS.sysfuncmode)
    {
    case 0:
        line_r += "\nsysfuncmode = SystemMode_IDLE";
        break;
    case 1:
        line_r += "\nsysfuncmode = SystemMode_DOA";
        break;
    case 2:
        line_r += "\nsysfuncmode = SystemMode_LCA";
        break;
    case 3:
        line_r += "\nsysfuncmode = SystemMode_RCTA";
        break;
    }
    line_r += "\ndoorStatusLeft = " + (QString::number(fc.VS.doorStatusLeft));
    line_r += "\ndoorStatusRight = " + (QString::number(fc.VS.doorStatusRight));
    switch(fc.VS.Gear)
    {
    case 0:
        line_r += "\nGear = P";
        break;
    case 1:
        line_r += "\nGear = R";
        break;
    case 2:
        line_r += "\nGear = N";
        break;
    case 3:
        line_r += "\nGear = D";
        break;
    }
    line_r += "\nExtrLtgStsTurnIndrLe = " + (QString::number(fc.VS.ExtrLtgStsTurnIndrLe));
    line_r += "\nExtrLtgStsTurnIndrRi = " + (QString::number(fc.VS.ExtrLtgStsTurnIndrRi));
    fr->write(line_r.toStdString().c_str());
    //以便于回放的方式保存
    line_p += QString::number(fc.VS.Speed) + " "
              + QString::number(fc.VS.sysfuncmode) + " "
              + QString::number(fc.VS.doorStatusLeft) + " "
              + QString::number(fc.VS.doorStatusRight) + " "
              + QString::number(fc.VS.Gear) + " "
              + QString::number(fc.VS.ExtrLtgStsTurnIndrLe) + " "
              + QString::number(fc.VS.ExtrLtgStsTurnIndrRi) + "\n";
    fp->write(line_p.toStdString().c_str());
}

//读取车辆状态信息
void MainWindow::playBack_VehicleStatus(bool position)
{
    VehicleStatus VS_pb;;
    QString lineStr = txtInput->readLine();
    QStringList strList = lineStr.split(" ");
    QStringListIterator it(strList);
    VS_pb.Speed = it.next().toFloat();
    VS_pb.sysfuncmode = it.next().toInt();
    VS_pb.doorStatusLeft = it.next().toInt();
    VS_pb.doorStatusRight = it.next().toInt();
    VS_pb.Gear = it.next().toInt();
    VS_pb.ExtrLtgStsTurnIndrLe = it.next().toInt();
    VS_pb.ExtrLtgStsTurnIndrLe = it.next().toInt();
    if(position)
        read_frame.fl.VS = VS_pb;
    else
        read_frame.fr.VS = VS_pb;
}

//蜂鸣器
void MainWindow::buzzerOut(UINT ALERT_SIG, bool position)
{
    QPushButton * pushButton_alert;
    int audioPlayerStatus = 0;
    if(!position)
    {
        // audioPlayerStatus = audioPlayerStatus_l;
        pushButton_alert = ui->ALERT_SIG_l;
    }
    else
    {
        // audioPlayerStatus = audioPlayerStatus_r;
        pushButton_alert = ui->ALERT_SIG_r;
    }

    switch(ALERT_SIG)
    {
    case 0:
    {
        audioPlayerStatus = 0;
        pushButton_alert->setStyleSheet("background: rgb(0,255,0)");
        break;
    }
    case 1:
    {
        audioPlayerStatus = 1;
        pushButton_alert->setStyleSheet("background: yellow");
        break;
    }
    case 3:
    {
        audioPlayerStatus = 3;
        pushButton_alert->setStyleSheet("background: red");
        break;
    }
    }

    if(!position)
    {
        audioPlayerStatus_l = audioPlayerStatus;
    }
    else
    {
        audioPlayerStatus_r = audioPlayerStatus;
    }

    if(audioPlayerStatus_l == 0 && audioPlayerStatus_r == 0)
    {
        audioPlayer->stop();
        pathStatus = 0;
    }
    else if(audioPlayerStatus_l == 3 || audioPlayerStatus_r == 3)
    {
        if(pathStatus != 3)
        {
            pathStatus = 3;
            QString path = "C:/Qt/qtProject/can/06/audio/buzzer on.mp3";
            audioPlayer->setSource(QUrl::fromLocalFile(path));
            audioPlayer->play();
        }
    }
    else
    {
        if(pathStatus != 1)
        {
            pathStatus = 1;
            QString path = "C:/Qt/qtProject/can/06/audio/buzzer flash.mp3";
            audioPlayer->setSource(QUrl::fromLocalFile(path));
            audioPlayer->play();
        }
    }
}
