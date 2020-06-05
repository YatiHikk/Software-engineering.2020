#include "creature.h"
#include "ui_creature.h"
#include "creatureclass.h"
#include "creaturelist.h"

Creature::Creature(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Creature)
{
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/shrift/18963.ttf");
    QFont baseFont("Pixel Times", 9);
    QFont subbase("Pixel Times", 11);

    this->setFont(baseFont);
    ui->Sublist->setFont(baseFont);
    ui->lSubtitle->setFont(subbase);
    ui->Name->setFont(subbase);

    ui->TitleE->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->TitleE->setTextFormat(Qt::RichText);
    ui->TitleE->setOpenExternalLinks(false);

    this->setWindowFlag(Qt::FramelessWindowHint);

    QPixmap bkgnd(":/Consol/Consol-1.png");
    bkgnd = bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    if(!QDir(QDir::currentPath() + "/Music").exists())
    {
        QDir().mkdir(QDir::currentPath() + "/Music");
    }
    QFile::copy(":/Music/Button.wav", QDir::currentPath() + "/Music/Button.wav");

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
//    qDebug() << "currentPage:" << currentPage;
    showCreature(currentPage);
}

Creature::~Creature()
{
    delete ui;
}

void Creature::showCreature(int page)
{
    currentUpCat = 0;
    currentPage = page;
    QSound::play(QDir::currentPath()+"/Music/Button.wav");
    if(currentPage == 0)
    {
        showContlist();
    }
    else
    {
        currentPage = page;
        QString enemy = makeHyperLinkList(list[currentPage].getEnemies(), "; <br>");
        QString hint = (list[currentPage].getHints().join(", <br>") );
        QString subCtgs = makeHyperLinkList(list[currentPage].getSubCtg(), ";<br>");
        currentUpCat = findCat(list[currentPage].getUpCtg());
        
//        qDebug() << "hints" <<(list[currentPage].getSubCtg());
        ui->List->clear();
        if(subCtgs != "")
        {
            uiManager(false);
        }
        else
        {
            uiManager(true);
        }
        
        ui->Name->setText(list[currentPage].getName());
        ui->TitleD->setText(list[currentPage].getDescrip());
        ui->TitleE->setText(enemy);
        ui->Sublist->setText(subCtgs);
        ui->TitleH->setText(hint);
        
        ui->Page1->setText(QString::number(currentPage+1));

        QPixmap pix(list[currentPage].getPic());
        int w = ui->Pic->width();
        int h = ui->Pic->height();
        ui->Pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
        ui->Pic->setAlignment(Qt::AlignCenter);

    }
}

void Creature::showContlist()
{
    uiManager(false);

    QString contlist = "";

    for (size_t i= 1; i < list.size(); i++)
    {
        QString part = "";
        int sizeCheck = 0, pageNum = i+1;
        QString spacer = "";
//        qDebug() << "category:" << list[i].getCtg();
        if(list[i].getCtg() == 1)
        {
            spacer = "";
            sizeCheck = 82;
        }
        else if(list[i].getCtg() == 2)
        {
            spacer = "&nbsp;&nbsp;&nbsp;&nbsp;";
            sizeCheck = 104;
        }

        part += spacer + makeHyperLink(i, list[i].getName());
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
    ui->List->setText(contlist);
}

QString Creature::makeHyperLink(int page, QString str)
{
    QString link = "";
    link += "<a href=\"" +QString::number(page) + "\" style=\"color: #9C0000;\">" + str + "<\a>";
    return link;
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
    if(currentPage == 0){
//        ui->Sublist->stackUnder(ui->List);
//        ui->TitleE->stackUnder(ui->List);
        ui->TitleE->clear();
        ui->Sublist->clear();
        ui->lSubtitle->clear();
        ui->Enemy->clear();
        ui->Hints->clear();
        ui->Descriptions->clear();
        ui->Page1->clear();
        ui->TitleD->clear();
        ui->TitleH->clear();
        ui->Pic->clear();
        ui->Name->setText("List of Content");
//        qDebug() << ui->Sublist;
    }
    else
    {

    if (!lowestCtg)
    {
        ui->List->stackUnder(ui->Sublist);
        ui->TitleE->stackUnder(ui->Sublist);
        ui->lSubtitle->setText("Kinds of " + list[currentPage].getName());
        ui->Enemy->clear();
        ui->Hints->setText("Hints:");
        ui->Descriptions->setText("Description:");
    }
    if(lowestCtg)
    {
        ui->Sublist->stackUnder(ui->TitleE);
        ui->List->stackUnder(ui->TitleE);
        ui->lSubtitle->clear();
        ui->Enemy->setText("Enemies:");
        ui->Hints->setText("Hints:");
        ui->Descriptions->setText("Description:");
    }
    }

    ui->rightButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    if(currentPage == list.size()-1)
    {
        ui->rightButton->setEnabled(false);
    }
    else if (currentPage == 0)
    {
        ui->leftButton->setEnabled(false);
    }
}

void Creature::on_rightButton_clicked()
{
    currentPage ++;
    showCreature(currentPage);
}

void Creature::on_TitleE_linkActivated(const QString &link)
{
    showCreature(link.toInt());
}

void Creature::on_leftButton_clicked()
{
    currentPage --;
    showCreature(currentPage);
}

void Creature::on_Sublist_linkActivated(const QString &link)
{
    showCreature(link.toInt());
}

void Creature::on_pushButton_clicked()
{
    this->close();
}

void Creature::on_List_linkActivated(const QString &link)
{
    showCreature(link.toInt());
}
