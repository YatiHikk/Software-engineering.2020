#ifndef CREATURECLASS_H
#define CREATURECLASS_H

#include <QString>
#include <QList>
#include <QDebug>

class Creatureclass
{
public:
    Creatureclass();
    Creatureclass(QString nameC, int ctgC, QString upctgC, QStringList subctgC, QString descripC, QString pictureC, QStringList enemiesC, QStringList hintsC);
    Creatureclass(const Creatureclass &v);

    ~Creatureclass ();

    QString getName();
    int getCtg();
    QString getUpCtg();
    QStringList getSubCtg();
    QString getDescrip();
    QStringList getEnemies();
    QStringList getHints();
    QString getPic();

private:
    QString name = "";
    int ctg = 0;
    QString upctg = "";
    QString description = "";
    QString picture = "";

    QStringList subctg;
    QStringList enemies;
    QStringList hints;
};

#endif // CREATURECLASS_H
