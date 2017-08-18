#include "qtbioblockexecutable.h"

QtBioblockExecutable::QtBioblockExecutable(_In_opt_ _crt_signal_t _Function, QObject *parent) :
    QObject(parent), _Function(_Function)
{
    this->app = QCoreApplication::instance();
    this->execution = NULL;
    this->command = NULL;
}

QtBioblockExecutable::~QtBioblockExecutable() {
    if(execution != NULL) {
        delete execution;
    }
}

void QtBioblockExecutable::quit() {
    emit finished();
}

void QtBioblockExecutable::cleanUp() {
    std::cout << "about to quit..." << std::endl;
    execution->stopExecution();

    PythonEnvironment::GetInstance()->finishEnvironment();
    PrologExecutor::destoryEngine();

    if (command != NULL) {
        command->disconnect();
    }
}

void QtBioblockExecutable::run() {
    try {
        CommandLineParametersObj parameters = CommandLineParametersObj::parseCommandLineArguments(*app);
        command = parameters.getCommand();

        PluginFileLoader::setPluginDir(parameters.getPluginFolderPath());

        PythonEnvironment::GetInstance()->initEnvironment(parameters.getPluginBaseFolderPath());
        PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

        signal(SIGINT, _Function);

        command->connect();

        std::shared_ptr<PythonPluginAbstractFactory> pythonPlugins = std::make_shared<PythonPluginAbstractFactory>(command);
        std::shared_ptr<UserCommunicationInterface> userCom = std::make_shared<ConsoleUserCommunications>();
        execution = new BioblocksExecution(pythonPlugins, userCom);

        execution->executeNewProtocol(parameters.getProtocolFilePath(), parameters.getMachineFilePath(), parameters.getTimeSlice());

        quit();
    } catch (std::exception & e) {
        std::cerr << "Exeption occurred: " << e.what() << std::endl;
        quit();
    }
}

void QtBioblockExecutable::aboutToQuitApp() {
    cleanUp();
}
