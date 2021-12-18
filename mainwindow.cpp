#include <QWidget>
#include <QMoveEvent>
#include "mainwindow.h"
#include "lib/rs232.h"
#include "windowpos.h"
#include "./ui_mainwindow.h"

#define WIDTH 730
#define HEIGHT 100
#define HIDDEN_HEIGHT 52

MainWindow::MainWindow(QWidget *parent, miniconf::Config *config)
        : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->config = config;
    connect(ui->connect, &QPushButton::clicked, this, [this]() { on_connect_clicked(); });
    connect(ui->disconnect, &QPushButton::clicked, this, [this]() { on_disconnect_clicked(); });
    connect(ui->pushButton_1, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button1.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button2.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button3.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button4.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button5.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button6.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_7, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button7.action").getString() + "\r").c_str());
    });
    connect(ui->pushButton_8, &QPushButton::clicked, this, [this]() {
        on_pushButton_clicked((this->config->operator[]("buttons.button8.action").getString() + "\r").c_str());
    });

    connect(ui->stayTop, &QCheckBox::stateChanged, this, [this](int state) {
        if (state == Qt::Checked) {
            this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
        } else {
            this->setWindowFlags(Qt::Widget);
        }
        this->show();
    });

    connect(ui->expand, &QCheckBox::stateChanged, this, [this](int state) {
        if (state == Qt::Checked) {
            this->setFixedSize(WIDTH, HEIGHT);
            // move bottomBar to the bottom
            ui->bottomBar->move(0, HEIGHT - 16);
            ui->label_1->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_5->setVisible(true);
            ui->label_6->setVisible(true);
            ui->label_7->setVisible(true);
            ui->label_8->setVisible(true);
            ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
            ui->horizontalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        } else {
            this->setFixedSize(WIDTH, HIDDEN_HEIGHT);
            // move bottomBar to the bottom
            ui->bottomBar->move(0, HIDDEN_HEIGHT - 16);
            ui->label_1->setVisible(false);
            ui->label_2->setVisible(false);
            ui->label_3->setVisible(false);
            ui->label_4->setVisible(false);
            ui->label_5->setVisible(false);
            ui->label_6->setVisible(false);
            ui->label_7->setVisible(false);
            ui->label_8->setVisible(false);
            ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
            ui->horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        }
        this->show();
    });



    if(this->config->operator[]("autoConnect").getString() == "true") {
        on_connect_clicked();
    }

    WindowPos::load();

    setButtonTexts();
    setLabelTexts();
    setPosition();
    ui->disconnect->setEnabled(false);
    ui->status->setText("Waiting for connection...");
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

void MainWindow::setLabelTexts() {
    ui->label_1->setText(this->config->operator[]("buttons.button1.label").getString().c_str());
    ui->label_2->setText(this->config->operator[]("buttons.button2.label").getString().c_str());
    ui->label_3->setText(this->config->operator[]("buttons.button3.label").getString().c_str());
    ui->label_4->setText(this->config->operator[]("buttons.button4.label").getString().c_str());
    ui->label_5->setText(this->config->operator[]("buttons.button5.label").getString().c_str());
    ui->label_6->setText(this->config->operator[]("buttons.button6.label").getString().c_str());
    ui->label_7->setText(this->config->operator[]("buttons.button7.label").getString().c_str());
    ui->label_8->setText(this->config->operator[]("buttons.button8.label").getString().c_str());
}

void MainWindow::on_pushButton_clicked(const char *data) const {
    if (this->connected) {
        RS232_cputs(this->portnr, (const char *) data);
    }
}

void MainWindow::on_connect_clicked() {
    std::string portStr = this->config->operator[]("serial.port").getString();
    printf("Connecting to %s\n", portStr.c_str());
    this->portnr = RS232_GetPortnr(this->config->operator[]("serial.port").getString().c_str());
    if (this->portnr < 0) {
        ui->status->setText("Could not find serial port");
        return;
    }
    if (RS232_OpenComport(this->portnr, std::stoi(this->config->operator[]("serial.baudrate").getString()), "8N1", 0)) {
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
