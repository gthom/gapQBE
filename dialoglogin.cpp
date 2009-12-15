#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include "mainwindow.h"
#include <QMessageBox>

DialogLogin::DialogLogin(QWidget *parent, QSqlDatabase& pdb) :
    QDialog(parent),
    m_ui(new Ui::DialogLogin)
{
    m_ui->setupUi(this);
    db=&pdb;
    m_ui->comboBox->insertItems(0,db->drivers());
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


    *db=QSqlDatabase::addDatabase(m_ui->comboBox->currentText());
    db->setHostName(m_ui->lineEditLoginHost->text());
    db->setUserName(m_ui->lineEditLogin->text());
    db->setDatabaseName(m_ui->lineEditLoginDatabaseName->text());
    db->setPassword(m_ui->lineEditLoginPassword->text());
    if(db->open())
    {
        //la connexion a réussi
        accept();
    }
    else
    {
        QMessageBox::warning(this,this->windowTitle(),"Erreur lors de la connexion");
    }
}

void DialogLogin::on_pushButtonAnnuler_clicked()
{
    reject();
}
