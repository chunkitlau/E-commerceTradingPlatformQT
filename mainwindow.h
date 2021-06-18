#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>
#include <QDebug>
#include "ui_mainwindow.h"

#define ERROR1 1
#define SUCCESS 0
#define BUFSIZE 10240

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int socketInit();
    int read(std::string &string);
    int write(std::string string);
private slots:
    void on_pushButton_clicked();
    int display();
    void on_signUp_clicked();

    void on_signIn_clicked();

    void on_signOut_clicked();

    void on_editPassword_clicked();

    void on_send_clicked();

    void on_consume_clicked();

    void on_charge_clicked();

    void on_addToCart_clicked();

    void on_deleteInCart_clicked();

    void on_editInCart_clicked();

    void on_generateOrders_clicked();

    void on_cancelOrders_clicked();

    void on_pay_clicked();

    void on_addCommodity_clicked();

    void on_editPrice_clicked();

    void on_editAmount_clicked();

    void on_searchCommodity_clicked();

    void on_exit_clicked();

    void on_getBalance_clicked();

    void on_showCommodity_clicked();

    void on_showInCart_clicked();

    void on_showOrders_clicked();

    void on_discount_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int isSignIn = 0, isGetBalance = 0, isShowCommodity = 0, isShowInCart = 0, isShowOrders = 0;
};
#endif // MAINWINDOW_H
