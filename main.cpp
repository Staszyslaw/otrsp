#include <cstdio>
#include <sys/stat.h>
#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

bool check_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

miniconf::Config readConfig(int argc, char *argv[]) {
    miniconf::Config conf; // Create config object

    conf.description("OTRSP config v1");

    conf.option("serial.port").shortflag("s")
            .defaultValue("/dev/ttyUSB0").required(true)
            .description("Serial port connected to OTRSP device");

    conf.option("serial.baudrate").shortflag("b").defaultValue("9600").required(true)
    .description("Baudrate of serial port");
    conf.option("serial.timeout").shortflag("t").defaultValue("1000").required(true)
    .description("Timeout for serial port");

    // Text on buttons
    conf.option("buttons.button1").shortflag("b1").defaultValue("Button 1").required(false)
            .description("Text on button 1");
    conf.option("buttons.button2").shortflag("b2").defaultValue("Button 2").required(false)
            .description("Text on button 2");
    conf.option("buttons.button3").shortflag("b3").defaultValue("Button 3").required(false)
            .description("Text on button 4");
    conf.option("buttons.button4").shortflag("b4").defaultValue("Button 4").required(false)
            .description("Text on button 4");
    conf.option("buttons.button5").shortflag("b5").defaultValue("Button 5").required(false)
            .description("Text on button 5");
    conf.option("buttons.button6").shortflag("b6").defaultValue("Button 6").required(false)
            .description("Text on button 6");
    conf.option("buttons.button7").shortflag("b7").defaultValue("Button 7").required(false)
            .description("Text on button 7");
    conf.option("buttons.button8").shortflag("b8").defaultValue("Button 8").required(false)
            .description("Text on button 8");

    // Labels below buttons
    conf.option("description.button1").shortflag("d1").defaultValue("Config 1").required(false)
            .description("Description on button 1");
    conf.option("description.button2").shortflag("d2").defaultValue("Config 2").required(false)
            .description("Description on button 2");
    conf.option("description.button3").shortflag("d3").defaultValue("Config 3").required(false)
            .description("Description on button 3");
    conf.option("description.button4").shortflag("d4").defaultValue("Config 4").required(false)
            .description("Description on button 4");
    conf.option("description.button5").shortflag("d5").defaultValue("Config 5").required(false)
            .description("Description on button 5");
    conf.option("description.button6").shortflag("d6").defaultValue("Config 6").required(false)
            .description("Description on button 6");
    conf.option("description.button7").shortflag("d7").defaultValue("Config 7").required(false)
            .description("Description on button 7");
    conf.option("description.button8").shortflag("d8").defaultValue("Config 8").required(false)
            .description("Description on button 8");

    conf.config("config.json");

    if(!check_exists("config.json")) {
        if (conf.parse(argc, argv)) {
            printf("Config file parsed successfully\n");
            conf.serialize("config.json", miniconf::Config::ExportFormat::JSON);
            conf.config("config.json");
        }
    }

    return conf;
}

int main(int argc, char *argv[]) {

    auto config = readConfig(argc, argv);

    QApplication a(argc, argv);
    MainWindow w(nullptr, &config);

    w.show();
    return QApplication::exec();
}
