#ifndef PASSPORT_H
#define PASSPORT_H

#include <QString>
#include <QDate>

class Passport
{
public:
    Passport(const QString&& surnameX, const QString&& nameX, const QString&& secondNameX,
             const QDate&& birthdayX, const int&& itnX);

    bool isValid() const;

    QString surname;
    QString name;
    QString secondName;
    QDate birthday;
    int itn;
};

#endif // PASSPORT_H
