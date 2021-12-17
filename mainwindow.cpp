#include "mainwindow.h"
#include "lib/rs232.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, miniconf::Config* config)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->config = config;
    connect(ui->connect, &QPushButton::clicked, this, [this](){ on_connect_clicked(); });
    connect(ui->disconnect, &QPushButton::clicked, this, [this](){ on_disconnect_clicked(); });
    connect(ui->pushButton_1, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX11\r"); });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX12\r"); });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX13\r"); });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX14\r"); });
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX15\r"); });
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX16\r"); });
    connect(ui->pushButton_7, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX17\r"); });
    connect(ui->pushButton_8, &QPushButton::clicked, this, [this](){ on_pushButton_clicked("AUX18\r"); });

    setButtonTexts();
    setLabelTexts();
    ui->disconnect->setEnabled(false);
    ui->status->setText("Waiting for connection...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonTexts() {
    ui->pushButton_1->setText(this->config->operator[]("buttons.button1").getString().c_str());
    ui->pushButton_2->setText(this->config->operator[]("buttons.button2").getString().c_str());
    ui->pushButton_3->setText(this->config->operator[]("buttons.button3").getString().c_str());
    ui->pushButton_4->setText(this->config->operator[]("buttons.button4").getString().c_str());
    ui->pushButton_5->setText(this->config->operator[]("buttons.button5").getString().c_str());
    ui->pushButton_6->setText(this->config->operator[]("buttons.button6").getString().c_str());
    ui->pushButton_7->setText(this->config->operator[]("buttons.button7").getString().c_str());
    ui->pushButton_8->setText(this->config->operator[]("buttons.button8").getString().c_str());
}

void MainWindow::setLabelTexts() {
    ui->label_1->setText(this->config->operator[]("description.button1").getString().c_str());
    ui->label_2->setText(this->config->operator[]("description.button2").getString().c_str());
    ui->label_3->setText(this->config->operator[]("description.button3").getString().c_str());
    ui->label_4->setText(this->config->operator[]("description.button4").getString().c_str());
    ui->label_5->setText(this->config->operator[]("description.button5").getString().c_str());
    ui->label_6->setText(this->config->operator[]("description.button6").getString().c_str());
    ui->label_7->setText(this->config->operator[]("description.button7").getString().c_str());
    ui->label_8->setText(this->config->operator[]("description.button8").getString().c_str());
}

void MainWindow::on_pushButton_clicked(const char *data) const {
    if (this->connected) {
        RS232_cputs(this->portnr, (const char *) data);
    }
}

void MainWindow::on_connect_clicked() {
    std::string portStr = "/dev/" + this->config->operator[]("serial.port").getString();
    printf("Connecting to %s\n", portStr.c_str());
    this->portnr = RS232_GetPortnr(this->config->operator[]("serial.port").getString().c_str());
    if(this->portnr < 0) {
	    ui->status->setText("Could not find serial port");
	    return;
    }
    if(RS232_OpenComport(this->portnr, std::stoi(this->config->operator[]("serial.baudrate").getString()), "8N1", 0)) {
        connected = false;
        ui->status->setText("There was a problem opening the serial port");
    } else {
        connected = true;
        ui->connect->setEnabled(false);
        ui->disconnect->setEnabled(true);
        ui->status->setText("Connected");
    }
}

void MainWindow::on_disconnect_clicked() const {
    RS232_CloseComport(this->portnr);
    ui->connect->setEnabled(true);
    ui->disconnect->setEnabled(false);
    ui->status->setText("Disconnected");
}
