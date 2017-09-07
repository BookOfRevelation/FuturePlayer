#include "infodialog.h"
#include <QFileDialog>

InfoDialog::InfoDialog(const QString& n)
    : BaseDialog("Ｔｒａｃｋ  ｍｅｔａ  ｄａｔａ", "")
{
    desc = "";
    QFont f;
    f.setPointSize(13);

    trackName = n;
    img = new QLabel("");

    QLabel* title = new QLabel(n + QString("\n\n\n"));
    title->setAlignment(Qt::AlignCenter);
    title->setFont(f);
    this->contentLt->addWidget(title);


    QBoxLayout* imglt = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* imglbl = new QLabel("Ｃｏｖｅｒ  ：");
    imglbl->setFont(f);

    imglt->addSpacerItem(new QSpacerItem(45,45));
    imglt->addWidget(imglbl);
    imglt->addWidget(img);
    imglt->addSpacerItem(new QSpacerItem(45,45));


    load = new TextButton("ｌｏａｄ");
    load->setFixedSize(90,45);

    imglt->addWidget(load);
    imglt->addSpacerItem(new QSpacerItem(45,120));


    QFile fl(QString("./meta/%1.ftr").arg(n));
    if(fl.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&fl);
        QString line = ts.readLine();
        //first line : cover
        if(!line.isNull() && line.size() > 1)
        {
           img->setPixmap(QPixmap::fromImage(QImage(line).scaled(100,100)));
           coverPath = line;
        }
        else
        {
            img->setPixmap(QPixmap::fromImage(QImage(":/icons/res/noart.jpg").scaled(100,100)));
            coverPath = ":/icons/res/noart.jpg";
        }

        //description
        line = ts.readLine();
        while(!line.isNull())
        {
            desc = desc + line + "\n";
            line = ts.readLine();
        }
        desc.chop(1);
    }
    else
    {
        img->setPixmap(QPixmap::fromImage(QImage(":/icons/res/noart.jpg").scaled(100,100)));
        coverPath = ":/icons/res/noart.jpg";
    }

    this->contentLt->addLayout(imglt);
    this->contentLt->addSpacerItem(new QSpacerItem(45,45));
    descEdit = new QPlainTextEdit(desc);

    QBoxLayout* desclt = new QBoxLayout(QBoxLayout::LeftToRight);
    desclt->addSpacerItem(new QSpacerItem(45,45));
    desclt->addWidget(descEdit);
    desclt->addSpacerItem(new QSpacerItem(45,45));

    this->contentLt->addLayout(desclt);
    this->contentLt->addSpacerItem(new QSpacerItem(45,45));

    connect(load, &TextButton::pressed, this, &InfoDialog::changeCover);

}


void InfoDialog::changeCover()
{
    QString path = "";

    path = QFileDialog::getOpenFileName(
                this,
                "Load cover",
                "./",
                tr("Images (*.png *.xpm *.jpg)")
                );

    if(path != "")
    {
        coverPath = path;
        img->setPixmap(QPixmap::fromImage(QImage(coverPath).scaled(100,100)));
    }
}
