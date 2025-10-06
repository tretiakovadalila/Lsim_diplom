QT       += core gui
QT += charts
QT += datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AtmLoss.cpp \
    BeamPattern.cpp \
    Chebyshev_window.cpp \
    Complex.cpp \
    RSPSimFull.cpp \
    RadarParInit.cpp \
    Rnd.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AntPosition_type.h \
    ClutSimPar_type.h \
    InitMenu_type.h \
    L_Head_type.h \
    L_RadSimOut_type.h \
    L_RadarPar_type.h \
    L_RspOut_type.h \
    L_TwsPar_type.h \
    MathConst.h \
    TerMap_type.h \
    TgtSimPar_type.h \
    mainwindow.h \
    rspSimFull.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/thirdparty/fftw3/include
LIBS += -L$$PWD/thirdparty/fftw3/lib -lfftw3-3 -lm

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
