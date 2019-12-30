#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FloatCanculator backFloat;
    connect(&backFloat , SIGNAL(FloatToMain()) , this , SLOT(ReveiveFloat()));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_floatCanculate_clicked()
{
    FloatCanculator jump;
    jump.exec();
}
//void MainWindow::ReceiveFloat()
//{
//    this->show();
//}
void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->Time->setText(str);
}

void MainWindow::on_MatrixCalculate_clicked()
{
    MatrixFunction jump;
    jump.exec();
}
