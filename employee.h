#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <passport.h>

class Employee
{
public:
    Employee(Passport& passportX, const QString&& phoneX, const int&& id_postX, const int& salaryX,
             const QDate&& recruitmentX);

    bool isValid() const;

    Passport& passport;
    QString phone;
    int id_post;
    int salary;
    QDate recruitment;
};

#endif // EMPLOYEE_H
