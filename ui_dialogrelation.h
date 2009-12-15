/********************************************************************************
** Form generated from reading ui file 'dialogrelation.ui'
**
** Created: Tue Dec 15 16:32:44 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGRELATION_H
#define UI_DIALOGRELATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "customgraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_dialogRelation
{
public:
    QAction *actionSuprime;
    QAction *actionActionSuprTable;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetTables;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAdd;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonJoin;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonExecuteRequete;
    QSpacerItem *verticalSpacer_2;
    customGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditQuery;
    QTableWidget *tableWidgetPreview;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *dialogRelation)
    {
        if (dialogRelation->objectName().isEmpty())
            dialogRelation->setObjectName(QString::fromUtf8("dialogRelation"));
        dialogRelation->resize(748, 559);
        actionSuprime = new QAction(dialogRelation);
        actionSuprime->setObjectName(QString::fromUtf8("actionSuprime"));
        actionActionSuprTable = new QAction(dialogRelation);
        actionActionSuprTable->setObjectName(QString::fromUtf8("actionActionSuprTable"));
        verticalLayout_4 = new QVBoxLayout(dialogRelation);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter = new QSplitter(dialogRelation);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidgetTables = new QListWidget(layoutWidget);
        listWidgetTables->setObjectName(QString::fromUtf8("listWidgetTables"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidgetTables->sizePolicy().hasHeightForWidth());
        listWidgetTables->setSizePolicy(sizePolicy);
        listWidgetTables->setAlternatingRowColors(true);
        listWidgetTables->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetTables);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButtonAdd = new QPushButton(layoutWidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonAdd->sizePolicy().hasHeightForWidth());
        pushButtonAdd->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(pushButtonAdd);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonJoin = new QToolButton(layoutWidget1);
        toolButtonJoin->setObjectName(QString::fromUtf8("toolButtonJoin"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tables-relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonJoin->setIcon(icon);

        verticalLayout_2->addWidget(toolButtonJoin);

        toolButtonMove = new QToolButton(layoutWidget1);
        toolButtonMove->setObjectName(QString::fromUtf8("toolButtonMove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/arrow-move.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonMove->setIcon(icon1);

        verticalLayout_2->addWidget(toolButtonMove);

        toolButtonExecuteRequete = new QToolButton(layoutWidget1);
        toolButtonExecuteRequete->setObjectName(QString::fromUtf8("toolButtonExecuteRequete"));

        verticalLayout_2->addWidget(toolButtonExecuteRequete);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        graphicsView = new customGraphicsView(layoutWidget1);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setContextMenuPolicy(Qt::ActionsContextMenu);
        graphicsView->setAcceptDrops(true);
        graphicsView->setDragMode(QGraphicsView::NoDrag);

        horizontalLayout_4->addWidget(graphicsView);

        splitter->addWidget(layoutWidget1);

        verticalLayout_4->addWidget(splitter);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(dialogRelation);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditQuery = new QLineEdit(dialogRelation);
        lineEditQuery->setObjectName(QString::fromUtf8("lineEditQuery"));

        horizontalLayout->addWidget(lineEditQuery);


        verticalLayout_3->addLayout(horizontalLayout);

        tableWidgetPreview = new QTableWidget(dialogRelation);
        tableWidgetPreview->setObjectName(QString::fromUtf8("tableWidgetPreview"));

        verticalLayout_3->addWidget(tableWidgetPreview);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(dialogRelation);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Help|QDialogButtonBox::Ok|QDialogButtonBox::Reset);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(dialogRelation);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogRelation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogRelation, SLOT(reject()));

        QMetaObject::connectSlotsByName(dialogRelation);
    } // setupUi

    void retranslateUi(QDialog *dialogRelation)
    {
        dialogRelation->setWindowTitle(QApplication::translate("dialogRelation", "Gap Query Builder QBE", 0, QApplication::UnicodeUTF8));
        actionSuprime->setText(QApplication::translate("dialogRelation", "suprime", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSuprime->setToolTip(QApplication::translate("dialogRelation", "supprimer le champ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSuprime->setShortcut(QApplication::translate("dialogRelation", "Del", 0, QApplication::UnicodeUTF8));
        actionActionSuprTable->setText(QApplication::translate("dialogRelation", "actionSuprTable", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        listWidgetTables->setStatusTip(QApplication::translate("dialogRelation", "choose tables you need", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        listWidgetTables->setWhatsThis(QApplication::translate("dialogRelation", "Tables you need", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        pushButtonAdd->setText(QApplication::translate("dialogRelation", "&I need it", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonJoin->setToolTip(QApplication::translate("dialogRelation", "tool to join tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonJoin->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonMove->setToolTip(QApplication::translate("dialogRelation", "tool to move tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonMove->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonExecuteRequete->setToolTip(QApplication::translate("dialogRelation", "tool to execute the query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonExecuteRequete->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dialogRelation", "Result:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(dialogRelation);
    } // retranslateUi

};

namespace Ui {
    class dialogRelation: public Ui_dialogRelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELATION_H
