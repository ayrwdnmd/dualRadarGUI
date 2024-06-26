/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_dataOut;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_left;
    QVBoxLayout *verticalLayout_8;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ALERT_SIG_l;
    QPushButton *ALERT_SIG_r;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_6;
    QChartView *chartView_ak;
    QChartView *chartView_bk;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QTableWidget *table_l_ak;
    QTableWidget *table_r_ak;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *table_l_bk;
    QTableWidget *table_r_bk;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_start;
    QPushButton *pushButton_camera;
    QPushButton *pushButton_setting;
    QPushButton *pushButton_floating;
    QWidget *widget_10;
    QPushButton *pushButton_dataPath;
    QTextEdit *textEdit_dataPath;
    QWidget *widget_8;
    QVBoxLayout *verticalLayout_5;
    QSlider *horizontalSlider;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_pb_rewind;
    QPushButton *pushButton_pb_previon;
    QPushButton *pushButton_pb_start;
    QPushButton *pushButton_pb_next;
    QPushButton *pushButton_pb_forward;
    QLineEdit *lineEdit_target;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_14;
    QTextEdit *textEdit;
    QPushButton *pushButton_bk;
    QPushButton *pushButton_ak;
    QVideoWidget *display_widget0;
    QVideoWidget *display_widget1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 851);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        widget_dataOut = new QWidget(centralwidget);
        widget_dataOut->setObjectName("widget_dataOut");
        horizontalLayout = new QHBoxLayout(widget_dataOut);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_left = new QWidget(widget_dataOut);
        widget_left->setObjectName("widget_left");
        verticalLayout_8 = new QVBoxLayout(widget_left);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_11 = new QWidget(widget_left);
        widget_11->setObjectName("widget_11");
        horizontalLayout_5 = new QHBoxLayout(widget_11);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        ALERT_SIG_l = new QPushButton(widget_11);
        ALERT_SIG_l->setObjectName("ALERT_SIG_l");

        horizontalLayout_5->addWidget(ALERT_SIG_l);

        ALERT_SIG_r = new QPushButton(widget_11);
        ALERT_SIG_r->setObjectName("ALERT_SIG_r");

        horizontalLayout_5->addWidget(ALERT_SIG_r);


        verticalLayout_8->addWidget(widget_11);

        widget_13 = new QWidget(widget_left);
        widget_13->setObjectName("widget_13");
        horizontalLayout_7 = new QHBoxLayout(widget_13);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_12 = new QWidget(widget_13);
        widget_12->setObjectName("widget_12");
        verticalLayout_6 = new QVBoxLayout(widget_12);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        chartView_ak = new QChartView(widget_12);
        chartView_ak->setObjectName("chartView_ak");

        verticalLayout_6->addWidget(chartView_ak);

        chartView_bk = new QChartView(widget_12);
        chartView_bk->setObjectName("chartView_bk");

        verticalLayout_6->addWidget(chartView_bk);


        horizontalLayout_7->addWidget(widget_12);

        widget_3 = new QWidget(widget_13);
        widget_3->setObjectName("widget_3");
        widget_3->setMinimumSize(QSize(472, 0));
        widget_3->setMaximumSize(QSize(472, 16777215));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        table_l_ak = new QTableWidget(widget_6);
        table_l_ak->setObjectName("table_l_ak");
        table_l_ak->setMaximumSize(QSize(236, 16777215));

        horizontalLayout_6->addWidget(table_l_ak);

        table_r_ak = new QTableWidget(widget_6);
        table_r_ak->setObjectName("table_r_ak");
        table_r_ak->setMaximumSize(QSize(236, 16777215));

        horizontalLayout_6->addWidget(table_r_ak);


        verticalLayout_3->addWidget(widget_6);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        widget_2->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        table_l_bk = new QTableWidget(widget_2);
        table_l_bk->setObjectName("table_l_bk");
        table_l_bk->setMinimumSize(QSize(0, 0));
        table_l_bk->setMaximumSize(QSize(236, 16777215));

        horizontalLayout_2->addWidget(table_l_bk);

        table_r_bk = new QTableWidget(widget_2);
        table_r_bk->setObjectName("table_r_bk");
        table_r_bk->setMinimumSize(QSize(0, 0));
        table_r_bk->setMaximumSize(QSize(236, 16777215));

        horizontalLayout_2->addWidget(table_r_bk);


        verticalLayout_3->addWidget(widget_2);


        horizontalLayout_7->addWidget(widget_3);


        verticalLayout_8->addWidget(widget_13);


        horizontalLayout->addWidget(widget_left);

        widget = new QWidget(widget_dataOut);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(360, 16777215));
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        widget_4->setMinimumSize(QSize(360, 160));
        widget_4->setMaximumSize(QSize(360, 200));
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QWidget(widget_4);
        widget_9->setObjectName("widget_9");
        widget_9->setMaximumSize(QSize(360, 16777215));
        horizontalLayout_4 = new QHBoxLayout(widget_9);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_start = new QPushButton(widget_9);
        pushButton_start->setObjectName("pushButton_start");

        horizontalLayout_4->addWidget(pushButton_start);

        pushButton_camera = new QPushButton(widget_9);
        pushButton_camera->setObjectName("pushButton_camera");

        horizontalLayout_4->addWidget(pushButton_camera);

        pushButton_setting = new QPushButton(widget_9);
        pushButton_setting->setObjectName("pushButton_setting");

        horizontalLayout_4->addWidget(pushButton_setting);

        pushButton_floating = new QPushButton(widget_9);
        pushButton_floating->setObjectName("pushButton_floating");

        horizontalLayout_4->addWidget(pushButton_floating);


        verticalLayout_4->addWidget(widget_9);

        widget_10 = new QWidget(widget_4);
        widget_10->setObjectName("widget_10");
        widget_10->setMaximumSize(QSize(360, 16777215));
        pushButton_dataPath = new QPushButton(widget_10);
        pushButton_dataPath->setObjectName("pushButton_dataPath");
        pushButton_dataPath->setGeometry(QRect(0, 10, 80, 28));
        pushButton_dataPath->setMaximumSize(QSize(80, 16777215));
        textEdit_dataPath = new QTextEdit(widget_10);
        textEdit_dataPath->setObjectName("textEdit_dataPath");
        textEdit_dataPath->setGeometry(QRect(80, 0, 280, 51));
        textEdit_dataPath->setMaximumSize(QSize(280, 16777215));

        verticalLayout_4->addWidget(widget_10);

        widget_8 = new QWidget(widget_4);
        widget_8->setObjectName("widget_8");
        widget_8->setMaximumSize(QSize(16777215, 30));
        verticalLayout_5 = new QVBoxLayout(widget_8);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(widget_8);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMaximumSize(QSize(360, 16777215));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(horizontalSlider);


        verticalLayout_4->addWidget(widget_8);

        widget_7 = new QWidget(widget_4);
        widget_7->setObjectName("widget_7");
        widget_7->setMaximumSize(QSize(360, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget_7);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_pb_rewind = new QPushButton(widget_7);
        pushButton_pb_rewind->setObjectName("pushButton_pb_rewind");

        horizontalLayout_3->addWidget(pushButton_pb_rewind);

        pushButton_pb_previon = new QPushButton(widget_7);
        pushButton_pb_previon->setObjectName("pushButton_pb_previon");

        horizontalLayout_3->addWidget(pushButton_pb_previon);

        pushButton_pb_start = new QPushButton(widget_7);
        pushButton_pb_start->setObjectName("pushButton_pb_start");

        horizontalLayout_3->addWidget(pushButton_pb_start);

        pushButton_pb_next = new QPushButton(widget_7);
        pushButton_pb_next->setObjectName("pushButton_pb_next");

        horizontalLayout_3->addWidget(pushButton_pb_next);

        pushButton_pb_forward = new QPushButton(widget_7);
        pushButton_pb_forward->setObjectName("pushButton_pb_forward");

        horizontalLayout_3->addWidget(pushButton_pb_forward);

        lineEdit_target = new QLineEdit(widget_7);
        lineEdit_target->setObjectName("lineEdit_target");
        lineEdit_target->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(lineEdit_target);


        verticalLayout_4->addWidget(widget_7);


        verticalLayout_7->addWidget(widget_4);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        widget_5->setMinimumSize(QSize(0, 0));
        widget_5->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget_5);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_14 = new QWidget(widget_5);
        widget_14->setObjectName("widget_14");
        widget_14->setMinimumSize(QSize(0, 90));
        widget_14->setMaximumSize(QSize(16777215, 90));
        textEdit = new QTextEdit(widget_14);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 0, 251, 90));
        textEdit->setMinimumSize(QSize(0, 90));
        textEdit->setMaximumSize(QSize(360, 90));
        pushButton_bk = new QPushButton(widget_14);
        pushButton_bk->setObjectName("pushButton_bk");
        pushButton_bk->setGeometry(QRect(260, 0, 93, 28));
        pushButton_ak = new QPushButton(widget_14);
        pushButton_ak->setObjectName("pushButton_ak");
        pushButton_ak->setGeometry(QRect(260, 30, 93, 28));

        verticalLayout_2->addWidget(widget_14);

        display_widget0 = new QVideoWidget(widget_5);
        display_widget0->setObjectName("display_widget0");
        display_widget0->setMinimumSize(QSize(360, 270));
        display_widget0->setMaximumSize(QSize(360, 270));

        verticalLayout_2->addWidget(display_widget0);

        display_widget1 = new QVideoWidget(widget_5);
        display_widget1->setObjectName("display_widget1");
        display_widget1->setMinimumSize(QSize(360, 270));
        display_widget1->setMaximumSize(QSize(360, 270));

        verticalLayout_2->addWidget(display_widget1);


        verticalLayout_7->addWidget(widget_5);


        horizontalLayout->addWidget(widget);


        verticalLayout->addWidget(widget_dataOut);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ALERT_SIG_l->setText(QString());
        ALERT_SIG_r->setText(QString());
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        pushButton_camera->setText(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        pushButton_setting->setText(QCoreApplication::translate("MainWindow", "setting", nullptr));
        pushButton_floating->setText(QCoreApplication::translate("MainWindow", "Floating", nullptr));
        pushButton_dataPath->setText(QCoreApplication::translate("MainWindow", "dataPath", nullptr));
        pushButton_pb_rewind->setText(QCoreApplication::translate("MainWindow", "-10", nullptr));
        pushButton_pb_previon->setText(QCoreApplication::translate("MainWindow", "-1", nullptr));
        pushButton_pb_start->setText(QString());
        pushButton_pb_next->setText(QCoreApplication::translate("MainWindow", "+1", nullptr));
        pushButton_pb_forward->setText(QCoreApplication::translate("MainWindow", "+10", nullptr));
        pushButton_bk->setText(QCoreApplication::translate("MainWindow", "bk hide", nullptr));
        pushButton_ak->setText(QCoreApplication::translate("MainWindow", "ak hide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
