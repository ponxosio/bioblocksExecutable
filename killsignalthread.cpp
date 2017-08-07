#include "killsignalthread.h"

KillSignalThread::KillSignalThread(
        BioblocksExecution* executable,
        const std::string & protocolJSONFile,
        const std::string & machineJSONFile,
        const std::string & pluginBaseFolder,
        units::Time timeSlice,
        QObject* parent) :
    QThread(parent), protocolJSONFile(protocolJSONFile), machineJSONFile(machineJSONFile), pluginBaseFolder(pluginBaseFolder)
{
    this->executable = executable;
    this->timeSlice = timeSlice;
}

KillSignalThread::~KillSignalThread() {

}

void KillSignalThread::run() {

    std::cout << "initilaizing environment...";

    PythonEnvironment::GetInstance()->initEnvironment(pluginBaseFolder);
    PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

    std::cout << "done!" << std::endl;

    std::cout << "executing in thread:" << std::endl;

    executable->executeNewProtocol(protocolJSONFile, machineJSONFile, timeSlice);

    std::cout << "end execution!" << std::endl;
    emit ended();
}
