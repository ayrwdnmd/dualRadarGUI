/********************************************************************************
** Form generated from reading UI file 'settingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWINDOW_H
#define UI_SETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingwindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_chart;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_max_Xaxis;
    QLineEdit *lineEdit_max_Xaxis;
    QLabel *label_min_Xaxis;
    QLineEdit *lineEdit_min_Xaxis;
    QLabel *label_max_Yaxis;
    QLineEdit *lineEdit_max_Yaxis;
    QLabel *label_min_Yaxis;
    QLineEdit *lineEdit_min_Yaxis;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_pointSize;
    QLineEdit *lineEdit_pointSize;
    QLabel *label_fontSize;
    QLineEdit *lineEdit_fontSize;
    QLabel *label_colWidth;
    QLineEdit *lineEdit_colWidth;
    QLabel *label_radarCnt;
    QLineEdit *lineEdit_radarCnt;
    QWidget *widget_3;
    QLabel *label_carWidth;
    QLineEdit *lineEdit_carWidth;
    QLabel *label_carLenght;
    QLineEdit *lineEdit_carLenght;
    QWidget *tab_mode;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton_LCA;
    QRadioButton *radioButton_HDS;
    QRadioButton *radioButton_AUTODOOR;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox_chartUp;
    QComboBox *comboBox_chartDown;
    QWidget *tab_camera;
    QComboBox *comboBox_camera_1;
    QComboBox *comboBox_format_1;
    QComboBox *comboBox_camera_2;
    QComboBox *comboBox_format_2;
    QPushButton *pushButton_refresh;
    QPushButton *pushButton_save;

    void setupUi(QWidget *settingwindow)
    {
        if (settingwindow->objectName().isEmpty())
            settingwindow->setObjectName("settingwindow");
        settingwindow->resize(600, 400);
        tabWidget = new QTabWidget(settingwindow);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(11, 11, 571, 350));
        tab_chart = new QWidget();
        tab_chart->setObjectName("tab_chart");
        widget = new QWidget(tab_chart);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 10, 555, 47));
        widget->setMaximumSize(QSize(600, 16777215));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 11, -1, -1);
        label_max_Xaxis = new QLabel(widget);
        label_max_Xaxis->setObjectName("label_max_Xaxis");
        label_max_Xaxis->setMinimumSize(QSize(70, 0));
        label_max_Xaxis->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label_max_Xaxis);

        lineEdit_max_Xaxis = new QLineEdit(widget);
        lineEdit_max_Xaxis->setObjectName("lineEdit_max_Xaxis");
        lineEdit_max_Xaxis->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineEdit_max_Xaxis);

        label_min_Xaxis = new QLabel(widget);
        label_min_Xaxis->setObjectName("label_min_Xaxis");
        label_min_Xaxis->setMinimumSize(QSize(70, 0));
        label_min_Xaxis->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label_min_Xaxis);

        lineEdit_min_Xaxis = new QLineEdit(widget);
        lineEdit_min_Xaxis->setObjectName("lineEdit_min_Xaxis");
        lineEdit_min_Xaxis->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineEdit_min_Xaxis);

        label_max_Yaxis = new QLabel(widget);
        label_max_Yaxis->setObjectName("label_max_Yaxis");
        label_max_Yaxis->setMinimumSize(QSize(70, 0));
        label_max_Yaxis->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label_max_Yaxis);

        lineEdit_max_Yaxis = new QLineEdit(widget);
        lineEdit_max_Yaxis->setObjectName("lineEdit_max_Yaxis");
        lineEdit_max_Yaxis->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineEdit_max_Yaxis);

        label_min_Yaxis = new QLabel(widget);
        label_min_Yaxis->setObjectName("label_min_Yaxis");
        label_min_Yaxis->setMinimumSize(QSize(70, 0));
        label_min_Yaxis->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(label_min_Yaxis);

        lineEdit_min_Yaxis = new QLineEdit(widget);
        lineEdit_min_Yaxis->setObjectName("lineEdit_min_Yaxis");
        lineEdit_min_Yaxis->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lineEdit_min_Yaxis);

        widget_2 = new QWidget(tab_chart);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 60, 555, 47));
        widget_2->setMaximumSize(QSize(600, 16777215));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_pointSize = new QLabel(widget_2);
        label_pointSize->setObjectName("label_pointSize");
        label_pointSize->setMinimumSize(QSize(70, 0));
        label_pointSize->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(label_pointSize);

        lineEdit_pointSize = new QLineEdit(widget_2);
        lineEdit_pointSize->setObjectName("lineEdit_pointSize");
        lineEdit_pointSize->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(lineEdit_pointSize);

        label_fontSize = new QLabel(widget_2);
        label_fontSize->setObjectName("label_fontSize");
        label_fontSize->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(label_fontSize);

        lineEdit_fontSize = new QLineEdit(widget_2);
        lineEdit_fontSize->setObjectName("lineEdit_fontSize");
        lineEdit_fontSize->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(lineEdit_fontSize);

        label_colWidth = new QLabel(widget_2);
        label_colWidth->setObjectName("label_colWidth");
        label_colWidth->setMinimumSize(QSize(70, 0));
        label_colWidth->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(label_colWidth);

        lineEdit_colWidth = new QLineEdit(widget_2);
        lineEdit_colWidth->setObjectName("lineEdit_colWidth");
        lineEdit_colWidth->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(lineEdit_colWidth);

        label_radarCnt = new QLabel(widget_2);
        label_radarCnt->setObjectName("label_radarCnt");
        label_radarCnt->setMinimumSize(QSize(70, 0));
        label_radarCnt->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(label_radarCnt);

        lineEdit_radarCnt = new QLineEdit(widget_2);
        lineEdit_radarCnt->setObjectName("lineEdit_radarCnt");
        lineEdit_radarCnt->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(lineEdit_radarCnt);

        widget_3 = new QWidget(tab_chart);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(0, 110, 555, 47));
        widget_3->setMaximumSize(QSize(600, 16777215));
        label_carWidth = new QLabel(widget_3);
        label_carWidth->setObjectName("label_carWidth");
        label_carWidth->setGeometry(QRect(11, 11, 70, 19));
        label_carWidth->setMinimumSize(QSize(70, 0));
        label_carWidth->setMaximumSize(QSize(70, 16777215));
        lineEdit_carWidth = new QLineEdit(widget_3);
        lineEdit_carWidth->setObjectName("lineEdit_carWidth");
        lineEdit_carWidth->setGeometry(QRect(88, 11, 50, 25));
        lineEdit_carWidth->setMaximumSize(QSize(50, 16777215));
        label_carLenght = new QLabel(widget_3);
        label_carLenght->setObjectName("label_carLenght");
        label_carLenght->setGeometry(QRect(145, 11, 70, 25));
        label_carLenght->setMinimumSize(QSize(70, 0));
        label_carLenght->setMaximumSize(QSize(70, 16777215));
        lineEdit_carLenght = new QLineEdit(widget_3);
        lineEdit_carLenght->setObjectName("lineEdit_carLenght");
        lineEdit_carLenght->setGeometry(QRect(222, 11, 50, 25));
        lineEdit_carLenght->setMaximumSize(QSize(50, 16777215));
        tabWidget->addTab(tab_chart, QString());
        tab_mode = new QWidget();
        tab_mode->setObjectName("tab_mode");
        widget_4 = new QWidget(tab_mode);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(10, 10, 266, 47));
        widget_4->setMaximumSize(QSize(600, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        radioButton_LCA = new QRadioButton(widget_4);
        radioButton_LCA->setObjectName("radioButton_LCA");

        horizontalLayout_3->addWidget(radioButton_LCA);

        radioButton_HDS = new QRadioButton(widget_4);
        radioButton_HDS->setObjectName("radioButton_HDS");

        horizontalLayout_3->addWidget(radioButton_HDS);

        radioButton_AUTODOOR = new QRadioButton(widget_4);
        radioButton_AUTODOOR->setObjectName("radioButton_AUTODOOR");

        horizontalLayout_3->addWidget(radioButton_AUTODOOR);

        widget_5 = new QWidget(tab_mode);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(0, 60, 555, 47));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        comboBox_chartUp = new QComboBox(widget_5);
        comboBox_chartUp->setObjectName("comboBox_chartUp");

        horizontalLayout_4->addWidget(comboBox_chartUp);

        comboBox_chartDown = new QComboBox(widget_5);
        comboBox_chartDown->setObjectName("comboBox_chartDown");

        horizontalLayout_4->addWidget(comboBox_chartDown);

        tabWidget->addTab(tab_mode, QString());
        tab_camera = new QWidget();
        tab_camera->setObjectName("tab_camera");
        comboBox_camera_1 = new QComboBox(tab_camera);
        comboBox_camera_1->setObjectName("comboBox_camera_1");
        comboBox_camera_1->setGeometry(QRect(20, 20, 150, 25));
        comboBox_format_1 = new QComboBox(tab_camera);
        comboBox_format_1->setObjectName("comboBox_format_1");
        comboBox_format_1->setGeometry(QRect(190, 20, 371, 25));
        comboBox_camera_2 = new QComboBox(tab_camera);
        comboBox_camera_2->setObjectName("comboBox_camera_2");
        comboBox_camera_2->setGeometry(QRect(20, 60, 150, 25));
        comboBox_format_2 = new QComboBox(tab_camera);
        comboBox_format_2->setObjectName("comboBox_format_2");
        comboBox_format_2->setGeometry(QRect(190, 60, 371, 25));
        pushButton_refresh = new QPushButton(tab_camera);
        pushButton_refresh->setObjectName("pushButton_refresh");
        pushButton_refresh->setGeometry(QRect(40, 100, 93, 28));
        tabWidget->addTab(tab_camera, QString());
        pushButton_save = new QPushButton(settingwindow);
        pushButton_save->setObjectName("pushButton_save");
        pushButton_save->setGeometry(QRect(480, 360, 93, 28));

        retranslateUi(settingwindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settingwindow);
    } // setupUi

    void retranslateUi(QWidget *settingwindow)
    {
        settingwindow->setWindowTitle(QCoreApplication::translate("settingwindow", "setting", nullptr));
        label_max_Xaxis->setText(QCoreApplication::translate("settingwindow", "maxXaxis", nullptr));
        label_min_Xaxis->setText(QCoreApplication::translate("settingwindow", "minXaxis", nullptr));
        label_max_Yaxis->setText(QCoreApplication::translate("settingwindow", "maxYaxis", nullptr));
        label_min_Yaxis->setText(QCoreApplication::translate("settingwindow", "min_Yaxis", nullptr));
        label_pointSize->setText(QCoreApplication::translate("settingwindow", "pointSize", nullptr));
        label_fontSize->setText(QCoreApplication::translate("settingwindow", "fontSize", nullptr));
        label_colWidth->setText(QCoreApplication::translate("settingwindow", "ColWidth", nullptr));
        label_radarCnt->setText(QCoreApplication::translate("settingwindow", "radarCnt", nullptr));
        label_carWidth->setText(QCoreApplication::translate("settingwindow", "carWidth", nullptr));
        label_carLenght->setText(QCoreApplication::translate("settingwindow", "carLenght", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_chart), QCoreApplication::translate("settingwindow", "chart", nullptr));
        radioButton_LCA->setText(QCoreApplication::translate("settingwindow", "LCA", nullptr));
        radioButton_HDS->setText(QCoreApplication::translate("settingwindow", "HDS", nullptr));
        radioButton_AUTODOOR->setText(QCoreApplication::translate("settingwindow", "AUTODOOR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_mode), QCoreApplication::translate("settingwindow", "mode", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("settingwindow", "refresh", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_camera), QCoreApplication::translate("settingwindow", "camera", nullptr));
        pushButton_save->setText(QCoreApplication::translate("settingwindow", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingwindow: public Ui_settingwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
