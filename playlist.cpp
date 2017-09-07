#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include "playlist.h"
#include "infodialog.h"
#include "pureconfiguration.h"

PlayList::PlayList(QWidget *parent) : QWidget(parent)
{
    tracks.clear();
    currentTrack = -1;

    QBoxLayout* mainLt = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setLayout(mainLt);

    QFont f;
    f.setPointSize(13);
    QLabel* ttl = new QLabel("Playlist : ");
    ttl->setAlignment(Qt::AlignCenter);
    ttl->setFont(f);

    mainLt->addWidget(ttl);

    QBoxLayout* toptbnlt = new QBoxLayout(QBoxLayout::LeftToRight);
    addBtn = new TextButton("Ａｄｄ．．．");
    addBtn->setFixedSize(75,45);

    removeBtn = new TextButton("Ｒｅｍｏｖｅ");
    removeBtn->setFixedSize(75,45);

    toptbnlt->addWidget(addBtn);
    toptbnlt->addWidget(removeBtn);
    mainLt->addLayout(toptbnlt);

    playlist = new QListWidget();
    mainLt->addWidget(playlist);

    QBoxLayout* botbtnlt = new QBoxLayout(QBoxLayout::LeftToRight);
    saveBtn = new TextButton("Ｓａｖｅ");
    saveBtn->setFixedSize(65,45);
    loadBtn = new TextButton("Ｌｏａｄ");
    loadBtn->setFixedSize(65,45);

    botbtnlt->addWidget(saveBtn);
    botbtnlt->addWidget(loadBtn);

    mainLt->addLayout(botbtnlt);

    playlist->setStyleSheet("font-size : 20px;");


    connect(addBtn, &TextButton::pressed, this, &PlayList::addTrack);
    connect(removeBtn, &TextButton::pressed, this, &PlayList::removeTrack);
    connect(playlist, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item)
    {
        Q_UNUSED(item);
        currentTrack = playlist->currentRow();
        emit playFile(tracks[currentTrack].first, tracks[currentTrack].second);
    });
    playlist->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(playlist, &QListWidget::customContextMenuRequested, this, [this](const QPoint& point)
    {
        Q_UNUSED(point);
        int item = playlist->currentRow();
        if(item < tracks.size() && item >= 0)
        {
            InfoDialog* id = new InfoDialog(tracks[item].second);
            if(id->exec() == QDialog::Accepted)
            {
                QFile f(QString("./meta/%1.ftr").arg(tracks[item].second));
                if(f.open(QIODevice::WriteOnly))
                {
                    QTextStream ts(&f);
                    ts << id->coverPath << "\n";
                    ts << id->descEdit->toPlainText();

                }
                if(currentTrack == item)
                {
                    emit reloadMeta(tracks[item].second);
                }
            }

            delete id;
        }

    });

    connect(loadBtn, &TextButton::pressed, this, [this]()
    {
       QString path = "";
       path = QFileDialog::getOpenFileName(
                   this,
                   "Open playlist",
                   PureConfiguration::lastPlaylistDir,
                   "Future playlist (*.fpl)"
                   );
       if(path != "")
       {
           tracks.clear();
           QFile f(path);
           QFileInfo fi(f);
           PureConfiguration::lastPlaylistDir = fi.absoluteDir().absolutePath();
           if(f.open(QIODevice::ReadOnly))
           {
               QTextStream ts(&f);
               QString line = ts.readLine();

               while(!line.isNull())
               {
                    insertTrack(line);
                    line = ts.readLine();
               }
                currentTrack = 0;
                updateTracks();
                reloadMeta(tracks[currentTrack].second);

           }
       }

    });

    connect(saveBtn, &TextButton::pressed, this, [this]()
    {
       QString path = "";
       path = QFileDialog::getSaveFileName(
                   this,
                   "Save playlist",
                   PureConfiguration::lastPlaylistDir,
                   "Future playlist (*.fpl)"
                   );

       if(path !="")
       {

           QFile f(path);
           QFileInfo fi(f);
           PureConfiguration::lastPlaylistDir = fi.absoluteDir().absolutePath();
           if(f.open(QIODevice::WriteOnly))
           {
               QTextStream ts(&f);
               for(int i = 0 ; i < tracks.size() ; ++i)
               {
                    ts<<tracks[i].first<<"\n";
               }
           }
       }

    });


    setAcceptDrops(true);

}
void PlayList::stop()
{
    if(tracks.size() > 0)
    {
        currentTrack = 0;
        playlist->setCurrentRow(0);
    }
    else
    {
        currentTrack = -1;
    }
}

void PlayList::nextSong()
{
    if(currentTrack >= 0)
    {
        currentTrack = (currentTrack+1) % tracks.size();
        emit playFile(tracks[currentTrack].first, tracks[currentTrack].second);
    }

    playlist->setCurrentRow(currentTrack);

}

void PlayList::currentSong()
{
    if(currentTrack >= 0)
    {
        emit playFile(tracks[currentTrack].first, tracks[currentTrack].second);
    }
    else if(tracks.size() > 0)
    {
        currentTrack = 0;
        emit playFile(tracks[currentTrack].first, tracks[currentTrack].second);
    }

    playlist->setCurrentRow(currentTrack);

}

void PlayList::addTrack()
{
    QStringList paths;
    paths.clear();
    paths = QFileDialog::getOpenFileNames(
                this,
                QString("Ｏｐｅｎ  Ｍｕｓｉｃ"),
                PureConfiguration::lastTrackDir,
                tr("Ｄｏｐｅ (*.mp3)")

                );

    if(paths.size() > 0)
    {
        for(int i = 0 ; i < paths.size() ; ++i)
        {
            QString path = paths[i];
            insertTrack(path);
        }

    }

}

void PlayList::insertTrack(const QString &path)
{
    QFile f(path);
    QFileInfo fi(f);
    QString name = fi.baseName();

    tracks.push_back(QPair<QString, QString>(path, name));

    PureConfiguration::lastTrackDir = fi.absoluteDir().absolutePath();

    updateTracks();

}

void PlayList::removeTrack()
{
    int selected = playlist->currentRow();
    if(selected >= 0)
    {
        tracks.remove(selected);
        if(tracks.size() == 0)
        {
            currentTrack = -1;
        }
        else if(selected <= currentTrack)
        {
            currentTrack++;
        }
    }

    updateTracks();
}

void PlayList::updateTracks()
{
    playlist->clear();

    for(int i = 0 ; i < tracks.size() ; ++i)
    {
        playlist->addItem(tracks[i].second);
    }


    playlist->setCurrentRow(currentTrack);

}
void PlayList::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void PlayList::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        insertTrack(fileName);
        QFileInfo fi(fileName);
        PureConfiguration::lastTrackDir = fi.absoluteDir().absolutePath();
    }
}

void PlayList::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Delete)
    {
        removeTrack();
    }
}
