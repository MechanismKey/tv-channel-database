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
    enum Table_id { schedule, employee, teamList};

    Database();

    static void loadTable(const Table_id&& table_id, QTableWidget* tableWidget);

    static bool addEmployee(const Employee& employee);
    static int addPost(const QString&& title);

    static int id_post(const QString&& title);
    static QStringList listPost();

    static int countTable(const Table_id&& table);

private:
    static QString tableTitle(const Table_id&& table_id);
};

#endif // DATABASE_H
