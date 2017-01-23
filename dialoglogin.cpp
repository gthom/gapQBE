#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <QSqlError>

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogLogin)
{
    m_ui->setupUi(this);

    m_ui->comboBox->insertItems(0,QSqlDatabase::database().drivers());
    QFile ficParam(".gapQbe");

    if(ficParam.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString nomUtil=ficParam.readLine(254);
        nomUtil=nomUtil.mid(0,nomUtil.length()-1);
        QString mdpUtil=ficParam.readLine(254);
       mdpUtil=mdpUtil.mid(0,mdpUtil.length()-1);
        QString baseUtil=ficParam.readLine(254);
        baseUtil=baseUtil.mid(0,baseUtil.length()-1);
        QString driverUtil=ficParam.readLine(254);
        driverUtil=driverUtil.mid(0,driverUtil.length()-1);
        m_ui->lineEditLogin->setText(nomUtil);
        m_ui->lineEditLoginPassword->setText(mdpUtil);
        m_ui->lineEditLoginDatabaseName->setText(baseUtil);
        m_ui->comboBox->setCurrentIndex(m_ui->comboBox->findText(driverUtil));
        ficParam.close();
    }
}

DialogLogin::~DialogLogin()
{
    delete m_ui;
}

void DialogLogin::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogLogin::on_pushButtonOk_clicked()
{

    QSqlDatabase::database()=QSqlDatabase::addDatabase(m_ui->comboBox->currentText());


    //db->cloneDatabase(dbEssai,"pof");
    QSqlDatabase::database().setHostName(m_ui->lineEditLoginHost->text());
    QSqlDatabase::database().setUserName(m_ui->lineEditLogin->text());
    QSqlDatabase::database().setDatabaseName(m_ui->lineEditLoginDatabaseName->text());
    QSqlDatabase::database().setPassword(m_ui->lineEditLoginPassword->text());
    if(QSqlDatabase::database().open())
    {
        //la connexion a réussi
        //on sauve les renseignements donnés

        std::ofstream fparam;
        fparam.open(".gapQbe");


        qDebug()<<"je suis là";
        fparam<<m_ui->lineEditLogin->text().toStdString().c_str()<<std::endl;
        fparam<<m_ui->lineEditLoginPassword->text().toStdString().c_str()<<std::endl;
        fparam<<m_ui->lineEditLoginDatabaseName->text().toStdString().c_str()<<std::endl;
        fparam<<m_ui->comboBox->currentText().toStdString().c_str()<<std::endl;
        fparam.close();

        accept();
    }
    else
    {
        QMessageBox::warning(this,this->windowTitle(),tr("Database connection rejected")+db->lastError().databaseText());
    }
}

void DialogLogin::on_pushButtonAnnuler_clicked()
{
    reject();
}
