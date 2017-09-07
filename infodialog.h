#ifndef INFODIALOG_H
#define INFODIALOG_H

#include "basedialog.h"
#include "textbutton.h"
#include <QPlainTextEdit>

class InfoDialog : public BaseDialog
{
    Q_OBJECT

public:

    InfoDialog(const QString& n);

    QString coverPath;
    QString desc;
    QPlainTextEdit* descEdit;

    void changeCover();

private:
    QLabel* img;
    TextButton* load;
    QString trackName;

};

#endif // INFODIALOG_H
