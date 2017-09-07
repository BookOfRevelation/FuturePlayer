#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QMenuBar>

#include "titlebar.h"
#include "aboutwindow.h"
#include "centralplayer.h"



class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);

private:
    void createMenus();

    TitleBar* titlebar;
    QGridLayout* mainLt;
    QSizeGrip* grip;
    bool maximized;
    QPoint offset;
    QMenuBar* menuBar;
    AboutWindow* abw;
    CentralPlayer* centralWidget;

private slots:
    void minOrMaximize();

};

#endif // MAINWINDOW_H
