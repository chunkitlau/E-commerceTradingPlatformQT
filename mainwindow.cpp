#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socketInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::socketInit() {
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress("127.0.0.1"), 8000);
    QObject::connect(socket, SIGNAL(readyRead()),this, SLOT(display()));
    return SUCCESS;
}

int MainWindow::display() {
    std::string string;
    read(string);
    qDebug() << QString::fromStdString(string);
    if (isSignIn) {
        if (isSignIn == 3) {
            isSignIn = -1;
            ui->userName->setText(QString::fromStdString(string).split(" ")[2]);
        }
        ui->output->setText(QString::fromStdString(string));
        ++isSignIn;
    }
    else if (isGetBalance) {
        isGetBalance = 0;
        ui->balance->setText(QString::fromStdString(string).split(" ")[5]);
        ui->output->setText(QString::fromStdString(string));
    }
    else if (isShowCommodity) {
        isShowCommodity = 0;
        ui->commodity->setText(QString::fromStdString(string));
    }
    else if (isShowInCart) {
        isShowInCart = 0;
        ui->shoppingCart->setText(QString::fromStdString(string));
    }
    else if (isShowOrders) {
        isShowOrders = 0;
        ui->orders->setText(QString::fromStdString(string));
    }
    else {
        ui->output->setText(QString::fromStdString(string));
    }
    return SUCCESS;
}

int MainWindow::read(std::string &string) {
    char buf[BUFSIZE];
    memset(buf, 0, sizeof(buf));
    std::string strin;
    socket->read(buf, sizeof(buf));
    int len = strlen(buf) + 1;
    qDebug() << len;
    //int len = recv(Client::client, buf, sizeof(buf), 0);
    buf[len] = '\0';
    string = std::string(buf);
    return SUCCESS;
}

int MainWindow::write(std::string string) {
    char buf[BUFSIZE];
    int len = string.copy(buf, BUFSIZE);
    buf[len] = '\0';
    socket->write(buf, len);
    //send(Client::client, buf, len, 0);
    return SUCCESS;
}

void MainWindow::on_send_clicked()
{
    std::string string = ui->input->text().toStdString();
    write(string);
}

void MainWindow::on_signUp_clicked()
{
    write("1");
}


void MainWindow::on_signIn_clicked()
{
    write("4");
    isSignIn = 1;
}


void MainWindow::on_signOut_clicked()
{
    write("5");
}


void MainWindow::on_editPassword_clicked()
{
    write("6");
}

void MainWindow::on_consume_clicked()
{
    write("8");
}


void MainWindow::on_charge_clicked()
{
    write("12");
}


void MainWindow::on_addToCart_clicked()
{
    write("13");
}


void MainWindow::on_deleteInCart_clicked()
{
    write("14");
}


void MainWindow::on_editInCart_clicked()
{
    write("15");
}


void MainWindow::on_generateOrders_clicked()
{
    write("17");
}


void MainWindow::on_cancelOrders_clicked()
{
    write("18");
}


void MainWindow::on_pay_clicked()
{
    write("20");
}


void MainWindow::on_addCommodity_clicked()
{
    write("9");
}


void MainWindow::on_editPrice_clicked()
{
    write("10");
}


void MainWindow::on_editAmount_clicked()
{
    write("11");
}


void MainWindow::on_searchCommodity_clicked()
{
    write("3");
}


void MainWindow::on_exit_clicked()
{
    write("0");
}


void MainWindow::on_getBalance_clicked()
{
    write("7");
    isGetBalance = 1;
}


void MainWindow::on_showCommodity_clicked()
{
    write("2");
    isShowCommodity = 1;
}


void MainWindow::on_showInCart_clicked()
{
    write("16");
    isShowInCart = 1;
}


void MainWindow::on_showOrders_clicked()
{
    write("19");
    isShowOrders = 1;
}


void MainWindow::on_discount_clicked()
{
    write("21");
}

