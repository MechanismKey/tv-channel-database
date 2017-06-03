#include "database.h"

using std::unique_ptr;
using std::move;

Database::Database()
{

}

QString Database::tableTitle(const Table_id&& table_id)
{
    QString tableTitle;
    switch(table_id)
    {
    case schedule: tableTitle = "Schedule"; break;
    case employee: tableTitle = "Employee"; break;
    case teamList: tableTitle = "TeamList"; break;
    }
    return tableTitle;
}

void Database::loadTable(const Table_id&& table_id, QTableWidget* tableWidget)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery());

    tableWidget->setRowCount(0);

    switch(table_id)
    {
    case schedule: break;
    case employee:
    {
        tableWidget->setRowCount(Database::countTable(move(table_id)));

        query->exec("SELECT p.surname, p.name, p.second_name, p.birthday, p.itn, e.phone, x.title, e.salary, e.recruitment "
                    "FROM Employee AS e "
                    "JOIN Passport AS p "
                            "ON p.itn = e.id_passport "
                    "JOIN EmployeePost AS x "
                            "ON x.id = e.id_post "
                    );

        QString fullname;
        for(int row = 0; row < tableWidget->rowCount(); ++row)
        {
            query->next();
            fullname = QString(query->value(0).toString() + " " + query->value(1).toString().at(0) + ". " +
                             query->value(2).toString().at(0) + ".");
            tableWidget->setItem(row, 0, new QTableWidgetItem(fullname));
            for(int column = 1; column < tableWidget->columnCount(); ++column)
                tableWidget->setItem(row, column, new QTableWidgetItem(query->value(column).toString()));
        }
    } break;
    case teamList: break;
    };
}


bool Database::addEmployee(const Employee& employee)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery());
    query->prepare( "INSERT INTO Passport(surname, name, second_name, birthday, itn)"
                    "VALUES(:surname, :name, :second_name ,:birthday, :itn)"
                    "INSERT INTO Employee(id_passport, phone, id_post, salary, recruitment)"
                    "VALUES(:itn, :phone, :id_post, :salary, :recruitment)"
                   );

    query->bindValue(":surname", employee.passport.surname);
    query->bindValue(":name", employee.passport.name);
    query->bindValue(":second_name", employee.passport.secondName);
    query->bindValue(":birthday", employee.passport.birthday.toString("yyyy-MM-dd"));
    //    QDate::fromString(ui->lineEdit_Date->text(), "yyyy-MM-dd");
    query->bindValue(":itn", employee.passport.itn);

    query->bindValue(":phone", employee.phone);
    query->bindValue(":id_post", employee.id_post);
    query->bindValue(":salary", employee.salary);
    query->bindValue(":recruitment", employee.recruitment.toString("yyyy-MM-dd"));

    return query->exec();
}
void Database::editEmployee(const Employee& employee)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery());

    query->prepare("UPDATE Employee SET phone=?, id_post=?, salary=? "
                   "WHERE id_passport like '" + employee.passport.itn + "' ");
    query->bindValue(0, employee.phone);
    query->bindValue(1, employee.id_post);
    query->bindValue(2, employee.salary);

    query->exec();
}
bool Database::removeEmployee(const QString& id_passport)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery);
    query->prepare("DELETE from Employee WHERE id_passport like '" + id_passport + "' "+
                   "DELETE from Passport WHERE itn like '" + id_passport + "'");
    if(query->exec())
        return true;
    return false;
}
int Database::countTable(const Table_id&& table_id)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery());

    query->exec("SELECT COUNT (*) FROM " + tableTitle(move(table_id)));

    query->next();

    return query->value(0).toInt();
}

int Database::addPost(const QString&& title)
{
    unique_ptr<QSqlQuery> query(new QSqlQuery());

    query->prepare( "INSERT INTO EmployeePost(title)"
                    "VALUES(:title)"
                  );
    query->bindValue(":title", title);

    query->exec();

    QVariant id = query->lastInsertId();

    if(id.isValid())
        return id.toInt();
    else
        return -1;
}

int Database::getPostId(const QString&& title)
{
    std::unique_ptr<QSqlQuery> query(new QSqlQuery());
    query->exec("SELECT id FROM EmployeePost WHERE title like '" + title + "'");

    if(query->next())
        return query->value(0).toInt();
    else
        return -1;
}

QString Database::getPostName(const int& id_post)
{
    std::unique_ptr<QSqlQuery> query(new QSqlQuery());
    query->exec("SELECT title FROM EmployeePost WHERE id = " + QString::number(id_post));

    if(query->next())
        return query->value(0).toString();
    else
        return "";
}
QStringList Database::listPost()
{
    QStringList listPost;
    std::unique_ptr<QSqlQuery> query(new QSqlQuery());
    query->exec("SELECT title FROM EmployeePost");
    while(query->next())
    {
        listPost.append(query->value(0).toString());
    }
    return listPost;
}
