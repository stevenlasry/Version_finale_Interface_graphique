QT += widgets
QT += core gui
greaterThan(QT_MAJOR_VERSION,4): QT += widgets printsupport

SUBDIRS += \
    plot-examples.pro

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ModeleDePrevision.cpp \
    CalculDuScore.cpp \
    Parser.cpp \
    ModeleDePlusProchesVoisins.cpp \
    PrevisionPlusProchesVoisinsNormeEuclidienne.cpp \
    PrevisionPlusProchesVoisinsNormeUn.cpp

HEADERS += \
    mainwindow.h \
    qcustomplot.h \
    ModeleDePrevision.h \
    CalculDuScore.h \
    Parser.h \
    ModeleDePlusProchesVoisins.h \
    PrevisionPlusProchesVoisinsNormeEuclidienne.h \
    PrevisionPlusProchesVoisinsNormeUn.h

RESOURCES +=

FORMS +=
