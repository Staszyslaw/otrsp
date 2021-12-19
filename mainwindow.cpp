#include <QWidget>
#include <QMoveEvent>
#include <QMessageBox>
#include <future>
#include <thread>

#include "mainwindow.h"
#include "windowpos.h"

#include "lib/rs232.h"
#include "./ui_mainwindow.h"

#define WIDTH 730
#define HEIGHT 60

MainWindow::MainWindow(QWidget *parent, miniconf::Config *config)
        : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->config = config;
    connect(ui->connect, &QPushButton::clicked, this, [this]() { on_connect_clicked(); });
    connect(ui->disconnect, &QPushButton::clicked, this, [this]() { on_disconnect_clicked(); });
    connect(ui->pushButton_1, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button1.action").getString() + "\r").c_str(), ui->pushButton_1);
    });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button2.action").getString() + "\r").c_str(), ui->pushButton_2);
    });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button3.action").getString() + "\r").c_str(), ui->pushButton_3);
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button4.action").getString() + "\r").c_str(), ui->pushButton_4);
    });
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button5.action").getString() + "\r").c_str(), ui->pushButton_5);
    });
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button6.action").getString() + "\r").c_str(), ui->pushButton_6);
    });
    connect(ui->pushButton_7, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button7.action").getString() + "\r").c_str(), ui->pushButton_7);
    });
    connect(ui->pushButton_8, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button8.action").getString() + "\r").c_str(), ui->pushButton_8);
    });

    connect(ui->close, &QPushButton::clicked, this, [this]() { on_disconnect_clicked(); exit(0); });

    connect(ui->stayTop, &QCheckBox::stateChanged, this, [this](int state) {
        if (state == Qt::Checked) {
            ui->close->setVisible(true);
            this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
        } else {
            ui->close->setVisible(false);
            this->setWindowFlags(Qt::Widget);
        }
        this->show();
    });

    WindowPos::load();

    setButtonTexts();
    setPosition();
    ui->disconnect->setEnabled(false);
    ui->status->setText("Waiting for connection...");

    // comparing string to true is done to avoid bad value
    if(this->config->operator[]("stayOnTop").getString() == "true") {
        ui->close->setVisible(true);
        ui->stayTop->setChecked(true);
        this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    } else {
        ui->close->setVisible(false);
        ui->stayTop->setChecked(false);
        this->setWindowFlags(Qt::Widget);
    }

    if(this->config->operator[]("autoConnect").getString() == "true") {
//        printf("autoConnect detected\n");
        on_connect_clicked();
    }


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::moveEvent(QMoveEvent *event) {
    int x = event->pos().x();
    int y = event->pos().y();
    WindowPos::x = x;
    WindowPos::y = y;
    WindowPos::save();
}

void MainWindow::setPosition() {
    this->setGeometry(WindowPos::x, WindowPos::y, WIDTH, HEIGHT);
}

void MainWindow::setButtonTexts() {
    ui->pushButton_1->setText(this->config->operator[]("buttons.button1.text").getString().c_str());
    ui->pushButton_2->setText(this->config->operator[]("buttons.button2.text").getString().c_str());
    ui->pushButton_3->setText(this->config->operator[]("buttons.button3.text").getString().c_str());
    ui->pushButton_4->setText(this->config->operator[]("buttons.button4.text").getString().c_str());
    ui->pushButton_5->setText(this->config->operator[]("buttons.button5.text").getString().c_str());
    ui->pushButton_6->setText(this->config->operator[]("buttons.button6.text").getString().c_str());
    ui->pushButton_7->setText(this->config->operator[]("buttons.button7.text").getString().c_str());
    ui->pushButton_8->setText(this->config->operator[]("buttons.button8.text").getString().c_str());
}

void MainWindow::on_pushButton_clicked(const char *data, QPushButton *btn) const {
    if (this->connected) {
        RS232_cputs(this->portnr, (const char *) data);
    } else {
        QMessageBox::warning((QWidget *) this, "Error", "Not connected to a device!", QMessageBox::Ok, QMessageBox::Ok);
    }
    // Restart checked of each button
    ui->pushButton_1->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_8->setChecked(false);

    // Set color of button that was clicked
    btn->setChecked(true);

}

void MainWindow::on_connect_clicked() {
    std::string portStr = this->config->operator[]("serial.port").getString();
    printf("Connecting to %s\n", portStr.c_str());
    this->portnr = RS232_GetPortnr(this->config->operator[]("serial.port").getString().c_str());
    if (this->portnr < 0) {
        ui->status->setText("Could not find serial port");
        return;
    }
    // Open serial port on portnr with baudrate from config, 8 bits, no parity, 1 stop bit, no hardware flow control
    if (RS232_OpenComport(this->portnr, std::stoi(this->config->operator[]("serial.baudrate").getString()), "8N1", 0)) {
        connected = false;
        ui->status->setText("Problem with opening serial port");
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
