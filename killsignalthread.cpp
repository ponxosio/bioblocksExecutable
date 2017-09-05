#include "killsignalthread.h"

KillSignalThread::KillSignalThread(
        BioblocksExecution* executable,
        const std::string & protocolJSONFile,
        const std::string & machineJSONFile,
        const std::string & pluginBaseFolder,
        units::Time timeSlice,
        std::shared_ptr<TimeStampSimulator> timestampSimulator,
        QObject* parent) :
    QThread(parent), protocolJSONFile(protocolJSONFile), machineJSONFile(machineJSONFile), pluginBaseFolder(pluginBaseFolder)
{
    this->executable = executable;
    this->timeSlice = timeSlice;

    this->timestampSimulator = timestampSimulator;
}

KillSignalThread::~KillSignalThread() {

}

void KillSignalThread::run() {
    try {
        std::cout << "initilaizing environment...";

        PythonEnvironment::GetInstance()->initEnvironment(pluginBaseFolder);
        PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

        std::cout << "done!" << std::endl;

        std::cout << "executing in thread:" << std::endl;

        if (timestampSimulator == NULL) {
            executable->executeNewProtocol(protocolJSONFile, machineJSONFile, timeSlice);
        } else {
            executable->executeNewProtocolSimulateTime(protocolJSONFile, machineJSONFile, timeSlice, timestampSimulator);
        }

        std::cout << "end execution!" << std::endl;
        emit ended();
    } catch (std::exception & e) {
        std::cerr << "Execption Ocurred: " << e.what() << std::endl;
        emit ended();
    }
}
