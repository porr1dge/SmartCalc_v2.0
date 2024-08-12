QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/graphwindow.cc \
    main.cc \
    View/view.cc \
    Model/model.cc \
    Controller/controller.cc \
    qcustomplot.cpp

HEADERS += \
    Model/helper.h \
    View/graphwindow.h \
    View/view.h \
    Model/model.h \
    Controller/controller.h \
    qcustomplot.h

FORMS += \
    View/graphwindow.ui\
    View/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
