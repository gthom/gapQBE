/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Tue Dec 1 10:32:01 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *action_Quitter;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditTableName;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QListWidget *listWidgetChamps;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEditNouveauFieldName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *comboBoxNouveauFieldType;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *lineEditNewTaille;
    QCheckBox *checkBoxNouveauObligatoire;
    QCheckBox *checkBoxNouveauPrimaryKey;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *lineEditNouveauDefaultValue;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLineEdit *lineEditNouveauCheck;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAjouter;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEditEditFieldName;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *comboBoxEditFieldType;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QLineEdit *lineEditEditTaille;
    QCheckBox *checkBoxEditObligatoire;
    QCheckBox *checkBoxEditPrimaryKey;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLineEdit *lineEditEditDefault;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QLineEdit *lineEditEditCheck;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonModifier;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonCreerTable;
    QPushButton *pushButtonQuitter;
    QSpacerItem *horizontalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menu_Fichier;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(567, 423);
        action_Quitter = new QAction(MainWindowClass);
        action_Quitter->setObjectName(QString::fromUtf8("action_Quitter"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setMargin(11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditTableName = new QLineEdit(centralWidget);
        lineEditTableName->setObjectName(QString::fromUtf8("lineEditTableName"));

        horizontalLayout->addWidget(lineEditTableName);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        listWidgetChamps = new QListWidget(centralWidget);
        listWidgetChamps->setObjectName(QString::fromUtf8("listWidgetChamps"));

        verticalLayout_3->addWidget(listWidgetChamps);


        horizontalLayout_14->addLayout(verticalLayout_3);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditNouveauFieldName = new QLineEdit(tab);
        lineEditNouveauFieldName->setObjectName(QString::fromUtf8("lineEditNouveauFieldName"));

        horizontalLayout_2->addWidget(lineEditNouveauFieldName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        comboBoxNouveauFieldType = new QComboBox(tab);
        comboBoxNouveauFieldType->setObjectName(QString::fromUtf8("comboBoxNouveauFieldType"));

        horizontalLayout_3->addWidget(comboBoxNouveauFieldType);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        lineEditNewTaille = new QLineEdit(tab);
        lineEditNewTaille->setObjectName(QString::fromUtf8("lineEditNewTaille"));

        horizontalLayout_4->addWidget(lineEditNewTaille);


        verticalLayout->addLayout(horizontalLayout_4);

        checkBoxNouveauObligatoire = new QCheckBox(tab);
        checkBoxNouveauObligatoire->setObjectName(QString::fromUtf8("checkBoxNouveauObligatoire"));

        verticalLayout->addWidget(checkBoxNouveauObligatoire);

        checkBoxNouveauPrimaryKey = new QCheckBox(tab);
        checkBoxNouveauPrimaryKey->setObjectName(QString::fromUtf8("checkBoxNouveauPrimaryKey"));

        verticalLayout->addWidget(checkBoxNouveauPrimaryKey);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        lineEditNouveauDefaultValue = new QLineEdit(tab);
        lineEditNouveauDefaultValue->setObjectName(QString::fromUtf8("lineEditNouveauDefaultValue"));

        horizontalLayout_7->addWidget(lineEditNouveauDefaultValue);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_8->addWidget(label_9);

        lineEditNouveauCheck = new QLineEdit(tab);
        lineEditNouveauCheck->setObjectName(QString::fromUtf8("lineEditNouveauCheck"));

        horizontalLayout_8->addWidget(lineEditNouveauCheck);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        pushButtonAjouter = new QPushButton(tab);
        pushButtonAjouter->setObjectName(QString::fromUtf8("pushButtonAjouter"));

        horizontalLayout_9->addWidget(pushButtonAjouter);


        verticalLayout->addLayout(horizontalLayout_9);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lineEditEditFieldName = new QLineEdit(tab_2);
        lineEditEditFieldName->setObjectName(QString::fromUtf8("lineEditEditFieldName"));

        horizontalLayout_5->addWidget(lineEditEditFieldName);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        comboBoxEditFieldType = new QComboBox(tab_2);
        comboBoxEditFieldType->setObjectName(QString::fromUtf8("comboBoxEditFieldType"));

        horizontalLayout_6->addWidget(comboBoxEditFieldType);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_12->addWidget(label_12);

        lineEditEditTaille = new QLineEdit(tab_2);
        lineEditEditTaille->setObjectName(QString::fromUtf8("lineEditEditTaille"));

        horizontalLayout_12->addWidget(lineEditEditTaille);


        verticalLayout_2->addLayout(horizontalLayout_12);

        checkBoxEditObligatoire = new QCheckBox(tab_2);
        checkBoxEditObligatoire->setObjectName(QString::fromUtf8("checkBoxEditObligatoire"));

        verticalLayout_2->addWidget(checkBoxEditObligatoire);

        checkBoxEditPrimaryKey = new QCheckBox(tab_2);
        checkBoxEditPrimaryKey->setObjectName(QString::fromUtf8("checkBoxEditPrimaryKey"));

        verticalLayout_2->addWidget(checkBoxEditPrimaryKey);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_10->addWidget(label_10);

        lineEditEditDefault = new QLineEdit(tab_2);
        lineEditEditDefault->setObjectName(QString::fromUtf8("lineEditEditDefault"));

        horizontalLayout_10->addWidget(lineEditEditDefault);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_11->addWidget(label_11);

        lineEditEditCheck = new QLineEdit(tab_2);
        lineEditEditCheck->setObjectName(QString::fromUtf8("lineEditEditCheck"));

        horizontalLayout_11->addWidget(lineEditEditCheck);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_2);

        pushButtonModifier = new QPushButton(tab_2);
        pushButtonModifier->setObjectName(QString::fromUtf8("pushButtonModifier"));

        horizontalLayout_13->addWidget(pushButtonModifier);


        verticalLayout_2->addLayout(horizontalLayout_13);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_14->addWidget(tabWidget);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_3);

        pushButtonCreerTable = new QPushButton(centralWidget);
        pushButtonCreerTable->setObjectName(QString::fromUtf8("pushButtonCreerTable"));

        horizontalLayout_15->addWidget(pushButtonCreerTable);

        pushButtonQuitter = new QPushButton(centralWidget);
        pushButtonQuitter->setObjectName(QString::fromUtf8("pushButtonQuitter"));

        horizontalLayout_15->addWidget(pushButtonQuitter);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_15);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 567, 26));
        menu_Fichier = new QMenu(menuBar);
        menu_Fichier->setObjectName(QString::fromUtf8("menu_Fichier"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu_Fichier->menuAction());
        menu_Fichier->addAction(action_Quitter);

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Quitter->setText(QApplication::translate("MainWindowClass", "&Quitter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "Nom de la table", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowClass", "Liste des champs:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowClass", "Nom du champ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowClass", "Type:", 0, QApplication::UnicodeUTF8));
        comboBoxNouveauFieldType->clear();
        comboBoxNouveauFieldType->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "integer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "float", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "date", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "datetime", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "boolean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "varchar", 0, QApplication::UnicodeUTF8)
        );
        label_7->setText(QApplication::translate("MainWindowClass", "Taille:", 0, QApplication::UnicodeUTF8));
        checkBoxNouveauObligatoire->setText(QApplication::translate("MainWindowClass", "Obligatoire", 0, QApplication::UnicodeUTF8));
        checkBoxNouveauPrimaryKey->setText(QApplication::translate("MainWindowClass", "Fait partie de la clef", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindowClass", "valeur Par d\303\251faut:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindowClass", "Autre contrainte", 0, QApplication::UnicodeUTF8));
        pushButtonAjouter->setText(QApplication::translate("MainWindowClass", "&Ajouter", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowClass", "&Nouveau", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindowClass", "Nom du champ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowClass", "Type:", 0, QApplication::UnicodeUTF8));
        comboBoxEditFieldType->clear();
        comboBoxEditFieldType->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "integer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "float", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "date", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "datetime", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "boolean", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "varchar", 0, QApplication::UnicodeUTF8)
        );
        label_12->setText(QApplication::translate("MainWindowClass", "Taille:", 0, QApplication::UnicodeUTF8));
        checkBoxEditObligatoire->setText(QApplication::translate("MainWindowClass", "Obligatoire", 0, QApplication::UnicodeUTF8));
        checkBoxEditPrimaryKey->setText(QApplication::translate("MainWindowClass", "Fait partie de la clef", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindowClass", "valeurPar d\303\251faut:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindowClass", "Autre contrainte", 0, QApplication::UnicodeUTF8));
        pushButtonModifier->setText(QApplication::translate("MainWindowClass", "&Modifier", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowClass", "&Edition", 0, QApplication::UnicodeUTF8));
        pushButtonCreerTable->setText(QApplication::translate("MainWindowClass", "&Cr\303\251er", 0, QApplication::UnicodeUTF8));
        pushButtonQuitter->setText(QApplication::translate("MainWindowClass", "&Quitter", 0, QApplication::UnicodeUTF8));
        menu_Fichier->setTitle(QApplication::translate("MainWindowClass", "&Fichier", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
