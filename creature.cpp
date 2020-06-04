#include "creature.h"
#include "ui_creature.h"
#include "creatureclass.h"
#include "creaturelist.h"

Creature::Creature(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Creature)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/shrift/19246.ttf");
    QFont baseFont("MKARCADECAPS", 8);

    this->setFont(baseFont);

    this->setWindowFlag(Qt::FramelessWindowHint);

    QPixmap bkgnd(":/Consol/Consol-1.png");
    bkgnd = bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    if(!QDir(QDir::currentPath() + "/Sounds").exists())
    {
        QDir().mkdir(QDir::currentPath() + "/Sounds");
    }
    QFile::copy(":/Music/joystick-trigger-button-press_gyyt5ied (online-audio-converter.com).wav", QDir::currentPath() + ":/Music/joystick-trigger-button-press_gyyt5ied (online-audio-converter.com).wav");

    currentPage = 0;
    try
    {
        QString linker = ":/JSONs/Bestiaria.json";
        JSONs_reader read(linker);
        creatureList newList(read.getMap());
        list = newList.getList();
    }
    catch (const char* err)
    {
        QMessageBox::critical(this, "Error", err);
        exit(0);
    }

    showCreature(currentPage);
}

Creature::~Creature()
{
    delete ui;
}

void Creature::showCreature(int page)
{

}

void Creature::showContlist()
{
    uiManager(false);

    QString contlist = "";

    for (size_t i= 1; i < list.size(); i++)
    {
        QString part = "";
        int sizeCheck = 0, pageNum = i*2-1;
        QString spacer = "";
        if(list[i].getCtg() == 1)
        {
            spacer = "";
            sizeCheck = 82;
        }
        else if(list[i].getCtg() == 2)
        {
            spacer = "&#160;&#160;&#160;&#160";
            sizeCheck = 104;
        }

        part += spacer +makeHyperLink(i, list[i].getName());
        for(int j = part.size(); j != sizeCheck; j++)
        {
            part += "..";
        }
        contlist += part + QString::number(pageNum);
        if(i != list.size())
        {
            contlist += "<br>";
        }
    }

}

QString Creature::makeHyperLink(int page, QString str)
{
    QString link = "";
    link += "<a href=\"" +QString::number(page) + "\" style=\"color: #9C0000;\">" + str + "<\a>";
}

QString Creature::makeHyperLinkList(QStringList convList, QString separator)
{
    QString newlist = "";
    for(int i = 0; i < convList.size(); i++)
    {
        for (size_t j = 0; j <list.size(); j++){
            if (list[j].getName() == convList.at(i)){
                newlist += makeHyperLink(j, convList.at(i));
                if(i != convList.size()-1)
                {
                    newlist += separator;
                }
                break;
            }
        }
    }
    return newlist;
}

int Creature::findCat(QString name)
{
    int catPage = 0;
    for(size_t j = 0; j < list.size(); j++){
        if(list[j].getName() == name)
        {
            catPage = j;
            break;
        }
    }
    return catPage;
}

void Creature::uiManager(bool lowestCtg)
{
}

void Creature::on_rightButton_clicked()
{

}

void Creature::on_TitleE_linkActivated(const QString &link)
{

}

void Creature::on_leftButton_clicked()
{

}
