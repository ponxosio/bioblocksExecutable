/*
 * PLEASE ALWAYS IMPORT PYTHON PLUGINS THE FIRST IN A PROJECT, USING MSVC boost/python/operators.hpp COLIDES WITH <cisco646>
 * http://boost.2283326.n4.nabble.com/boost-python-incorrect-use-of-keywords-and-or-etc-td4630496.html
 */
#include <pythonPlugins/actuators/pythonpluginabstractfactory.h>
#include <pythonPlugins/environment/PythonEnvironment.h>
//

#include <iostream>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <bioblocksExecution/usercommunications/consoleusercommunications.h>
#include <bioblocksExecution/bioblocksexecution.h>

#include <communications/CommandSender.h>
#include <communications/FileSender.h>
#include <communications/SerialSender.h>

#include <constraintengine/prologexecutor.h>

#include <utils/units.h>
#include <utils/utilsjson.h>

#include "commandlineparametersobj.h"

int main(int argc, char *argv[])
{
    std::cout << "Initializing System..."<< std::endl;

    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationVersion("0.1");

    std::shared_ptr<CommandSender> command = NULL;
    try {
        CommandLineParametersObj parameters = CommandLineParametersObj::parseCommandLineArguments(a);
        command = parameters.getCommand();

        PluginFileLoader::setPluginDir(parameters.getPluginFolderPath());

        PythonEnvironment::GetInstance()->initEnvironment(parameters.getPluginBaseFolderPath());
        PrologExecutor::createEngine(QCoreApplication::applicationName().toStdString());

        command->connect();

        std::shared_ptr<PythonPluginAbstractFactory> pythonPlugins = std::make_shared<PythonPluginAbstractFactory>(command);
        std::shared_ptr<UserCommunicationInterface> userCom = std::make_shared<ConsoleUserCommunications>();
        BioblocksExecution execution(pythonPlugins, userCom);

        execution.executeNewProtocol(parameters.getProtocolFilePath(), parameters.getMachineFilePath(), parameters.getTimeSlice());

        PythonEnvironment::GetInstance()->finishEnvironment();
        PrologExecutor::destoryEngine();
        command->disconnect();

        return 0;
    } catch (std::exception & e) {
        std::cerr << "Exeption occurred: " << e.what() << std::endl;

        PythonEnvironment::GetInstance()->finishEnvironment();
        PrologExecutor::destoryEngine();
        if (command != NULL) {
            command->disconnect();
        }
        return -1;
    }
}
