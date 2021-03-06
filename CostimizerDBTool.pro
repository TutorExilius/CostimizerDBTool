#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T19:35:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CostimizerDBTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    db_dataprovider.cpp \
    discounter.cpp \
    discountershopitem.cpp \
    shopitem.cpp \
    config.cpp \
    shopitemdialog.cpp \
    discounterdialog.cpp \
    configdialog.cpp \
    customaboutdialog.cpp

HEADERS += \
        mainwindow.h \
    db_dataprovider.h \
    discounter.h \
    discountershopitem.h \
    shopitem.h \
    config.h \
    shopitemdialog.h \
    discounterdialog.h \
    configdialog.h \
    customaboutdialog.h

FORMS += \
        mainwindow.ui \
    shopitemdialog.ui \
    discounterdialog.ui \
    configdialog.ui \
    customaboutdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
