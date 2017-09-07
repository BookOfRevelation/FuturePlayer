#include "oldbutton.h"
#include <QMouseEvent>

OldButton::OldButton(const QString& path, const QString& path2, const QString& path3, const QString& path4) : QLabel()
{
    setFixedSize(24,24);
    normal.load(path);
    pushed.load(path2);
    if(path3 == "")
    {
        alternative.load(path);
    }
    else
    {
        alternative.load(path3);
    }
    if(path4 == "")
    {
        alternativePressed.load(path2);
    }
    else
    {
        alternativePressed.load(path4);
    }
    this->setScaledContents(true);

    setPixmap(normal);

    setCursor(QCursor(Qt::PointingHandCursor));
    state = false;
    hovered = false;
}


void OldButton::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    if(e->button() & Qt::LeftButton)
    {
        QPointF p = e->localPos();
        if(p.x() > 24 || p.x() < 0 || p.y() > 24 || p.y() < 0)
        {
            hovered = false;
        }
        else
        {
            hovered = true;
        }

        if(!state && hovered)
        {
            setPixmap(alternative);
        }
        else
        {
            setPixmap(normal);
        }

        if(hovered)
        {
            state = !state;
            emit pressed();
        }
    }

}

void OldButton::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    if(e->button() & Qt::LeftButton)
    {
        if(!state)
        {
            setPixmap(pushed);
        }
        else
        {
            setPixmap(alternativePressed);
        }
    }
}
