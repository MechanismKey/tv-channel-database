#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>

#include <database.h>

#include <QtSql/QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>

#include <QTableView>
#include <QComboBox>


#include <QDebug>

namespace Form
{
    enum { Tables, AddEmployee};
}

namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

private slots:
    void on_listWidget_itemSelectionChanged();

    void on_pushButton_toAddEmployee_clicked();

    void on_pushButton_toEditEmployee_clicked();

    void on_pushButton_backFromAddEmployee_clicked();

    void on_pushButton_addEmployee_clicked();

    void on_tableWidget_Employee_cellPressed(int row, int column);

private:
    Ui::Manager *ui;

    QSqlTableModel* model;

    void loadComboPost();
    void loadAllTables();

    int getCurrentPost();
};

#endif // MANAGER_H
