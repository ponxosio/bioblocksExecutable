#ifndef QTBIOBLOCKEXECUTABLE_H
#define QTBIOBLOCKEXECUTABLE_H

/*
 * PLEASE ALWAYS IMPORT PYTHON PLUGINS THE FIRST IN A PROJECT, USING MSVC boost/python/operators.hpp COLIDES WITH <cisco646>
 * http://boost.2283326.n4.nabble.com/boost-python-incorrect-use-of-keywords-and-or-etc-td4630496.html
 */
#include <pythonPlugins/actuators/pythonpluginabstractfactory.h>
#include <pythonPlugins/environment/PythonEnvironment.h>
//

#include <signal.h>

#include <QObject>

#include <bioblocksExecution/usercommunications/consoleusercommunications.h>
#include <bioblocksExecution/bioblocksexecution.h>

#include <communications/CommandSender.h>
#include <communications/FileSender.h>
#include <communications/SerialSender.h>

#include <constraintengine/prologexecutor.h>

#include <utils/units.h>
#include <utils/utilsjson.h>

#include "commandlineparametersobj.h"

class QtBioblockExecutable : public QObject
{
    Q_OBJECT

private:
    QCoreApplication* app;
    BioblocksExecution* execution;
    std::shared_ptr<CommandSender> command;
    _In_opt_ _crt_signal_t _Function;

public:
    explicit QtBioblockExecutable(_In_opt_ _crt_signal_t _Function, QObject *parent = 0);
    ~QtBioblockExecutable();

    /////////////////////////////////////////////////////////////
    /// Call this to quit application
    /////////////////////////////////////////////////////////////
    void quit();

    /////////////////////////////////////////////////////////////
    /// Call this function before the programs quits
    /////////////////////////////////////////////////////////////
    void cleanUp();

signals:
    /////////////////////////////////////////////////////////////
    /// Signal to finish, this is connected to Application Quit
    /////////////////////////////////////////////////////////////
    void finished();

public slots:
    /////////////////////////////////////////////////////////////
    /// This is the slot that gets called from main to start everything
    /// but, everthing is set up in the Constructor
    /////////////////////////////////////////////////////////////
    void run();

    /////////////////////////////////////////////////////////////
    /// slot that get signal when that application is about to quit
    /////////////////////////////////////////////////////////////
    void aboutToQuitApp();
};

#endif // QTBIOBLOCKEXECUTABLE_H
