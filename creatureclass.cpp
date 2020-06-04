#include "creatureclass.h"

Creatureclass::Creatureclass()
{
}
Creatureclass::Creatureclass(QString nameC, int ctgC, QString upctgC, QStringList subctgC, QString descripC, QString pictureC, QStringList enemyC, QStringList hintsC)
{
    name = nameC;
    ctg = ctgC;
    upctg = upctgC;
    subctg = subctgC;
    description = descripC;
    picture = pictureC;
    enemies = enemyC;
    hints = hintsC;
}

Creatureclass::Creatureclass(const Creatureclass &v)
{
    name = v.name;
    ctg = v.ctg;
    upctg = v.upctg;
    subctg = v.subctg;
    description = v.description;
    picture = v.picture;
    enemies = v.enemies;
    hints = v.hints;
}

Creatureclass::~Creatureclass()
{

}

QString Creatureclass::getName()
{
    return name;
}

int Creatureclass::getCtg()
{
    return ctg;
}

QString Creatureclass::getUpCtg()
{
    return upctg;
}

QStringList Creatureclass::getSubCtg()
{
    return subctg;
}

QString Creatureclass::getDescrip()
{
    return description;
}

QStringList Creatureclass::getEnemy()
{
    return enemies;
}

QStringList Creatureclass::getHints()
{
    return hints;
}

QString Creatureclass::getPic()
{
    return picture;
}

