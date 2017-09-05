#ifndef KILLSIGNALTHREAD_H
#define KILLSIGNALTHREAD_H

/*
 * PLEASE ALWAYS IMPORT PYTHON PLUGINS THE FIRST IN A PROJECT, USING MSVC boost/python/operators.hpp COLIDES WITH <cisco646>
 * http://boost.2283326.n4.nabble.com/boost-python-incorrect-use-of-keywords-and-or-etc-td4630496.html
 */
#include <pythonPlugins/actuators/pythonpluginabstractfactory.h>
#include <pythonPlugins/environment/PythonEnvironment.h>
//

#include <stdexcept>

#include <QCoreApplication>
#include <QThread>

#include <bioblocksExecution/bioblocksexecution.h>
#include <constraintengine/prologexecutor.h>
#include <utils/timestampsimulator.h>

class KillSignalThread : public QThread
{
    Q_OBJECT

public:
    KillSignalThread(BioblocksExecution* executable,
                     const std::string & protocolJSONFile,
                     const std::string & machineJSONFile,
                     const std::string & pluginBaseFolder,
                     units::Time timeSlice,
                     std::shared_ptr<TimeStampSimulator> timestampSimulator = NULL,
                     QObject* parent=0);

    virtual ~KillSignalThread();

signals:
    void ended();

protected:
    void run() override;

private:
    BioblocksExecution* executable;
    std::string protocolJSONFile;
    std::string machineJSONFile;
    std::string pluginBaseFolder;
    units::Time timeSlice;

    std::shared_ptr<TimeStampSimulator> timestampSimulator;
};

#endif // KILLSIGNALTHREAD_H
