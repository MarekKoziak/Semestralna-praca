QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

message(Building for Windows)
# OpenCV path
INCLUDEPATH += C://opencv/build/include

# OpenCV libs
LIBS += "C://opencv/build/x64/vc15/lib/opencv_world420d.lib"

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    filebrowser.cpp

HEADERS += \
    mainwindow.h \
    filebrowser.h

FORMS += \
    mainwindow.ui \
    filebrowser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
