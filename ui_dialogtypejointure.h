/********************************************************************************
** Form generated from reading ui file 'dialogtypejointure.ui'
**
** Created: Fri Feb 19 07:09:18 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGTYPEJOINTURE_H
#define UI_DIALOGTYPEJOINTURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogTypeJointure
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBoxType;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogTypeJointure)
    {
        if (DialogTypeJointure->objectName().isEmpty())
            DialogTypeJointure->setObjectName(QString::fromUtf8("DialogTypeJointure"));
        DialogTypeJointure->setWindowModality(Qt::ApplicationModal);
        DialogTypeJointure->resize(268, 68);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/gapQBE.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogTypeJointure->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(DialogTypeJointure);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogTypeJointure);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        comboBoxType = new QComboBox(DialogTypeJointure);
        comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));

        horizontalLayout->addWidget(comboBoxType);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(DialogTypeJointure);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogTypeJointure);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogTypeJointure, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogTypeJointure, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogTypeJointure);
    } // setupUi

    void retranslateUi(QDialog *DialogTypeJointure)
    {
        DialogTypeJointure->setWindowTitle(QApplication::translate("DialogTypeJointure", "Type de jointure", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogTypeJointure", "Please choose a type:", 0, QApplication::UnicodeUTF8));
        comboBoxType->clear();
        comboBoxType->insertItems(0, QStringList()
         << QApplication::translate("DialogTypeJointure", "Natural", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogTypeJointure", "Cross", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogTypeJointure", "Inner", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogTypeJointure", "left outer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DialogTypeJointure", "right outer", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(DialogTypeJointure);
    } // retranslateUi

};

namespace Ui {
    class DialogTypeJointure: public Ui_DialogTypeJointure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTYPEJOINTURE_H
