# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
    # ensure one "debug" or "release" in CONFIG so they can be used as
    #   conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

QT += core
QT -= gui

CONFIG += c++11

TARGET = bioblocksExecutable
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    commandlineparametersobj.cpp \
    qtbioblockexecutable.cpp

debug {
    QMAKE_POST_LINK=X:\bioblocksExecutable\bioblocksExecutable\copyDLL.bat $$shell_path($$OUT_PWD/debug) debug

    INCLUDEPATH += X:\fluidicMachineModel\dll_debug\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_debug\bin) -lFluidicMachineModel

    INCLUDEPATH += X:\constraintsEngine\dll_debug\include
    LIBS += -L$$quote(X:\constraintsEngine\dll_debug\bin) -lconstraintsEngineLibrary

    INCLUDEPATH += X:\utils\dll_debug\include
    LIBS += -L$$quote(X:\utils\dll_debug\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_debug\include
    LIBS += -L$$quote(X:\commomModel\dll_debug\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_debug\include
    LIBS += -L$$quote(X:\protocolGraph\dll_debug\bin) -lprotocolGraph

    INCLUDEPATH += X:\blockly_fluidicMachine_translator\dll_debug\include
    LIBS += -L$$quote(X:\blockly_fluidicMachine_translator\dll_debug\bin) -lblocklyFluidicMachineTranslator

    INCLUDEPATH += X:\fluidicModelMapping\dll_debug\include
    LIBS += -L$$quote(X:\fluidicModelMapping\dll_debug\bin) -lFluidicModelMapping

    INCLUDEPATH += X:\bioblocksTranslation\dll_debug\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_debug\bin) -lbioblocksTranslation

    INCLUDEPATH += X:\bioblocksExecution\dll_debug\include
    LIBS += -L$$quote(X:\bioblocksExecution\dll_debug\bin) -lbioblocksExecution

    INCLUDEPATH += X:\pythonPlugins\dll_debug\include
    LIBS += -L$$quote(X:\pythonPlugins\dll_debug\bin) -lpythonPlugins

    LIBS += -L$$quote(X:\libraries\boost_1_63_0\stage\lib) -lboost_python-vc140-mt-gd-1_63
}

!debug {
    QMAKE_POST_LINK=X:\bioblocksExecutable\bioblocksExecutable\copyDLL.bat $$shell_path($$OUT_PWD/release) release

    INCLUDEPATH += X:\fluidicMachineModel\dll_release\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_release\bin) -lFluidicMachineModel

    INCLUDEPATH +=X:\constraintsEngine\dll_release\include
    LIBS += -L$$quote(X:\constraintsEngine\dll_release\bin) -lconstraintsEngineLibrary

    INCLUDEPATH += X:\utils\dll_release\include
    LIBS += -L$$quote(X:\utils\dll_release\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_release\include
    LIBS += -L$$quote(X:\commomModel\dll_release\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_release\include
    LIBS += -L$$quote(X:\protocolGraph\dll_release\bin) -lprotocolGraph

    INCLUDEPATH += X:\blockly_fluidicMachine_translator\dll_release\include
    LIBS += -L$$quote(X:\blockly_fluidicMachine_translator\dll_release\bin) -lblocklyFluidicMachineTranslator

    INCLUDEPATH += X:\fluidicModelMapping\dll_release\include
    LIBS += -L$$quote(X:\fluidicModelMapping\dll_release\bin) -lFluidicModelMapping

    INCLUDEPATH += X:\bioblocksTranslation\dll_release\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_release\bin) -lbioblocksTranslation

    INCLUDEPATH += X:\bioblocksExecution\dll_release\include
    LIBS += -L$$quote(X:\bioblocksExecution\dll_release\bin) -lbioblocksExecution

    INCLUDEPATH += X:\pythonPlugins\dll_release\include
    LIBS += -L$$quote(X:\pythonPlugins\dll_release\bin) -lpythonPlugins

    LIBS += -L$$quote(X:\libraries\boost_1_63_0\stage\lib) -lboost_python-vc140-mt-1_63
}

INCLUDEPATH += X:\libraries\cereal-1.2.2\include
INCLUDEPATH += X:\libraries\json-2.1.1\src
INCLUDEPATH += X:\libraries\boost_1_63_0

INCLUDEPATH += X:\swipl\include
LIBS += -L$$quote(X:\swipl\bin) -llibswipl
LIBS += -L$$quote(X:\swipl\lib) -llibswipl

#python environment
INCLUDEPATH += C:\Python27\include
LIBS += -L$$quote(C:\Python27\libs)

HEADERS += \
    commandlineparametersobj.h \
    qtbioblockexecutable.h
