/********************************************************************************
** Form generated from reading ui file 'dialoglogin.ui'
**
** Created: Mon Jan 18 18:08:40 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogLogin
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditLogin;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditLoginPassword;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEditLoginDatabaseName;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEditLoginHost;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonAnnuler;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QString::fromUtf8("DialogLogin"));
        DialogLogin->resize(277, 230);
        verticalLayout = new QVBoxLayout(DialogLogin);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogLogin);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditLogin = new QLineEdit(DialogLogin);
        lineEditLogin->setObjectName(QString::fromUtf8("lineEditLogin"));

        horizontalLayout->addWidget(lineEditLogin);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DialogLogin);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditLoginPassword = new QLineEdit(DialogLogin);
        lineEditLoginPassword->setObjectName(QString::fromUtf8("lineEditLoginPassword"));
        lineEditLoginPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditLoginPassword);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(DialogLogin);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEditLoginDatabaseName = new QLineEdit(DialogLogin);
        lineEditLoginDatabaseName->setObjectName(QString::fromUtf8("lineEditLoginDatabaseName"));

        horizontalLayout_3->addWidget(lineEditLoginDatabaseName);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(DialogLogin);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineEditLoginHost = new QLineEdit(DialogLogin);
        lineEditLoginHost->setObjectName(QString::fromUtf8("lineEditLoginHost"));

        horizontalLayout_4->addWidget(lineEditLoginHost);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(DialogLogin);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        comboBox = new QComboBox(DialogLogin);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButtonOk = new QPushButton(DialogLogin);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));

        horizontalLayout_6->addWidget(pushButtonOk);

        pushButtonAnnuler = new QPushButton(DialogLogin);
        pushButtonAnnuler->setObjectName(QString::fromUtf8("pushButtonAnnuler"));

        horizontalLayout_6->addWidget(pushButtonAnnuler);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(DialogLogin);

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QApplication::translate("DialogLogin", "GapTableConceptor-login", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogLogin", "Login:", 0, QApplication::UnicodeUTF8));
        lineEditLogin->setText(QApplication::translate("DialogLogin", "root", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogLogin", "Password:", 0, QApplication::UnicodeUTF8));
        lineEditLoginPassword->setText(QString());
        label_3->setText(QApplication::translate("DialogLogin", "Database Name:", 0, QApplication::UnicodeUTF8));
        lineEditLoginDatabaseName->setText(QApplication::translate("DialogLogin", "mysql", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DialogLogin", "Host:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogLogin", "Database Engine:", 0, QApplication::UnicodeUTF8));
        pushButtonOk->setText(QApplication::translate("DialogLogin", "&Ok", 0, QApplication::UnicodeUTF8));
        pushButtonAnnuler->setText(QApplication::translate("DialogLogin", "&Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DialogLogin);
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
