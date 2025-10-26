QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include(DinamicTable/DinamicTable.pri)
include(ResultShower/ResultShower.pri)

SOURCES += \
    CalcButton.cpp \
    CalcFunctions.cpp \
    CalcSubGame.cpp \
    CastomRecord/CastomRecord.cpp \
    Schedule/ScheduleGame.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CalcButton.h \
    CalcFunctions.h \
    CalcSubGame.h \
    CastomRecord/CastomRecord.h \
    Schedule/ScheduleGame.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
