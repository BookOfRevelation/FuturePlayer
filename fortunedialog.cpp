#include "fortunedialog.h"

QVector<QString> FortuneDialog::fortunes
{
    "Ｂｅｈｉｎｄ  ｅｖｅｒｙ  ｅｘｑｕｉｓｉｔｅ  ｔｈｉｎｇ  ｔｈａｔ  ｅｘｉｓｔｅｄ，  ｔｈｅｒｅ  ｗａｓ  ｓｏｍｅｔｈｉｎｇ  ｔｒａｇｉｃ．\n\tOscar Wilde, The Picture of Dorian Gray ",
    "Ｎｏｔｈｉｎｇ＇ｓ  ｐｅｒｆｅｃｔ，  ｔｈｅ  ｗｏｒｌｄ＇ｓ  ｎｏｔ  ｐｅｒｆｅｃｔ．  Ｂｕｔ  ｉｔ＇ｓ  ｔｈｅｒｅ  ｆｏｒ  ｕｓ，"
    "\n     ｔｒｙｉｎｇ  ｔｈｅ  ｂｅｓｔ  ｉｔ  ｃａｎ； ｔｈａｔ＇ｓ  ｗｈａｔ ｍａｋｅｓ  ｉｔ  ｓｏ  ｄａｍｎ  ｂｅａｕｔｉｆｕｌ．\n\tHiromu Arakawa, Fullmetal Alchemist, Vol. 1 ",
    "Ｉｎ  ｓｏ  ｆａｒ  ａｓ  ｔｈｅ  ｍｉｎｄ  ｓｅｅｓ  ｔｈｉｎｇｓ  ｉｎ  ｔｈｅｉｒ  ｅｔｅｒｎａｌ  ａｓｐｅｃｔ，"
    "\n     ｉｔ  ｐａｒｔｉｃｉｐａｔｅｓ  ｉｎ  ｅｔｅｒｎｉｔｙ.\n\t Baruch Spinoza, Spinoza in der europäischen Geistesgeschichte "


};

FortuneDialog::FortuneDialog():
    BaseDialog("Ｆｕｔｕｒｅ", FortuneDialog::fortunes[(rand()%FortuneDialog::fortunes.size())], nullptr)
{

}
