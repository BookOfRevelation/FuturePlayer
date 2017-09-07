#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H
#include <QWidget>
#include <QLabel>

class TextButton : public QLabel
{
    Q_OBJECT

public:
    TextButton(const QString& title);
    void click();

signals:
    void pressed();    

protected:
    void mouseReleaseEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);

private:
    QString normal;
    QString pushed;
    bool hovered;

};

#endif // TEXTBUTTON_H
