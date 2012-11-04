#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T10:24:03
#
#-------------------------------------------------

TARGET = QCvImageWindow
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qcvimagewindow.cpp

HEADERS += qcvimagewindow.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
