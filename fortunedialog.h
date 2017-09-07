#ifndef FORTUNEDIALOG_H
#define FORTUNEDIALOG_H
#include "basedialog.h"

class FortuneDialog : public BaseDialog
{
public:

    static QVector<QString> fortunes;

    FortuneDialog();
};

#endif // FORTUNEDIALOG_H


