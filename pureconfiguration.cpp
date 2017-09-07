#include "pureconfiguration.h"
#include <QFile>

QSettings* PureConfiguration::settings;
QString PureConfiguration::lastTrackDir;
QString PureConfiguration::lastPlaylistDir;
int PureConfiguration::windowGeometry[4];

PureConfiguration::PureConfiguration()
{

}


void PureConfiguration::loadConf()
{
    QFile f("./conf.ini");
    //open in readwrite to create the
    //file if not exist
    f.open(QIODevice::ReadWrite);
    f.close();

    settings = new QSettings("./conf.ini", QSettings::IniFormat);

    lastTrackDir = "./";
    lastPlaylistDir = "./";

    bool result = settings->childGroups().contains("global", Qt::CaseInsensitive);
    if(result)
    {
        lastTrackDir = settings->value("global/trackDir", "./").toString();
        lastPlaylistDir = settings->value("global/playlistDir", "./").toString();;

        windowGeometry[0] = settings->value("ui/winW", 1024).toInt();
        windowGeometry[1] = settings->value("ui/winH", 768).toInt();
        windowGeometry[2] = settings->value("ui/winX", 0).toInt();
        windowGeometry[3] = settings->value("ui/winY", 0).toInt();

    }
}

void PureConfiguration::saveConf()
{
    settings->setValue("global/trackDir", lastTrackDir);
    settings->setValue("global/playlistDir", lastPlaylistDir);

    settings->setValue("ui/winW", windowGeometry[0]);
    settings->setValue("ui/winH", windowGeometry[1]);
    settings->setValue("ui/winX", windowGeometry[2]);
    settings->setValue("ui/winY", windowGeometry[3]);

    delete settings;

}
