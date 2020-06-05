#ifndef JSONS_READER_H
#define JSONS_READER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>


class JSONs_reader
{
public:
    JSONs_reader(QString linker);

    QVariantMap getMap();

private:
    QVariantMap json_map;
};

#endif // JSONS_READER_H
