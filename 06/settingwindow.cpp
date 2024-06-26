#include "settingwindow.h"
#include "ui_settingwindow.h"

settingwindow::settingwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::settingwindow)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    layout();
    loadConfig();

    connect(ui->comboBox_camera_1,&QComboBox::activated,this,[this](){
        showFormatList(ui->comboBox_camera_1->currentIndex(),0);
    });
    connect(ui->comboBox_camera_2,&QComboBox::activated,this,[this](){
        showFormatList(ui->comboBox_camera_2->currentIndex(),1);
    });
    connect(ui->comboBox_format_1,&QComboBox::activated,this,[this](){
        emit selectCamera(ui->comboBox_camera_1->currentIndex(),ui->comboBox_format_1->currentIndex(),0);
    });
    connect(ui->comboBox_format_2,&QComboBox::activated,this,[this](){
        emit selectCamera(ui->comboBox_camera_2->currentIndex(),ui->comboBox_format_2->currentIndex(),1);
    });
    connect(ui->pushButton_refresh,&QPushButton::clicked,this,&settingwindow::showCameraList);
    connect(ui->pushButton_save,&QPushButton::clicked,this,&settingwindow::saveConfig);

    connect(modeGroup,&QButtonGroup::idClicked,this,&settingwindow::showChartList);
}

settingwindow::~settingwindow()
{
    delete ui;
}

//设计布局
void settingwindow::layout()
{
    //将单选按钮加入同一组
    modeGroup->addButton(ui->radioButton_LCA, 0);
    modeGroup->addButton(ui->radioButton_HDS, 1);
    modeGroup->addButton(ui->radioButton_AUTODOOR, 2);
    // modeGroup->button(Basic_Circular::getConfigArr(13).toInt())->setChecked(true);
}

//提供图表输出选择
void settingwindow::showChartList(int mode)
{
    ui->comboBox_chartUp->clear();
    ui->comboBox_chartDown->clear();
    ui->comboBox_chartUp->addItem("hide");
    ui->comboBox_chartDown->addItem("hide");
    QString str = "BK AK BK_X-Y BK_Z-Y AK_X-Y AK_Z-Y";
    QStringList strList = str.split(" ");
    if(mode != 1)   //当功能未选择HDS时，只需要显示BK/AK
    {
        ui->comboBox_chartUp->addItem(strList[0]);
        ui->comboBox_chartDown->addItem(strList[1]);
    }
    else            //当功能选择HDS时，需要显示BK/AK以及X-Y/Z-Y
    {
        ui->comboBox_chartUp->addItem(strList[2]);
        ui->comboBox_chartUp->addItem(strList[3]);
        ui->comboBox_chartDown->addItem(strList[4]);
        ui->comboBox_chartDown->addItem(strList[5]);
    }
    ui->comboBox_chartUp->setCurrentIndex(1);   //默认选择bk/ak,而非隐藏
    ui->comboBox_chartDown->setCurrentIndex(1);
}

//提供摄像头选择
void settingwindow::showCameraList()
{
    list_cameras.clear();
    list_cameras = QMediaDevices::videoInputs();
    ui->comboBox_camera_1->clear();
    ui->comboBox_camera_2->clear();
    for(int i = 0; i < list_cameras.length(); i++)
    {
        QString str = list_cameras[i].description();
        ui->comboBox_camera_1->addItem(str);
        ui->comboBox_camera_2->addItem(str);
    }
}

//提供摄像头配置选择
void settingwindow::showFormatList(int index, bool position)
{
    QComboBox * comboBoxFormat;
    comboBoxFormat = (!position)?ui->comboBox_format_1:ui->comboBox_format_2;
    comboBoxFormat->clear();
    QList<QCameraFormat> list_format = list_cameras[index].videoFormats();
    for(int i = 0; i < list_format.length(); i++)
    {
        QString str = QString("resolution:(%1,%2), pixelFormat:%3, FrameRate:%4")
                          .arg(list_format[i].resolution().width())
                          .arg(list_format[i].resolution().height())
                          .arg(list_format[i].pixelFormat())
                          .arg(list_format[i].minFrameRate());
        comboBoxFormat->addItem(str);
    }
}

//保存设置
void settingwindow::saveConfig()
{
    QString configFile = QDir::currentPath() + "/config/config_init.ini";
    QSettings *configIniWrite = new QSettings(configFile, QSettings::IniFormat);
    configIniWrite->clear();
    Basic_Circular::setConfigArr(0, ui->lineEdit_max_Xaxis->text());
    Basic_Circular::setConfigArr(1, ui->lineEdit_min_Xaxis->text());
    Basic_Circular::setConfigArr(2, ui->lineEdit_max_Yaxis->text());
    Basic_Circular::setConfigArr(3, ui->lineEdit_min_Yaxis->text());
    Basic_Circular::setConfigArr(4, ui->lineEdit_pointSize->text());
    Basic_Circular::setConfigArr(5, ui->lineEdit_fontSize->text());
    Basic_Circular::setConfigArr(6, ui->lineEdit_colWidth->text());
    Basic_Circular::setConfigArr(7, ui->lineEdit_carWidth->text());
    Basic_Circular::setConfigArr(8, ui->lineEdit_carLenght->text());

    configIniWrite->setValue("map/max_Xaxis", Basic_Circular::getConfigArr(0));
    configIniWrite->setValue("map/min_Xaxis", Basic_Circular::getConfigArr(1));
    configIniWrite->setValue("map/max_Yaxis", Basic_Circular::getConfigArr(2));
    configIniWrite->setValue("map/min_Yaxis", Basic_Circular::getConfigArr(3));
    configIniWrite->setValue("table/PointSize", Basic_Circular::getConfigArr(4));
    configIniWrite->setValue("table/FontSize", Basic_Circular::getConfigArr(5));
    configIniWrite->setValue("table/ColumnWidth", Basic_Circular::getConfigArr(6));
    configIniWrite->setValue("car/width", Basic_Circular::getConfigArr(7));
    configIniWrite->setValue("car/lenght", Basic_Circular::getConfigArr(8));

    //当未选择任何摄像头时，description函数会导致程序崩溃
    if(ui->comboBox_camera_1->currentIndex() != -1)
    {
        Basic_Circular::setConfigArr(9, list_cameras[ui->comboBox_camera_1->currentIndex()].description());
        Basic_Circular::setConfigArr(10, QString::number(ui->comboBox_format_1->currentIndex()));
        configIniWrite->setValue("camera/camera_1", Basic_Circular::getConfigArr(9));
        configIniWrite->setValue("camera/format_1", Basic_Circular::getConfigArr(10));
    }
    if(ui->comboBox_camera_2->currentIndex() != -1)
    {
        Basic_Circular::setConfigArr(11, list_cameras[ui->comboBox_camera_2->currentIndex()].description());
        Basic_Circular::setConfigArr(12, QString::number(ui->comboBox_format_2->currentIndex()));
        configIniWrite->setValue("camera/camera_2", Basic_Circular::getConfigArr(11));
        configIniWrite->setValue("camera/format_2", Basic_Circular::getConfigArr(12));
    }

    Basic_Circular::setConfigArr(13, QString::number(modeGroup->checkedId()));
    Basic_Circular::setConfigArr(14, QString::number(ui->comboBox_chartUp->currentIndex()));
    Basic_Circular::setConfigArr(15, QString::number(ui->comboBox_chartDown->currentIndex()));
    configIniWrite->setValue("mode/mode", Basic_Circular::getConfigArr(13));
    configIniWrite->setValue("mode/chart_up", Basic_Circular::getConfigArr(14));
    configIniWrite->setValue("mode/chart_down", Basic_Circular::getConfigArr(15));

    emit click_save();
    this->close();
}

//加载设置
void settingwindow::loadConfig()
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
    ui->lineEdit_max_Xaxis->setText(Basic_Circular::getConfigArr(0));
    ui->lineEdit_min_Xaxis->setText(Basic_Circular::getConfigArr(1));
    ui->lineEdit_max_Yaxis->setText(Basic_Circular::getConfigArr(2));
    ui->lineEdit_min_Yaxis->setText(Basic_Circular::getConfigArr(3));
    ui->lineEdit_pointSize->setText(Basic_Circular::getConfigArr(4));
    ui->lineEdit_fontSize->setText(Basic_Circular::getConfigArr(5));
    ui->lineEdit_colWidth->setText(Basic_Circular::getConfigArr(6));
    ui->lineEdit_carWidth->setText(Basic_Circular::getConfigArr(7));
    ui->lineEdit_carLenght->setText(Basic_Circular::getConfigArr(8));

    showCameraList();
    for(int i = 0; i < list_cameras.length(); i++)
    {
        if(Basic_Circular::getConfigArr(9) == list_cameras[i].description())
        {
            ui->comboBox_camera_1->setCurrentIndex(i);
            showFormatList(i,0);
            ui->comboBox_format_1->setCurrentIndex(Basic_Circular::getConfigArr(10).toInt());
        }
        if(Basic_Circular::getConfigArr(11) == list_cameras[i].description())
        {
            ui->comboBox_camera_2->setCurrentIndex(i);
            showFormatList(i,1);
            ui->comboBox_format_2->setCurrentIndex(Basic_Circular::getConfigArr(12).toInt());
        }
    }

    showChartList(Basic_Circular::getConfigArr(13).toInt());
    modeGroup->button(Basic_Circular::getConfigArr(13).toInt())->setChecked(true);
    ui->comboBox_chartUp->setCurrentIndex(Basic_Circular::getConfigArr(14).toInt());
    ui->comboBox_chartDown->setCurrentIndex(Basic_Circular::getConfigArr(15).toInt());
}
