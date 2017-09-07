#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QMenuBar>

#include "titlebar.h"
#include "textbutton.h"

class WarningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WarningDialog(const QString& title, const QString& descr, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void okPressed();
    void cancelPressed();

public slots:
    void onOkPressed();
    void onCancelPressed();

private:
    TitleBar* titlebar;
    QGridLayout* mainLt;
    QLabel* desc;
    TextButton* ok;
    TextButton* cancel;
};

#endif // WARNINGDIALOG_H
