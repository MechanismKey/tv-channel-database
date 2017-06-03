#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQuery>
#include <Qstring>
#include <QVariant>
#include <memory>
#include <QDebug>
#include <QTableWidget>
#include <employee.h>
#include <passport.h>

class Database
{
public:
    enum Table_id {schedule, employee, teamList};

    Database();

    static void loadTable(const Table_id&& table_id, QTableWidget* tableWidget);

    static bool addEmployee(const Employee& employee);
    static int addPost(const QString&& title);

    static bool removeEmployee(const QString& id_passport);

    static void editEmployee(const Employee& employee);

    static int getPostId(const QString&& title);
    static QString getPostName(const int& id_post);
    static QStringList listPost();

    static int countTable(const Table_id&& table);

private:
    static QString tableTitle(const Table_id&& table_id);
};

#endif // DATABASE_H
