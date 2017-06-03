#include "employee.h"
#include <QDebug>
Employee::Employee(Passport& passportX, const QString&& phoneX, const int&& id_postX, const int& salaryX,
                   const QDate&& recruitmentX) :
    passport(passportX), phone(phoneX), id_post(id_postX), salary(salaryX), recruitment(recruitmentX)
{

}

bool Employee::isValid() const
{
    if(!passport.isValid()) return false;
    if(phone.size()!=17) return false;
    if(id_post < 0) return false;
    if(salary < 10) return false;

    return true;
}
