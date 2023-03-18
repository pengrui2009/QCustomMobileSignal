#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cbx_direction_currentIndexChanged(const QString &arg1);

    void on_lineEdit_timecost_editingFinished();

    void on_lineEdit_title_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
