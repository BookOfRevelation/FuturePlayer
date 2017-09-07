#ifndef DURATIONPROGRESS_H
#define DURATIONPROGRESS_H

#include <QProgressBar>
#include <QMouseEvent>

class DurationProgress : public QProgressBar
{
    Q_OBJECT

public:
    DurationProgress(QWidget* parent = nullptr);

signals:
    void trackTo(int percent);

protected:
    virtual void mousePressEvent(QMouseEvent* e);
};

#endif // DURATIONPROGRESS_H
