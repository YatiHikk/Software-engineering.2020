#ifndef CREATURE_H
#define CREATURE_H

#include <QDialog>
#include <vector>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QSound>
#include <QMouseEvent>
#include <QVariantMap>
#include <QDir>
#include <QFont>
#include <QFontDatabase>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "creatureclass.h"
#include "creaturelist.h"
#include "jsons_reader.h"


namespace Ui {
class Creature;
}

class Creature : public QDialog
{
    Q_OBJECT

public:
    explicit Creature(QWidget *parent = nullptr);

    ~Creature();

    void showCreature (int page);
    void showContlist ();
    QString makeHyperLink(int, QString);
    QString makeHyperLinkList (QStringList, QString);
    int findCat(QString);
    void uiManager (bool lowestCtg);


private slots:
    void on_rightButton_clicked();

    void on_TitleE_linkActivated(const QString &link);

    void on_leftButton_clicked();

private:
    Ui::Creature *ui;

    QString linker;
    QPoint mpos;
    size_t currentPage, currentUpCat;
    QVector <Creatureclass> list;
};

#endif // CREATURE_H
