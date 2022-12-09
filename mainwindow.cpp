#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),check(true)
{
    ui->setupUi(this);

    QLabel* output = new QLabel;
    output->setText("Hello");
    output->setParent(this);
    output->setAlignment(Qt::AlignCenter);
    output->setGeometry(0,0,0,0);

    ui->gridLayout_4->addWidget(output);

    Algorithm = new StepCounterAlgo(output);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Algorithm;
    delete runThread;
}

void MainWindow::on_Start_clicked()
{
    check = true;
    Algorithm->setCheckButton(check);
    runThread = new std::thread(&StepCounterAlgo::run,Algorithm);
    runThread->detach();
}

void MainWindow::on_reset_clicked()
{
    Algorithm->reset();
}

void MainWindow::on_Stop_clicked()
{
    check = false;
    Algorithm->setCheckButton(check);
}









