#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include <QMenuBar>

#include "titlebar.h"
#include "textbutton.h"


class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(const QString& title, const QString& desc, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    QBoxLayout* contentLt;
    QLabel* desc;

private:
    TitleBar* titlebar;
    QGridLayout* mainLt;
    TextButton* ok;
    TextButton* cancel;
};

#endif // BASEDIALOG_H
