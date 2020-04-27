#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

double oldNum = 0;
bool resetNum = false;
bool add = false;
bool sub = false;
bool mul = false;
bool divi = false;
bool twoOp = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_dot,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_per,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_sq,SIGNAL(released()),this,SLOT(pressB()));
    connect(ui->pushButton_C,SIGNAL(released()),this,SLOT(del()));
    connect(ui->pushButton_add,SIGNAL(released()),this,SLOT(op()));
    connect(ui->pushButton_sub,SIGNAL(released()),this,SLOT(op()));
    connect(ui->pushButton_mul,SIGNAL(released()),this,SLOT(op()));
    connect(ui->pushButton_div,SIGNAL(released()),this,SLOT(op()));
    connect(ui->pushButton_eq,SIGNAL(released()),this,SLOT(op()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressB()
{
    QPushButton* currentB = (QPushButton*)sender();
    if(currentB->text() == ".")
    {
        if(resetNum)
        {
            ui->disp->setText("0.");
            resetNum = false;
            twoOp = false;
            return;
        }
        else if(ui->disp->text().contains(".")) return;
        else
        {
            ui->disp->setText(ui->disp->text() + ".");
            twoOp = false;
            return;
        }

    }
    else if (ui->disp->text().contains(".") && currentB->text() == "0")
    {
        ui->disp->setText(ui->disp->text() + "0");
        twoOp = false;
        return;
    }
    if(currentB->text() == "%")
    {
        ui->disp->setText(QString::number((ui->disp->text().toDouble() / 100),'g',12));
        return;
    }
    if(currentB->text() == "^2")
    {
        ui->disp->setText(QString::number((ui->disp->text().toDouble() * ui->disp->text().toDouble()),'g',12));
        return;
    }
    QString strNum;
    if(resetNum) { strNum = currentB->text(); resetNum = false; }
    else strNum = ui->disp->text() + currentB->text();
    double num = strNum.toDouble();
    strNum = QString::number(num,'g',12);
    twoOp = false;
    if (strNum.size() > 15) return;
    ui->disp->setText(strNum);
}

void MainWindow::del()
{
    oldNum = 0;
    resetNum = false;
    add = false;
    sub = false;
    mul = false;
    divi = false;
    twoOp = false;
    ui->disp->setText("0");
}

void MainWindow::op()
{
    QPushButton* currentB = (QPushButton*)sender();
    double secondNum = ui->disp->text().toDouble();
    resetNum = true;

    if(add && !twoOp)
    {
        ui->disp->setText(QString::number((oldNum + secondNum),'g',12));
        add = false;
        oldNum = ui->disp->text().toDouble();
    }
    else if(sub && !twoOp)
    {
        ui->disp->setText(QString::number((oldNum - secondNum),'g',12));
        sub = false;
        oldNum = ui->disp->text().toDouble();
    }
    else if(mul && !twoOp)
    {
        ui->disp->setText(QString::number((oldNum * secondNum),'g',12));
        mul = false;
        oldNum = ui->disp->text().toDouble();
    }
    else if(divi && !twoOp)
    {
        ui->disp->setText(QString::number((oldNum / secondNum),'g',12));
        divi = false;
        oldNum = ui->disp->text().toDouble();
    }
    oldNum = ui->disp->text().toDouble();

    if(twoOp)
    {
        add = false;
        sub = false;
        mul = false;
        divi = false;
    }

    if(currentB->text() == "+")
        add = true;
    if(currentB->text() == "-")
        sub = true;
    if(currentB->text() == "*")
        mul = true;
    if(currentB->text() == "/")
        divi = true;
    twoOp = true;
}

