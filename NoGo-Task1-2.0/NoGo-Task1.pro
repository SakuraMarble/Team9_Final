QT       += core gui
QT += network
#QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chat.cpp \
    GameModel.cpp \
    connectdialog.cpp \
    dialogchoosemode.cpp \
    main.cpp \
    mainwindow.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp \
    nogo_ai.cpp \
    online_ai_helper.cpp \
    signinwindow.cpp

HEADERS += \
    Chat.h \
    GameModel.h \
    connectdialog.h \
    dialogchoosemode.h \
    mainwindow.h \
    networkdata.h \
    networkserver.h \
    networksocket.h \
    nogo_ai.h \
    online_ai_helper.h \
    signinwindow.h

FORMS += \
    Chat.ui \
    connectdialog.ui \
    dialogchoosemode.ui \
    mainwindow.ui \
    signinwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
