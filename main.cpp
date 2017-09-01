/*
 * PLEASE ALWAYS IMPORT PYTHON PLUGINS THE FIRST IN A PROJECT, USING MSVC boost/python/operators.hpp COLIDES WITH <cisco646>
 * http://boost.2283326.n4.nabble.com/boost-python-incorrect-use-of-keywords-and-or-etc-td4630496.html
 */
#include <pythonPlugins/actuators/pythonpluginabstractfactory.h>
#include <pythonPlugins/environment/PythonEnvironment.h>
//

#include <signal.h>

#include <QObject>
#include <QTimer>
#include <QLocalServer>

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

int main(int argc, char *argv[])
{
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
}
