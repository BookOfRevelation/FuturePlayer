#include "centralplayer.h"
#include <QMediaMetaData>
#include <QFile>

CentralPlayer::CentralPlayer(QWidget *parent) : QWidget(parent)
{
    QFont f;
    f.setPointSize(13);

    fullstop = true;
    this->setStyleSheet(
                    "QProgressBar {border: 2px solid grey; border-radius: 5px; text-align:center;} "
                    "QProgressBar::chunk {background-color: #33CC33; width: 1px; margin: 0px;}"
                    );

    title = new QLabel("Ｎｏ  ｔｉｔｌｅ");
    desc = new QLabel("");
    image = new QLabel();
    image->setPixmap(QPixmap(":/icons/res/noart.jpg"));
    duration = new DurationProgress();
    duration->setMinimum(0);
    duration->setMaximum(1);
    duration->setValue(0);

    player = new QMediaPlayer;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* playerLt = new QBoxLayout(QBoxLayout::TopToBottom);

    this->setLayout(mainLt);

    QBoxLayout* btnLt = new QBoxLayout(QBoxLayout::LeftToRight);
    playPause = new TextButton("►");
    playPause->setFixedSize(90,45);
    stop = new TextButton("■");
    stop->setFixedSize(90,45);

    volume = new QDial;
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(100);

    connect(volume, &QDial::valueChanged, this, [this](int v)
    {
        player->setVolume(v);
    });

    btnLt->addWidget(playPause);
    btnLt->addWidget(stop);
    btnLt->addWidget(volume);

    playerLt->addWidget(image);
    playerLt->addWidget(desc);

    playerLt->addLayout(btnLt);

    timer = new QLabel("00:00 / 00:00");
    timer->setFont(f);
    QBoxLayout* durlt = new QBoxLayout(QBoxLayout::LeftToRight);
    durlt->addWidget(duration);
    durlt->addWidget(timer);

    playerLt->addLayout(durlt);
    playerLt->addWidget(title);

    image->setAlignment(Qt::AlignCenter);
    title->setAlignment(Qt::AlignCenter);
    desc->setAlignment(Qt::AlignCenter);

    plw = new PlayList;
    mainLt->addWidget(plw);
    mainLt->addLayout(playerLt);

    title->setFont(f);
    desc->setFont(f);

    connect(plw, &PlayList::playFile, this, &CentralPlayer::playSound);
    connect(player, &QMediaPlayer::positionChanged, this, [this](qint64 pos)
    {
        duration->setMaximum(player->duration());
        duration->setValue(pos);
        if(duration->value() >= duration->maximum() && duration->value() > 0)
        {
            plw->nextSong();
        }
        else
        {
            int curmin = (pos/1000)/60;
            int cursec = (pos/1000)%60;

            int ttlmin = (player->duration()/1000)/60;
            int ttlsec = (player->duration()/1000)%60;

            timer->setText(QString("%1:%2 / %3:%4")
                           .arg(curmin, 2, 10, QChar('0'))
                           .arg(cursec, 2, 10, QChar('0'))
                           .arg(ttlmin, 2, 10, QChar('0'))
                           .arg(ttlsec, 2, 10, QChar('0'))
                           );

        }
    });

    connect(stop, &TextButton::pressed, this, [this]()
    {
        if(player->state() == QMediaPlayer::StoppedState)
        {
            plw->stop();
            fullstop = true;
            plw->currentSong();
            player->stop();
        }
        else
        {
            player->stop();
        }

        playPause->setText("►");
        duration->setValue(0);
        duration->setMaximum(1);
    });

    connect(playPause, &TextButton::pressed, this, [this]()
    {
        if(player->state() == QMediaPlayer::PlayingState)
        {
            player->pause();
            playPause->setText("►");
        }
        else
        {
            if(fullstop)
            {
                plw->currentSong();
            }
            else
            {
                player->play();
            }


            playPause->setText("║");
        }


        fullstop = false;
    });

    connect(plw, &PlayList::reloadMeta, this, &CentralPlayer::loadMeta);
    connect(duration, &DurationProgress::trackTo, this, &CentralPlayer::trackTo);


}

void CentralPlayer::playSound(const QString &path, const QString &name)
{

    player->setMedia(QUrl::fromLocalFile(path));
    player->setVolume(volume->value());

    loadMeta(name);


    player->play();
    playPause->setText("║");

    duration->setMinimum(0);


}


void CentralPlayer::loadMeta(const QString &name)
{
    QFile f(QString("./meta/%1.ftr").arg(name));
    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream ts(&f);
        QString img = ts.readLine();
        QImage cover(img);
        if(!cover.isNull())
        {
            cover = cover.scaled(500,500, Qt::KeepAspectRatio);
            image->setPixmap(QPixmap::fromImage(cover));
        }
        else
        {
            image->setPixmap(QPixmap(":/icons/res/noart.jpg"));
        }
        QString line = ts.readLine();
        QString final = "";
        while(!line.isNull())
        {
            final = final + line + QString("\n");
            line = ts.readLine();
        }
        desc->setText(final);
    }
    else
    {
        image->setPixmap(QPixmap(":/icons/res/noart.jpg"));
        desc->setText("");
    }

    title->setText(name);
}

CentralPlayer::~CentralPlayer()
{
    delete player;
}

void CentralPlayer::trackTo(int percent)
{
    if(player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState)
    {
        float ratio = static_cast<float>(percent)/100.0f;
        player->setPosition(ratio * player->duration());
    }
}



