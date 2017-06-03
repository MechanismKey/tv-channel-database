#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include <database.h>
#include <authorization.h>
#include <manager.h>


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
    void logged(QString nickname);

private:
    Ui::MainWindow *ui;

    Authorization* authorization;
    Manager* manager;

    QSqlDatabase DB;
};

#endif // MAINWINDOW_H
