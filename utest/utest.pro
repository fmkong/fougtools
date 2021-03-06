include(../qmake/config.pri)

TEMPLATE = app

TARGET = utest$$TARGET_SUFFIX

CONFIG += console
QT += testlib  gui  script

HEADERS += \
    $$PWD/test_cpptools.h \
    $$PWD/test_qttools.h \
    \
    $$PWD/../src/cpptools/enum_string_map.h \
    \
    $$PWD/../src/qttools/core/qlocale_utils.h \
    $$PWD/../src/qttools/gui/qstandard_item_explorer.h \
    $$PWD/../src/qttools/script/calculator.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/test_cpptools.cpp \
    $$PWD/test_qttools.cpp \
    \
    $$PWD/../src/qttools/core/qlocale_utils.cpp \
    $$PWD/../src/qttools/gui/qstandard_item_explorer.cpp \
    $$PWD/../src/qttools/script/calculator.cpp

occtools {
    DEFINES += FOUGTOOLS_HAVE_OCCTOOLS

    include(../src/occtools/occ.pri)

    HEADERS += \
        $$PWD/test_occtools.h \
        $$PWD/../src/occtools/io.h

    SOURCES += \
        $$PWD/test_occtools.cpp \
        $$PWD/../src/occtools/io.cpp

    LIBS += \
        -lTKBRep -lTKernel -lTKG2d -lTKG3d -lTKGeomAlgo -lTKGeomBase \
        -lTKIGES -lTKMath -lTKPrim -lTKService -lTKShHealing \
        -lTKSTEP -lTKSTEPAttr -lTKSTEPBase -lTKSTEP209 -lTKSTL -lTKTopAlgo \
        -lTKXSBase
} # occtools

qttools_task {
    DEFINES += FOUGTOOLS_HAVE_QTTOOLS_TASK
    include(../src/qttools/task/qttools_task.pri)
} # qttools_task
