#-------------------------------------------------
#
# Project created by QtCreator 2014-11-18T10:29:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nextday
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    lunar.cpp

HEADERS  += widget.h \
    lunar.h

FORMS    += widget.ui

RESOURCES += \
    Resource.qrc

OTHER_FILES += \
    ICOX.rc

RC_FILE += ICOX.rc
