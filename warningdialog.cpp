#include "warningdialog.h"

WarningDialog::WarningDialog(const QString& title, const QString& descr, QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(320,240);
    QFont f;
    f.setPointSize(13);
    desc = new QLabel(QString("   ") + descr);
    desc->setFont(f);
    titlebar = new TitleBar(title, TitleBar::DIALOG);

    ok = new TextButton("Ｏｋ");
    ok->setFixedSize(90,45);

    cancel = new TextButton("Ｃａｎｃｅｌ");
    cancel->setFixedSize(90,45);

    QBoxLayout* blt = new QBoxLayout(QBoxLayout::LeftToRight);
    blt->addWidget(ok);
    blt->addWidget(cancel);
    blt->setMargin(10);

    mainLt = new QGridLayout();
    mainLt->addWidget(titlebar, 0, 0, 1, 1);
    mainLt->setSpacing(0);
    mainLt->setMargin(0);
    mainLt->setRowStretch(1, 1);

    mainLt->addWidget(desc, 1,0,1,1);
    mainLt->addLayout(blt, 2,0,1,1);

    setLayout(mainLt);

    connect(titlebar, TitleBar::closePressed, this, WarningDialog::onCancelPressed);
    connect(ok, TextButton::pressed, this, WarningDialog::onOkPressed);
    connect(cancel, TextButton::pressed, this, WarningDialog::onCancelPressed);

    this->setModal(true);
}


void WarningDialog::onCancelPressed()
{
    emit cancelPressed();
    this->close();
}

void WarningDialog::onOkPressed()
{
    emit okPressed();
    this->close();
}

void WarningDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundedRect(0,5,width()-2, height()-7,3,3);
    QWidget::paintEvent(event);
}
