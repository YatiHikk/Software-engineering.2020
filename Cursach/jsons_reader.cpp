#include "jsons_reader.h"

JSONs_reader::JSONs_reader(QString linker)
{
    QFile file(linker);
    if(!file.open(QIODevice::ReadOnly)){
        throw "Failed open.\nYou are probably missing the needed JSON file.\nTry to reinstall the program to fix the problem.";
    }

    QTextStream file_text(&file);
    QString json_string;
    json_string = file_text.readAll();
    file.close();

    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonParseError docError;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes, &docError);
    if (docError.errorString().toInt() != QJsonParseError::NoError)
    {
        throw "Failed to parse.\nYouR JSON file is probably currupted.\nTry to reinstall the program to fix the problem.";
    }

    if(json_doc.isNull()){
        throw "Failed to create JSON doc.\nYour JSON file is probably currupted.\nTry to reinstall the program to fix the problem.";
    }

    if(!json_doc.isObject()){
        throw "JSON is not an object.\nYour JSON file is probably currupted.\nTry to reinstall the program to fix the problem.";
    }

    QJsonObject json_obj = json_doc.object();

    if(json_obj.isEmpty()){
        throw "JSON object is empty.\nYour JSON file is probably currupted.\nTry to reinstall the program to fix the problem.";
    }
    json_map = json_obj.toVariantMap();
}

QVariantMap JSONs_reader::getMap()
{
    return json_map;
}
