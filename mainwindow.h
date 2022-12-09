#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stepcounteralgo.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    bool check;
    StepCounterAlgo *Algorithm;
    std::thread *runThread;
    QLabel *output;

private slots:
    void on_Start_clicked();
    void on_reset_clicked();
    void on_Stop_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H
