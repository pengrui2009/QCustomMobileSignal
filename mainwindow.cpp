#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList strlist;
    strlist << "Left";
    strlist << "Right";
    ui->cbx_direction->addItems(strlist);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cbx_direction_currentIndexChanged(const QString &arg1)
{
    QString str = ui->cbx_direction->currentText();

    if (str == "Left")
    {
        ui->widget->setPosition(QCustomMobileSignal::POSITION_LEFT_TOP);
    } else if (str == "Right") {
        ui->widget->setPosition(QCustomMobileSignal::POSITION_RIGHT_TOP);
    } else {
        ui->widget->setPosition(QCustomMobileSignal::POSITION_CENTER_TOP);
    }
}

void MainWindow::on_lineEdit_timecost_editingFinished()
{
    double timecost = 0.0;

    timecost = ui->lineEdit_timecost->text().toDouble();

    ui->widget->setTimeCost(timecost);
}

void MainWindow::on_lineEdit_title_editingFinished()
{
    QString str = ui->lineEdit_title->text();

    ui->widget->setTitle(str);
}
