#ifndef CENTRALPLAYER_H
#define CENTRALPLAYER_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QLayout>
#include <QMediaPlayer>
#include <QDial>
#include <QKeyEvent>

#include "playlist.h"
#include "durationprogress.h"
#include "textbutton.h"

class CentralPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit CentralPlayer(QWidget *parent = 0);
    ~CentralPlayer();
    TextButton* playPause;

public slots:
    void playSound(const QString& path, const QString& name);
    void loadMeta(const QString& name);
    void trackTo(int percent);

private:
    QMediaPlayer* player;
    DurationProgress* duration;
    QLabel* title;
    QLabel* image;
    QLabel* desc;
    QLabel* timer;
    TextButton* stop;
    QDial* volume;
    PlayList* plw;
    bool fullstop;


};

#endif // CENTRALPLAYER_H
