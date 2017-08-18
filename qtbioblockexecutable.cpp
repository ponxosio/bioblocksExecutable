#include "qtbioblockexecutable.h"

<<<<<<< HEAD
QtBioblockExecutable::QtBioblockExecutable(_In_opt_ _crt_signal_t _Function, QObject *parent) :
    QObject(parent), _Function(_Function)
=======
QtBioblockExecutable::QtBioblockExecutable(QLocalServer* exitServer, QObject *parent) throw(std::runtime_error) :
    QObject(parent)
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
{
    this->app = QCoreApplication::instance();
    this->execution = NULL;
    this->command = NULL;
<<<<<<< HEAD
=======
    this->executionThread = NULL;
    this->exitServer = exitServer;
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
}

QtBioblockExecutable::~QtBioblockExecutable() {
    if(execution != NULL) {
        delete execution;
    }
<<<<<<< HEAD
=======

    if(executionThread != NULL) {
        delete executionThread;
    }
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
}

void QtBioblockExecutable::quit() {
    emit finished();
}

void QtBioblockExecutable::cleanUp() {
    std::cout << "about to quit..." << std::endl;
<<<<<<< HEAD
    execution->stopExecution();
=======

    if (executionThread != NULL) {
        executionThread->quit();
    }

    if (execution != NULL) {
        execution->stopExecution();
    }
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919

    PythonEnvironment::GetInstance()->finishEnvironment();
    PrologExecutor::destoryEngine();

    if (command != NULL) {
        command->disconnect();
    }
}

void QtBioblockExecutable::run() {
    try {
<<<<<<< HEAD
=======
        std::cout << "reading params...";
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
        CommandLineParametersObj parameters = CommandLineParametersObj::parseCommandLineArguments(*app);
        command = parameters.getCommand();

        PluginFileLoader::setPluginDir(parameters.getPluginFolderPath());
<<<<<<< HEAD

        PythonEnvironment::GetInstance()->initEnvironment(parameters.getPluginBaseFolderPath());
        PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

        signal(SIGINT, _Function);

        command->connect();
=======
        std::cout << "done!" << std::endl;

        command->connect();
        std::cout << "done!" << std::endl;
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919

        std::shared_ptr<PythonPluginAbstractFactory> pythonPlugins = std::make_shared<PythonPluginAbstractFactory>(command);
        std::shared_ptr<UserCommunicationInterface> userCom = std::make_shared<ConsoleUserCommunications>();
        execution = new BioblocksExecution(pythonPlugins, userCom);

<<<<<<< HEAD
        execution->executeNewProtocol(parameters.getProtocolFilePath(), parameters.getMachineFilePath(), parameters.getTimeSlice());

        quit();
=======
        executionThread = new KillSignalThread(execution,
                                               parameters.getProtocolFilePath(),
                                               parameters.getMachineFilePath(),
                                               parameters.getPluginBaseFolderPath(),
                                               parameters.getTimeSlice());

        connect(executionThread, SIGNAL(ended()), this, SLOT(aboutToQuitApp()));

        executionThread->start();
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
    } catch (std::exception & e) {
        std::cerr << "Exeption occurred: " << e.what() << std::endl;
        quit();
    }
}

void QtBioblockExecutable::aboutToQuitApp() {
    cleanUp();
}
<<<<<<< HEAD
=======

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
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
