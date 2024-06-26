QT       += core gui
QT       += charts
QT       += sql
QT       += multimedia
QT       += multimediawidgets
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basic_circular.cpp \
    canthread.cpp \
    main.cpp \
    mainwindow.cpp \
    newwindow.cpp \
    settingwindow.cpp

HEADERS += \
    ControlCAN.h \
    basic_circular.h \
    canthread.h \
    mainwindow.h \
    newwindow.h \
    settingwindow.h

FORMS += \
    mainwindow.ui \
    newwindow.ui \
    settingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LC:/Qt/qtProject/can/06/ -lControlCAN

DISTFILES +=

RESOURCES += \
    pic.qrc
