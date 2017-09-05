#include "qtbioblockexecutable.h"

QtBioblockExecutable::QtBioblockExecutable(QLocalServer* exitServer, QObject *parent) throw(std::runtime_error) :
    QObject(parent)
{
    this->exitServer = exitServer;

    this->app = QCoreApplication::instance();
    this->execution = NULL;
    this->command = NULL;
    this->executionThread = NULL;

}

QtBioblockExecutable::~QtBioblockExecutable() {
    if(execution != NULL) {
        delete execution;
    }

    if(executionThread != NULL) {
        delete executionThread;
    }
}

void QtBioblockExecutable::quit() {
    emit finished();
}

void QtBioblockExecutable::cleanUp() {
    std::cout << "about to quit...";

    if (execution != NULL) {
        execution->stopExecution();
    }

    if (executionThread != NULL) {
        //executionThread->quit();
        executionThread->wait(30000);
    }

    PythonEnvironment::GetInstance()->finishEnvironment();
    PrologExecutor::destoryEngine();

    if (command != NULL) {
        command->disconnect();
    }
    std::cout << "done!" << std::endl;
}

void QtBioblockExecutable::run() {
    try {
        std::cout << "reading params...";
        CommandLineParametersObj parameters = CommandLineParametersObj::parseCommandLineArguments(*app);
        command = parameters.getCommand();

        PluginFileLoader::setPluginDir(parameters.getPluginFolderPath());

        std::cout << "done!" << std::endl;

        std::cout << "opening communications with the machine...";
        command->connect();
        std::cout << "done!" << std::endl;

        std::shared_ptr<PythonPluginAbstractFactory> pythonPlugins = std::make_shared<PythonPluginAbstractFactory>(command);
        std::shared_ptr<UserCommunicationInterface> userCom = std::make_shared<ConsoleUserCommunications>();
        execution = new BioblocksExecution(pythonPlugins, userCom);

        executionThread = new KillSignalThread(execution,
                                               parameters.getProtocolFilePath(),
                                               parameters.getMachineFilePath(),
                                               parameters.getPluginBaseFolderPath(),
                                               parameters.getTimeSlice(),
                                               parameters.getSimulateTimestamp());

        connect(executionThread, SIGNAL(ended()), this, SLOT(terminate()));

        executionThread->start();
    } catch (std::exception & e) {
        std::cerr << "Exeption occurred: " << e.what() << std::endl;
        quit();
    }
}

void QtBioblockExecutable::aboutToQuitApp() {
    cleanUp();
}

void QtBioblockExecutable::processTerminationSignal() {
    QByteArray block;

    std::cout << "Termination signal arrived!" << std::endl;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint32)0;
    out << "OK";
    out.device()->seek(0);
    out << (quint32)(block.size() - sizeof(quint32));

    QLocalSocket *clientConnection = exitServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),clientConnection, SLOT(deleteLater()));

    clientConnection->write(block);
    clientConnection->flush();
    clientConnection->disconnectFromServer();

    quit();
}

void QtBioblockExecutable::terminate() {
    quit();
}
