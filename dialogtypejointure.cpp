#include "dialogtypejointure.h"
#include "ui_dialogtypejointure.h"

DialogTypeJointure::DialogTypeJointure(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogTypeJointure)
{
    m_ui->setupUi(this);
}

DialogTypeJointure::~DialogTypeJointure()
{
    delete m_ui;
}

void DialogTypeJointure::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
