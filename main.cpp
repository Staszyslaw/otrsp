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
            .defaultValue("ttyUSB0").required(true)
            .description("Serial port connected to OTRSP device");

    conf.option("serial.baudrate").shortflag("b").defaultValue("9600").required(true)
    .description("Baudrate of serial port");

    conf.option("autoConnect").shortflag("a").defaultValue("false").required(true)
    .description("Auto connect to OTRSP device");
    conf.option("stayOnTop").shortflag("t").defaultValue("false").required(true)
    .description("Stay on top of all windows");


    // Button 1 config
    conf.option("buttons.button1.text").shortflag("b1").defaultValue("Button 1").required(false)
            .description("Text on button 1");
    conf.option("buttons.button1.action").shortflag("b1a").defaultValue("AUX11").required(false)
            .description("Action on button 1");

    // Button 2 config
    conf.option("buttons.button2.text").shortflag("b2").defaultValue("Button 2").required(false)
            .description("Text on button 2");
    conf.option("buttons.button2.action").shortflag("b2a").defaultValue("AUX12").required(false)
            .description("Action on button 2");

    // Button 3 config
    conf.option("buttons.button3.text").shortflag("b3").defaultValue("Button 3").required(false)
            .description("Text on button 3");
    conf.option("buttons.button3.action").shortflag("b3a").defaultValue("AUX13").required(false)
            .description("Action on button 3");

    // Button 4 config
    conf.option("buttons.button4.text").shortflag("b4").defaultValue("Button 4").required(false)
            .description("Text on button 4");
    conf.option("buttons.button4.action").shortflag("b4a").defaultValue("AUX14").required(false)
            .description("Action on button 4");

    // Button 5 config
    conf.option("buttons.button5.text").shortflag("b5").defaultValue("Button 5").required(false)
            .description("Text on button 5");
    conf.option("buttons.button5.action").shortflag("b5a").defaultValue("AUX15").required(false)
            .description("Action on button 5");

    // Button 6 config
    conf.option("buttons.button6.text").shortflag("b6").defaultValue("Button 6").required(false)
            .description("Text on button 6");
    conf.option("buttons.button6.action").shortflag("b6a").defaultValue("AUX16").required(false)
            .description("Action on button 6");

    // Button 7 config
    conf.option("buttons.button7.text").shortflag("b7").defaultValue("Button 7").required(false)
            .description("Text on button 7");
    conf.option("buttons.button7.action").shortflag("b7a").defaultValue("AUX17").required(false)
            .description("Action on button 7");

    // Button 8 config
    conf.option("buttons.button8.text").shortflag("b8").defaultValue("Button 8").required(false)
            .description("Text on button 8");
    conf.option("buttons.button8.action").shortflag("b8a").defaultValue("AUX18").required(false)
            .description("Action on button 8");

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
