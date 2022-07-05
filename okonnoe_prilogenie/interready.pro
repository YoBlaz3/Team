QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../drive-download-20220629T131206Z-001/singletonclient.cpp \
    authreg.cpp \
    formtask.cpp \
    functionsforclient.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../drive-download-20220629T131206Z-001/singletonclient.h \
    authreg.h \
    formtask.h \
    functionsforclient.h \
    mainwindow.h

FORMS += \
    authreg.ui \
    formtask.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
