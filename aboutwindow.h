#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QMenuBar>

#include "titlebar.h"
#include "textbutton.h"


class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    TitleBar* titlebar;
    QGridLayout* mainLt;
    QLabel* desc;
    TextButton* ok;
};

#endif // ABOUTWINDOW_H
