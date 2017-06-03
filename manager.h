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


namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

    enum Form {tables, employee};
    enum EmployeeMode {add, edit};

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

private slots:
    void on_listWidget_itemSelectionChanged();

    void on_pushButton_toAddEmployee_clicked();

    void on_tableWidget_Employee_cellPressed(int row, int column);

    void on_pushButton_backFromEmployee_clicked();

    void on_pushButton_Employee_clicked();

    void on_pushButton_changeEmployee_clicked();

    void on_pushButton_deleteEmployee_clicked();

private:
    Ui::Manager *ui;

    EmployeeMode employee_mode;


    void loadAllTables();

    void loadComboPost();
    int getCurrentPost();

    void editInTableWidgetEmployee(const Employee& employee);
    void addToTableWidgetEmployee(const Employee& employee);
    void removeFromTableWidgetEmployee(const QString &itn);

    void clearEmployee();
    void fillEmployee(const int&& row);
    void setEmployeeReadOnly(const bool answer);
    void setEmployeeMode(const EmployeeMode&& mode);
    void setEmployeeEdit();
};

#endif // MANAGER_H
