QT += core
QT += core gui
QT += gui
QT += serialport
QT += charts

INCLUDEPATH += D:\Qt\Tools\mingw1120_64\lib\gcc\x86_64-w64-mingw32\11.2.0\include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    chartview.cpp \
    geoangularvelocityvector.cpp \
    inputsettings.cpp \
    main.cpp \
    mainwindow.cpp \
    monitorinput.cpp \
    navigationalgorithm.cpp \
    navigationalgorithmparallel.cpp \
    orientationalgorithm.cpp \
    orientationalgorithmparallel.cpp \
    parallelprocessthread.cpp \
    plotmonitor.cpp \
    qfileio.cpp \
    qserialio.cpp \
    serialprocessthread.cpp \
    stringtofloatmeasurements.cpp \
    tablecmatrix.cpp

HEADERS += \
    chart.h \
    chartview.h \
    geoangularvelocityvector.h \
    inputsettings.h \
    mainwindow.h \
    monitorinput.h \
    navigationalgorithm.h \
    navigationalgorithmparallel.h \
    orientationalgorithm.h \
    orientationalgorithmparallel.h \
    parallelprocessthread.h \
    plotmonitor.h \
    qfileio.h \
    qserialio.h \
    serialprocessthread.h \
    stringtofloatmeasurements.h \
    tablecmatrix.h

FORMS += \
    inputsettings.ui \
    mainwindow.ui \
    monitorinput.ui \
    plotmonitor.ui \
    tablecmatrix.ui

TRANSLATIONS += \
    Diplom_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
