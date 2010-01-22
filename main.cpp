#include <QtGui/QApplication>

#include "dialoglogin.h"
#include "dialogrelation.h"
#include <QSqlDatabase>
#include <QTranslator>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load(QString("gapQBE_") + locale);
     a.installTranslator(&translator);

     QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QSqlDatabase  laBase;
    DialogLogin dLogin(0,laBase);



    if(dLogin.exec())
    {
        dialogRelation relation(0,laBase);
        if (relation.exec())
        {
            return(0);
        }
        else
            return 0;

    }
    return a.exec();
}
