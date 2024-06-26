/********************************************************************************
** Form generated from reading UI file 'newwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWINDOW_H
#define UI_NEWWINDOW_H

#include <QtCore/QVariant>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QPushButton *pushButton_start;
    QPushButton *pushButton_camera;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QVideoWidget *display_widget3;
    QVideoWidget *display_widget2;

    void setupUi(QWidget *newWindow)
    {
        if (newWindow->objectName().isEmpty())
            newWindow->setObjectName("newWindow");
        newWindow->resize(698, 465);
        verticalLayout = new QVBoxLayout(newWindow);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(newWindow);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));
        pushButton_start = new QPushButton(widget);
        pushButton_start->setObjectName("pushButton_start");
        pushButton_start->setGeometry(QRect(10, 0, 93, 28));
        pushButton_camera = new QPushButton(widget);
        pushButton_camera->setObjectName("pushButton_camera");
        pushButton_camera->setGeometry(QRect(580, 0, 93, 28));

        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(newWindow);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        display_widget3 = new QVideoWidget(widget_2);
        display_widget3->setObjectName("display_widget3");

        horizontalLayout->addWidget(display_widget3);

        display_widget2 = new QVideoWidget(widget_2);
        display_widget2->setObjectName("display_widget2");

        horizontalLayout->addWidget(display_widget2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addWidget(widget_2);


        retranslateUi(newWindow);

        QMetaObject::connectSlotsByName(newWindow);
    } // setupUi

    void retranslateUi(QWidget *newWindow)
    {
        newWindow->setWindowTitle(QCoreApplication::translate("newWindow", "Form", nullptr));
        pushButton_start->setText(QCoreApplication::translate("newWindow", "start", nullptr));
        pushButton_camera->setText(QCoreApplication::translate("newWindow", "camera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newWindow: public Ui_newWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWINDOW_H
