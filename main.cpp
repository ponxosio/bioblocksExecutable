/*
 * PLEASE ALWAYS IMPORT PYTHON PLUGINS THE FIRST IN A PROJECT, USING MSVC boost/python/operators.hpp COLIDES WITH <cisco646>
 * http://boost.2283326.n4.nabble.com/boost-python-incorrect-use-of-keywords-and-or-etc-td4630496.html
 */
#include <pythonPlugins/actuators/pythonpluginabstractfactory.h>
#include <pythonPlugins/environment/PythonEnvironment.h>
//

#include <signal.h>

#include <QObject>
<<<<<<< HEAD
=======
#include <QTimer>
#include <QLocalServer>
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919

#include <bioblocksExecution/usercommunications/consoleusercommunications.h>
#include <bioblocksExecution/bioblocksexecution.h>

#include <communications/CommandSender.h>
#include <communications/FileSender.h>
#include <communications/SerialSender.h>

#include <constraintengine/prologexecutor.h>

#include <utils/units.h>
#include <utils/utilsjson.h>

#include "commandlineparametersobj.h"
#include "qtbioblockexecutable.h"
#include "killsignalthread.h"

 std::shared_ptr<CommandSender> command = NULL;
 BioblocksExecution* execution = NULL;

 void handle_eptr(std::exception_ptr eptr) // passing by value is ok
 {
     try {
         if (eptr) {
             std::rethrow_exception(eptr);
         }
     } catch(const std::exception& e) {
         std::cerr << "Exeption occurred: " << e.what() << std::endl;
     }
 }

 void cleanUp() {
     std::cout << "cleaning up...";

     if (execution != NULL) {
         execution->stopExecution();
         delete execution;
     }

     if (command != NULL) {
         command->disconnect();
     }

     PythonEnvironment::GetInstance()->finishEnvironment();
     PrologExecutor::destoryEngine();

     std::cout << "done!" << std::endl;
 }

void SignalHandler(int signal) {
    if(signal == SIGINT || signal == SIGTERM) {
        std::cout << "kill signal arrived" << std::endl;
        cleanUp();
        exit(0);
    }
}

 std::shared_ptr<CommandSender> command = NULL;
 BioblocksExecution* execution = NULL;

 void handle_eptr(std::exception_ptr eptr) // passing by value is ok
 {
     try {
         if (eptr) {
             std::rethrow_exception(eptr);
         }
     } catch(const std::exception& e) {
         std::cerr << "Exeption occurred: " << e.what() << std::endl;
     }
 }

 void cleanUp() {
     std::cout << "cleaning up...";

     if (execution != NULL) {
         execution->stopExecution();
         delete execution;
     }

     if (command != NULL) {
         command->disconnect();
     }

     PythonEnvironment::GetInstance()->finishEnvironment();
     PrologExecutor::destoryEngine();

     std::cout << "done!" << std::endl;
 }

void SignalHandler(int signal) {
    if(signal == SIGINT || signal == SIGTERM) {
        std::cout << "kill signal arrived" << std::endl;
        cleanUp();
        exit(0);
    }
}

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    std::cout << "starting...";
    QCoreApplication app(argc, argv);
    std::cout << "done!" << std::endl;

    std::exception_ptr eptr;
    try {
        std::cout << "reading params...";
        CommandLineParametersObj parameters = CommandLineParametersObj::parseCommandLineArguments(app);
        command = parameters.getCommand();

        PluginFileLoader::setPluginDir(parameters.getPluginFolderPath());
        std::cout << "done!" << std::endl;

        std::cout << "initilaizing environment...";
        PythonEnvironment::GetInstance()->initEnvironment(parameters.getPluginBaseFolderPath());
        PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

        signal(SIGINT, SignalHandler);
        signal(SIGTERM, SignalHandler);

        command->connect();
        std::cout << "done!" << std::endl;

        std::shared_ptr<PythonPluginAbstractFactory> pythonPlugins = std::make_shared<PythonPluginAbstractFactory>(command);
        std::shared_ptr<UserCommunicationInterface> userCom = std::make_shared<ConsoleUserCommunications>();
        execution = new BioblocksExecution(pythonPlugins, userCom);

        std::cout << "executing:" << std::endl;
        execution->executeNewProtocol(parameters.getProtocolFilePath(), parameters.getMachineFilePath(), parameters.getTimeSlice());

    } catch (std::exception & e) {
        std::cerr << "Exeption occurred: " << e.what() << std::endl;
    } catch(...) {
        eptr = std::current_exception();
    }

    handle_eptr(eptr);

    cleanUp();
    exit(0);
=======
    QCoreApplication app(argc, argv);

    // create the main class
    QLocalServer exitServer;
    QtBioblockExecutable myMain(&exitServer);

    /*KillSignalThread killThread(&myMain);
    killThread.start();*/

    std::cout << "starting quit server...";

    if (exitServer.listen("finishExecution")) {
        std::cout << "server listening for cancel signal...";
        QObject::connect(&exitServer, SIGNAL(newConnection()), &myMain, SLOT(processTerminationSignal()));
    } else {
        std::cerr << "impossible to open local server: " << exitServer.errorString().toStdString();
        return -1;
    }

    std::cout << "done!" << std::endl;


    // connect up the signals
    QObject::connect(&myMain, SIGNAL(finished()),
                     &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()),
                     &myMain, SLOT(aboutToQuitApp()));

    // This code will start the messaging engine in QT and in
    // 10ms it will start the execution in the MainClass.run routine;
    QTimer::singleShot(10, &myMain, SLOT(run()));
    return app.exec();
>>>>>>> 71849cd9ba2e8cd538941a138541871c0e52f919
}
