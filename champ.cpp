#include "ui_mainwindow.h"
#include "champ.h"
#include <QIcon>


champ::champ(QListWidget* l,MainWindow * mum):QListWidgetItem(l)
{
    maman=mum;
    fieldName=maman->ui->lineEditNouveauFieldName->text();
    this->fieldType=maman->ui->comboBoxNouveauFieldType->currentText();
    this->fieldSize=maman->ui->lineEditNewTaille->text();
    this->fieldCheck=maman->ui->lineEditNouveauCheck->text();
    this->fieldPK=maman->ui->checkBoxNouveauPrimaryKey->isChecked();
    this->fieldDefault=maman->ui->lineEditNouveauDefaultValue->text();
    this->fieldObligatoire=maman->ui->checkBoxNouveauObligatoire->isChecked();
    QString sql=fieldName+" "+fieldType;
    if(fieldSize!="") sql+="("+fieldSize+")";

    QString chaineDefault=fieldDefault;
    //on entoure les valeurs non numériques et non boolean par des "'"
    if(fieldType!="integer" && fieldType!="float" && fieldType!="boolean")
        chaineDefault="'"+fieldDefault+"'";
    if(fieldObligatoire) sql+=" not null";
    if (fieldDefault!="") sql+=" default "+chaineDefault;
    if (this->fieldCheck!="") sql+=" check "+ fieldCheck;

    this->setText(sql);

    if(this->fieldPK)
    {
        this->setIcon(QIcon("/home/gthom/gapTableConceptor/cle.xpm"));
    }

}
void champ::display()
{
    //on remplit l'onglet édition
    maman->ui->tabWidget->setCurrentIndex(1);
    maman->ui->lineEditEditFieldName->setText(fieldName);
    maman->ui->lineEditEditTaille->setText(fieldSize);
    maman->ui->checkBoxEditPrimaryKey->setChecked(fieldPK);
    maman->ui->checkBoxEditObligatoire->setChecked(fieldObligatoire);
    maman->ui->lineEditEditCheck->setText(this->fieldCheck);
    maman->ui->lineEditEditDefault->setText(this->fieldDefault);
    maman->ui->comboBoxEditFieldType->setCurrentIndex(maman->ui->comboBoxEditFieldType->findText(this->fieldType));



}
void champ::modification()
{
    fieldName=maman->ui->lineEditEditFieldName->text();
    this->fieldType=maman->ui->comboBoxEditFieldType->currentText();
    this->fieldSize=maman->ui->lineEditEditTaille->text();
    this->fieldCheck=maman->ui->lineEditEditCheck->text();
    this->fieldPK=maman->ui->checkBoxEditPrimaryKey->isChecked();
    this->fieldDefault=maman->ui->lineEditEditDefault->text();
    this->fieldObligatoire=maman->ui->checkBoxEditObligatoire->isChecked();
    QString sql=fieldName+" "+fieldType;
    if(fieldSize!="") sql+="("+fieldSize+")";

    QString chaineDefault=fieldDefault;
    //on entoure les valeurs non numériques et non boolean par des "'"
    if(fieldType!="integer" && fieldType!="float" && fieldType!="boolean")
        chaineDefault="'"+fieldDefault+"'";
    if(fieldObligatoire) sql+=" not null";
    if (fieldDefault!="") sql+=" default "+chaineDefault;
    if (this->fieldCheck!="") sql+=" check "+ fieldCheck;

    this->setText(sql);

    if(this->fieldPK)
    {
        this->setIcon(QIcon("/home/gthom/gapTableConceptor/cle.xpm"));
    }
    else this->setIcon(QIcon());
}
