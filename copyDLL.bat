SET COPY_DLL_QT_PATH=C:\Qt\5.7\msvc2015_64\bin

REM copy executable
COPY %1\bioblocksExecutable.exe X:\bioblocksExecutable\executable_%2\bioblocksExecutable.exe

REM copy local dll
COPY X:\fluidicMachineModel\dll_%2\bin\FluidicMachineModel.dll X:\bioblocksExecutable\executable_%2\FluidicMachineModel.dll

COPY X:\constraintsEngine\dll_%2\bin\constraintsEngineLibrary.dll X:\bioblocksExecutable\executable_%2\constraintsEngineLibrary.dll

COPY X:\utils\dll_%2\bin\utils.dll X:\bioblocksExecutable\executable_%2\utils.dll

COPY X:\commomModel\dll_%2\bin\commonModel.dll X:\bioblocksExecutable\executable_%2\commonModel.dll

COPY X:\bioblocksExecution\dll_%2\bin\bioblocksExecution.dll X:\bioblocksExecutable\executable_%2\bioblocksExecution.dll

COPY X:\blockly_fluidicMachine_translator\dll_%2\bin\blocklyFluidicMachineTranslator.dll X:\bioblocksExecutable\executable_%2\blocklyFluidicMachineTranslator.dll

COPY X:\fluidicModelMapping\dll_%2\bin\FluidicModelMapping.dll X:\bioblocksExecutable\executable_%2\FluidicModelMapping.dll

COPY X:\bioblocksTranslation\dll_%2\bin\bioblocksTranslation.dll X:\bioblocksExecutable\executable_%2\bioblocksTranslation.dll

COPY X:\pythonPlugins\dll_%2\bin\pythonPlugins.dll X:\bioblocksExecutable\executable_%2\pythonPlugins.dll

COPY X:\protocolGraph\dll_%2\bin\protocolGraph.dll X:\bioblocksExecutable\executable_%2\protocolGraph.dll

REM external libraries

REM PYTHON
if "%2" == "debug" (
	COPY X:\libraries\boost_1_63_0\stage\lib\boost_python-vc140-mt-gd-1_63.dll X:\bioblocksExecutable\executable_%2\boost_python-vc140-mt-gd-1_63.dll
	COPY %COPY_DLL_QT_PATH%\Qt5SerialPortd.dll X:\bioblocksExecutable\executable_%2\Qt5SerialPortd.dll
) else (
	COPY X:\libraries\boost_1_63_0\stage\lib\boost_python-vc140-mt-1_63.dll X:\bioblocksExecutable\executable_%2\boost_python-vc140-mt-1_63.dll
	COPY %COPY_DLL_QT_PATH%\Qt5SerialPort.dll X:\bioblocksExecutable\executable_%2\Qt5SerialPort.dll
)

REM PROLOG
COPY X:\swipl\bin\libswipl.dll X:\bioblocksExecutable\executable_%2\libswipl.dll
COPY X:\swipl\bin\libdwarf.dll X:\bioblocksExecutable\executable_%2\libdwarf.dll
COPY X:\swipl\bin\libwinpthread-1.dll X:\bioblocksExecutable\executable_%2\libwinpthread-1.dll
COPY X:\swipl\bin\libgmp-10.dll X:\bioblocksExecutable\executable_%2\libgmp-10.dll
COPY X:\swipl\bin\libgcc_s_seh-1.dll X:\bioblocksExecutable\executable_%2\libgcc_s_seh-1.dll

start /D "X:\bioblocksExecutable\executable_release" C:\Qt\5.7\msvc2015_64\bin\windeployqt.exe bioblocksExecutable.exe


