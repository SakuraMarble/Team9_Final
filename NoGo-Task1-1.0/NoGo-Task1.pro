QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameModel.cpp \
    main.cpp \
    mainwindow.cpp \
    nogo_ai.cpp

HEADERS += \
    GameModel.h \
<<<<<<< HEAD
    mainwindow.h
=======
    countwidget.h \
    mainwindow.h \
    nogo_ai.h
>>>>>>> 484e0405fa88a3102201ad655471fa4da7f358c4

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
