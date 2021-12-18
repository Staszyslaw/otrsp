#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "lib/rs232.h"
#include "lib/miniconf.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    bool connected = false;
    MainWindow(QWidget *parent = nullptr, miniconf::Config* config = nullptr);
    ~MainWindow();
    void moveEvent(QMoveEvent *event) override;
    void setButtonTexts();
    void setLabelTexts();
    void setPosition();
    void on_connect_clicked();
    void on_disconnect_clicked() const;
    void on_pushButton_clicked(const char *data) const;

private:
    int portnr = -1;
    Ui::MainWindow *ui;
    miniconf::Config *config;

};
#endif // MAINWINDOW_H
