#include "creaturelist.h"

creatureList::creatureList()
{

}

creatureList::creatureList(QVariantMap json_map)
{
    const auto count = json_map.size();
    list.resize(count+1);

    for (int i = 1; i <= count; i++)
    {
        QVariantMap currentMap = json_map[QString::number(i)].toMap();
        QString name = currentMap["Name"].toString();
        int ctg = currentMap["Category"].toInt();
        QString upctgpage = currentMap["Upcategory"].toString();
        QStringList subctgpage = currentMap["Subcategories"].toStringList();
        QString description = currentMap["Description"].toString();
        QString picture = currentMap["Picture"].toString();
        QStringList enemies = currentMap["Enemies"].toStringList();
        QStringList hints = currentMap["Hints"].toStringList();
        Creatureclass creature(name, ctg, upctgpage, subctgpage, description, picture, enemies, hints);
        list[i]=creature;
    }
}

creatureList::creatureList(const creatureList &base)
{
    list = base.list;
}

QVector<Creatureclass> creatureList::getList()
{
    return list;
}
