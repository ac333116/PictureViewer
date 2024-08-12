QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    imageloaderthread.cpp \
    largerviewdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    myitem.cpp \
    mylabel.cpp \
    threadpool.cpp

HEADERS += \
    imageloaderthread.h \
    largerviewdialog.h \
    mainwindow.h \
    myitem.h \
    mylabel.h \
    threadpool.h

FORMS += \
    largerviewdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rs.qrc
