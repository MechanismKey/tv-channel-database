#ifndef PASSPORT_H
#define PASSPORT_H

#include <QString>
#include <QDate>

class Passport
{
public:
    Passport(const QString&& surnameX, const QString&& nameX, const QString&& secondNameX,
             const QDate&& birthdayX, const QString&& itnX);

    bool isValid() const;

    QString surname;
    QString name;
    QString secondName;
    QDate birthday;
    QString itn;
};

#endif // PASSPORT_H
