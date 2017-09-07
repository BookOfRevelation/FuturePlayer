#include "textbutton.h"
#include <QMouseEvent>

TextButton::TextButton(const QString & title) : QLabel()
{
    normal = ":/icons/res/buttonBase.png";
    pushed = ":/icons/res/pressedbuttonBase.png";

    QFont f;
    f.setPointSize(13);
    this->setFont(f);
    this->setScaledContents(true);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet(QString("border-image: url("+normal+") 0 0 0 0 stretched stretched"));
    this->setText(title);


    setCursor(QCursor(Qt::PointingHandCursor));

    hovered = false;
}

void TextButton::click()
{
    emit pressed();
}

void TextButton::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    this->setStyleSheet(QString("border-image: url("+normal+") 0 0 0 0 stretched stretched"));

    if(e->button() & Qt::LeftButton)
    {
        QPointF p = e->localPos();
        if(p.x() > width() || p.x() < 0 || p.y() > height() || p.y() < 0)
        {
            hovered = false;
        }
        else
        {
            hovered = true;
        }

        if(hovered)
        {            
            emit pressed();
        }
    }

}

void TextButton::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    if(e->button() & Qt::LeftButton)
    {
        this->setStyleSheet(QString("border-image: url("+pushed+") 0 0 0 0 stretched stretched"));
    }
}
