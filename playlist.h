#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include "textbutton.h"

class PlayList : public QWidget
{
    Q_OBJECT

public:
    explicit PlayList(QWidget *parent = 0);
    void nextSong();
    void currentSong();
    void stop();

signals:
    void playFile(const QString& filepath, const QString& name);
    void reloadMeta(const QString& name);

public slots:
    void addTrack();
    void removeTrack();

protected:
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    void keyPressEvent(QKeyEvent* e);

private:
    QListWidget* playlist;
    TextButton* addBtn;
    TextButton* removeBtn;
    TextButton* saveBtn;
    TextButton* loadBtn;
    int currentTrack;
    QVector<QPair<QString, QString>> tracks;

    void updateTracks();
    void insertTrack(const QString& path);

};

#endif // PLAYLIST_H
