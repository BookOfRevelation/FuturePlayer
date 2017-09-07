#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QtWidgets>
#include "oldbutton.h"

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    enum TitleBarStyle
    {
        DIALOG, WINDOW
    };

    TitleBar(const QString& title, TitleBarStyle st = TitleBar::WINDOW);

private:
    QLabel* titleLbl;
    QPixmap icon;
    OldButton* closeButton;
    OldButton* maximizeButton;
    OldButton* minimizeButton;
    QBoxLayout* mainLt;


signals:
    void closePressed();
    void maximizePressed();
    void minimizePressed();

};

#endif // TITLEBAR_H
