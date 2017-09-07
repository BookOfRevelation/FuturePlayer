#ifndef OLDBUTTON_H
#define OLDBUTTON_H

#include <QWidget>
#include <QLabel>

class OldButton : public QLabel
{
    Q_OBJECT

public:
    explicit OldButton(const QString& path, const QString& path2, const QString& path3 = "", const QString& path4 = "");

signals:
    void pressed();

protected:
    void mouseReleaseEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);


private:
    QPixmap normal;
    QPixmap pushed;
    QPixmap alternative;
    QPixmap alternativePressed;
    bool state;
    bool hovered;

};

#endif // OLDBUTTON_H
