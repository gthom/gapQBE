#include <QtGui/QApplication>

#include "dialoglogin.h"
#include "dialogrelation.h"
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
