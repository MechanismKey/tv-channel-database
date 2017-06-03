#include "passport.h"

Passport::Passport(const QString&& surnameX, const QString&& nameX, const QString&& secondNameX,
                   const QDate&& birthdayX, const int&& itnX) :
    surname(surnameX), name(nameX), secondName(secondNameX), birthday(birthdayX), itn(itnX)
{

}

bool Passport::isValid() const
{
    if(surname.isEmpty()) return false;
    if(name.isEmpty()) return false;
    if(secondName.isEmpty()) return false;
    if(QString::number(itn).size() != 10) return false;

    return true;
}
