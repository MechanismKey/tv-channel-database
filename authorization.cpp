#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QSqlDatabase &linkDB, QWidget *parent) :
    DB(linkDB), QWidget(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

    ui->editPassword->setEchoMode(QLineEdit::Password);

    message = new QMessageBox();

    ui->editNickname->setText("admin");
    ui->editPassword->setText("23maxim23");
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_buttonLogIn_clicked()
{
    DB = QSqlDatabase::addDatabase("QODBC");
    DB.setDatabaseName("DRIVER={SQL Server};SERVER=MONKEYKING\\SQLEXPRESS;DATABASE=MainDB;");
    DB.setUserName(ui->editNickname->text());
    DB.setPassword(ui->editPassword->text());

    //admin
    //23maxim23
    if(DB.open())
    {
        emit logged(ui->editNickname->text());
    }
    else
    {
        message->setText("Соединение не установлено");
        message->show();
    }


}
