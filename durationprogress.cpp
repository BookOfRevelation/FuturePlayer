#include "durationprogress.h"

DurationProgress::DurationProgress(QWidget* parent)
    : QProgressBar(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    this->setTextVisible(false);
}


void DurationProgress::mousePressEvent(QMouseEvent *e)
{
    float pos = e->pos().x();
    float max = this->width();

    int percent = (pos/max)*100.0;

    emit trackTo(percent);


}
