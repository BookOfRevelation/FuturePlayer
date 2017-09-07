#include "mainwindow.h"
#include "fortunedialog.h"
#include <QDesktopWidget>
#include <QPainter>
#include "pureconfiguration.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    PureConfiguration::loadConf();
    abw = new AboutWindow();
    createMenus();
    setWindowFlags(Qt::FramelessWindowHint);
    resize(640,480);

    grip = new QSizeGrip(this);
    titlebar = new TitleBar("Ｆｕｔｕｒｅ Ｐｌａｙｅｒ");

    mainLt = new QGridLayout();
    mainLt->addWidget(titlebar, 0, 0, 1, 1);
    mainLt->setSpacing(0);
    mainLt->setMargin(0);
    mainLt->setRowStretch(2, 1);

    mainLt->addWidget(menuBar, 1,0,1,1);
    QBoxLayout* centralWrapper = new QBoxLayout(QBoxLayout::TopToBottom);
    centralWrapper->setMargin(10);
    centralWidget = new CentralPlayer(this);
    centralWrapper->addWidget(centralWidget);
    mainLt->addLayout(centralWrapper, 2, 0, 1, 1);

    setLayout(mainLt);

    connect(titlebar, TitleBar::closePressed, this, QWidget::close);
    connect(titlebar, TitleBar::minimizePressed, this, QWidget::showMinimized);
    connect(titlebar, TitleBar::maximizePressed, this, MainWindow::minOrMaximize);

    maximized = false;
    this->setFocusPolicy(Qt::StrongFocus);
    this->resize(PureConfiguration::windowGeometry[0], PureConfiguration::windowGeometry[1]);
    this->move(PureConfiguration::windowGeometry[2], PureConfiguration::windowGeometry[3]);


}

MainWindow::~MainWindow()
{
    PureConfiguration::windowGeometry[0] = this->size().width();
    PureConfiguration::windowGeometry[1] = this->size().height();
    PureConfiguration::windowGeometry[2] = this->pos().x();
    PureConfiguration::windowGeometry[3] = this->pos().y();
    PureConfiguration::saveConf();
}




void MainWindow::mousePressEvent(QMouseEvent *e)
{
    offset = e->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::RightButton)
    {
        this->move(mapToParent(e->pos() - offset));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    grip->move(width()-32, height()-32);
    grip->resize(32,32);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundedRect(0,5,width()-2, height()-7,3,3);

    QWidget::paintEvent(event);
}

void MainWindow::minOrMaximize()
{
    if(maximized)
    {
        setWindowState(Qt::WindowNoState);
        resize(640,480);
        this->adjustSize();
    }
    else
    {
        setWindowState(Qt::WindowMaximized);
    }

    maximized = !maximized;
}

void MainWindow::createMenus()
{
    menuBar = new QMenuBar;

    menuBar->setStyleSheet("background-color : lightgray;; border-bottom: 1px solid black; border-left : 1px solid black ; border-right : 1px solid black");

    QFont f;
    f.setPointSize(13);
    menuBar->setFont(f);

    QMenu* toolm = new QMenu("ｔｏｏｌｓ");
    menuBar->addMenu(toolm);

    QAction* fortuneAction = toolm->addAction(QIcon(QPixmap(":/icons/res/fortune.png")), "ｒｅａｄ  ａ  ｎｉｃｅ  ｑｕｏｔｅ");
    fortuneAction->setFont(f);

    connect(fortuneAction, QAction::triggered, this, [this]()
    {
       FortuneDialog* fortune = new FortuneDialog;
       fortune->exec();
       fortune->deleteLater();

    });


    QMenu* helpm = new QMenu("ｈｅｌｐ");
    menuBar->addMenu(helpm);

    QAction* aboutAction = helpm->addAction(QIcon(QPixmap(":/icons/res/about.png")), "ａｂｏｕｔ  Ｆｕｔｕｒｅ Ｐｌａｙｅｒ．．．");
    aboutAction->setFont(f);

    connect(aboutAction, QAction::triggered, this, [this]()
    {
        abw->exec();
    });



}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if(e->key() == Qt::Key_Space)
    {
        centralWidget->playPause->click();
    }
}
