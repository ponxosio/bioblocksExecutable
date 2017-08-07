#include "commandlineparametersobj.h"

CommandLineParametersObj CommandLineParametersObj::parseCommandLineArguments(const QCoreApplication & app) {
    QCommandLineParser parser;
    fillParserObj(parser);
    parser.process(app);

    CommandLineParametersObj obj;
    obj.pluginFolderPath = parser.value("plugin_folder").toStdString();
    obj.pluginBaseFolderPath = parser.value("plugin_base_folder").toStdString();
    obj.protocolFilePath = parser.value("protocol").toStdString();
    obj.machineFilePath = parser.value("machine").toStdString();

    std::string timeValue = parser.value("time").toStdString();
    std::string timeUnits = parser.value("time_units").toStdString();
    obj.timeSlice = std::atof(timeValue.c_str()) * UtilsJSON::getTimeUnits(timeUnits);

    std::shared_ptr<CommandSender> command;
    if (parser.isSet("simulate_execute")) {
        std::string serialPort = parser.value("port").toStdString();
        std::string baudrateStr = parser.value("baud_rate").toStdString();

        qint32 baudRate = std::atoi(baudrateStr.c_str());
        command = std::make_shared<SerialSender>(serialPort, baudRate);
    } else {
        std::string outFile = parser.value("out_file").toStdString();
        std::string dataFile = parser.value("data_file").toStdString();

        command = std::make_shared<FileSender>(outFile, dataFile);
    }
    obj.command = command;
    return obj;
}

void CommandLineParametersObj::fillParserObj(QCommandLineParser & parser) {
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption protocolFileOption(QStringList() << "protocol" << "p",
                                          QCoreApplication::translate("main", "Protocol executable JSON file"),
                                          "protocol");
    parser.addOption(protocolFileOption);

    QCommandLineOption machineFileOption(QStringList() << "machine" << "m",
                                         QCoreApplication::translate("main", "Machine executable JSON file"),
                                         "machine");
    parser.addOption(machineFileOption);

    QCommandLineOption timeSliceOption(QStringList() << "time" << "t",
                                       QCoreApplication::translate("main", "Time Slice value, format [double_value]"),
                                       "time");
    parser.addOption(timeSliceOption);

    QCommandLineOption timeSliceUnitsOption(QStringList() << "time_units" << "u",
                                       QCoreApplication::translate("main", "Time Slice units, format [ms,s,minute,h,hr]"),
                                       "time_units");
    parser.addOption(timeSliceUnitsOption);

    QCommandLineOption serialCommandOption("simulate_execute",
                                           QCoreApplication::translate("main", "execute the protocol using the serial command to communicate with the machine, add --port and --baudrates. If not simulates the protocols add --out_file and --data_file"));
    parser.addOption(serialCommandOption);

    QCommandLineOption baudRateOption("baud_rate",
                                      QCoreApplication::translate("main", "only use it with the serial command, specifies the baud rate of the connection"),
                                      "baud_rate");
    parser.addOption(baudRateOption);

    QCommandLineOption portOption("port",
                                  QCoreApplication::translate("main", "only use it with the serial command, specifies the the port to connect with"),
                                  "port");
    parser.addOption(portOption);

    QCommandLineOption outFileOption("out_file",
                                     QCoreApplication::translate("main", "only use it with out the serial command, specifies the file where the output of the execution is save"),
                                     "out_file");
    parser.addOption(outFileOption);

    QCommandLineOption dataFileOption("data_file",
                                      QCoreApplication::translate("main", "only use it with out the serial command, specifies the file where the protocol read data from"),
                                      "data_file");
    parser.addOption(dataFileOption);

    QCommandLineOption pluginFolderOption("plugin_folder",
                                          QCoreApplication::translate("main", "path to the folder with the plugins"),
                                          "plugin_folder");
    parser.addOption(pluginFolderOption);

    QCommandLineOption pluginBaseFolder("plugin_base_folder",
                                        QCoreApplication::translate("main", "path to the folder with the base plugins"),
                                        "plugin_base_folder");
    parser.addOption(pluginBaseFolder);
}

