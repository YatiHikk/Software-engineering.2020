#ifndef CREATURELIST_H
#define CREATURELIST_H

#include <creatureclass.h>
#include <QDebug>
#include <vector>

class creatureList
{
public:
    creatureList();
    creatureList(QVariantMap json_map);
    creatureList (const creatureList &base);

    QVector <Creatureclass> getList();

private:
    QVector <Creatureclass> list;
};

#endif // CREATURELIST_H
