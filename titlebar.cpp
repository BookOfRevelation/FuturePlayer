#include "titlebar.h"

TitleBar::TitleBar(const QString& title, TitleBarStyle st)
    : QWidget(nullptr)
{
    setFixedHeight(33);
    QPalette pal = palette();

    QPalette palette;



    pal.setColor(QPalette::Background, Qt::darkBlue);
    setAutoFillBackground(true);
    setPalette(pal);

    QFont font;
    font.setPointSize(20);
    font.setBold(false);
    titleLbl = new QLabel(title);
    titleLbl->setFont(font);
    //white text
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    //set white text
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    titleLbl->setPalette(palette);


    minimizeButton = new OldButton(":/icons/res/minimize.png", ":/icons/res/pressedminimize.png");
    maximizeButton = new OldButton(":/icons/res/maximize.png", ":/icons/res/pressedmaximize", ":/icons/res/resize.png", ":/icons/res/pressedresize.png");
    closeButton = new OldButton(":/icons/res/cross.png", ":/icons/res/pressedcross.png");

    icon.load(":/icons/res/icon.png");
    QLabel* iconlbl = new QLabel();
    iconlbl->setFixedSize(50,39);
    iconlbl->setScaledContents(true);
    iconlbl->setPixmap(icon);


    mainLt = new QBoxLayout(QBoxLayout::LeftToRight);
    mainLt->setSpacing(2);
    mainLt->setMargin(0);
    this->setLayout(mainLt);
    mainLt->addWidget(iconlbl);
    mainLt->addWidget(titleLbl);
    mainLt->addSpacerItem(new QSpacerItem(480,0));
    if(st == TitleBar::WINDOW)
    {
        mainLt->addWidget(minimizeButton);
        mainLt->addWidget(maximizeButton);
    }
    mainLt->addWidget(closeButton);
    mainLt->addSpacerItem(new QSpacerItem(10,10));


    connect(closeButton, OldButton::pressed, this, [this]()
    {
        emit this->closePressed();
    });
    connect(maximizeButton, OldButton::pressed, this, [this]()
    {
        emit this->maximizePressed();
    });
    connect(minimizeButton, OldButton::pressed, this, [this]()
    {
        emit this->minimizePressed();
    });
}
