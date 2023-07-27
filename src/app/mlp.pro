QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    view/graphreport.cc \
    view/learningpopup.cc \
    view/mainwindow.cc \
    view/painter.cc \
    model/datastorage.cc \
    model/facade.cc \
    model/network.cc \
    model/matrix_network.cc \
    model/graph_network.cc \
    model/s21matrix.cc \
    model/layer.cc \
    model/neuron.cc \
    controller/controller.cc \
    view/qcustomplot/qcustomplot.cpp \
    view/testpopup.cc

HEADERS += \
    view/graphreport.h \
    view/painter.h \
    view/mainwindow.h \
    model/datastorage.h \
    model/facade.h \
    model/network.h \
    model/matrix_network.h \
    model/graph_network.h \
    model/s21matrix.h \
    model/layer.h \
    model/neuron.h \
    controller/controller.h \
    view/learningpopup.h \
    view/testpopup.h \
    view/qcustomplot/qcustomplot.h

FORMS += \
    view/graphreport.ui \
    view/learningpopup.ui \
    view/mainwindow.ui \
    view/testpopup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
