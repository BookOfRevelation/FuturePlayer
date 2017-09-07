#include "aboutwindow.h"
#include <QFont>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(320,240);
    QFont f;
    f.setPointSize(13);
    desc = new QLabel("    Ｆｕｔｕｒｅ Ｐｌａｙｅｒ ｉｓ  ａ  ｍｐ３  ｐｌａｙｅｒ，  ｂａｓｅｄ  ｏｎ  ｔｈｅ  ＂Ｆｕｔｕｒｅ＂  ＧＵＩ  ｆｒａｍｅｗｏｒｋ，  ｐｏｗｅｒｅｄ  ｂｙ  Ｓｙｄｎｅｙ  Ｍｉｘｔａｐｅ ");
    desc->setFont(f);
    titlebar = new TitleBar("Aｂｏｕｔ", TitleBar::DIALOG);

    ok = new TextButton("Ｏｋ");
    ok->setFixedSize(90,45);

    QBoxLayout* blt = new QBoxLayout(QBoxLayout::LeftToRight);
    blt->addWidget(ok);
    blt->setMargin(10);

    mainLt = new QGridLayout();
    mainLt->addWidget(titlebar, 0, 0, 1, 1);
    mainLt->setSpacing(0);
    mainLt->setMargin(0);
    mainLt->setRowStretch(1, 1);

    mainLt->addWidget(desc, 1,0,1,1);
    mainLt->addLayout(blt, 2,0,1,1);

    setLayout(mainLt);

    connect(titlebar, TitleBar::closePressed, this, QWidget::close);
    connect(ok, TextButton::pressed, this, QDialog::close);
}

void AboutWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundedRect(0,5,width()-2, height()-7,3,3);
    QWidget::paintEvent(event);
}
