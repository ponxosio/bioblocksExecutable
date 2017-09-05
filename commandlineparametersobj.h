#ifndef COMMANDLINEPARAMETERSOBJ_H
#define COMMANDLINEPARAMETERSOBJ_H

#include <memory>
#include <string>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <communications/CommandSender.h>
#include <communications/FileSender.h>
#include <communications/SerialSender.h>

#include <utils/units.h>
#include <utils/utilsjson.h>
#include <utils/timestampsimulator.h>

class CommandLineParametersObj
{
public:
    static CommandLineParametersObj parseCommandLineArguments(const QCoreApplication & app);

    virtual ~CommandLineParametersObj(){}

    inline const std::string & getPluginFolderPath() const {
        return pluginFolderPath;
    }

    inline const std::string & getPluginBaseFolderPath() const {
        return pluginBaseFolderPath;
    }

    inline const std::string & getProtocolFilePath() const {
        return protocolFilePath;
    }

    inline const std::string & getMachineFilePath() const {
        return machineFilePath;
    }

    inline const units::Time & getTimeSlice() const {
        return timeSlice;
    }

    inline std::shared_ptr<CommandSender> getCommand() const {
        return command;
    }

    inline std::shared_ptr<TimeStampSimulator> getSimulateTimestamp() const {
        return timestampManager;
    }

protected:
    static void fillParserObj(QCommandLineParser & parser);

    CommandLineParametersObj(){}

    std::string pluginFolderPath;
    std::string pluginBaseFolderPath;
    std::string protocolFilePath;
    std::string machineFilePath;
    units::Time timeSlice;

    std::shared_ptr<CommandSender> command;
    std::shared_ptr<TimeStampSimulator> timestampManager;
    bool simulateTime;
};

#endif // COMMANDLINEPARAMETERSOBJ_H
