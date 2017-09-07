#include "basedialog.h"

BaseDialog::BaseDialog(const QString& title, const QString& descr, QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    resize(320,240);
    QFont f;
    f.setPointSize(13);
    desc = new QLabel(QString("    ") + descr);
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

    contentLt = new QBoxLayout(QBoxLayout::TopToBottom);
    contentLt->addWidget(desc);

    mainLt->addLayout(contentLt, 1,0,1,1);
    mainLt->addLayout(blt, 2,0,1,1);

    setLayout(mainLt);

    connect(titlebar, TitleBar::closePressed, this, &QDialog::reject);
    connect(ok, TextButton::pressed, this, QDialog::accept);
    connect(cancel, &TextButton::pressed, this, &BaseDialog::reject);

    this->setModal(true);
}

void BaseDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundedRect(0,5,width()-2, height()-7,3,3);
    QWidget::paintEvent(event);
}
