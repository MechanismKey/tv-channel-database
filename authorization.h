#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>

namespace Ui {
class Authorization;
}

class Authorization : public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QSqlDatabase& linkDB, QWidget *parent = 0);
    ~Authorization();

    QMessageBox* message;

signals:
    void logged(QString nickname);

private slots:
    void on_buttonLogIn_clicked();

private:
    Ui::Authorization *ui;

    QSqlDatabase& DB;
};

#endif // AUTHORIZATION_H
