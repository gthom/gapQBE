/********************************************************************************
** Form generated from reading ui file 'dialogrelation.ui'
**
** Created: Mon Dec 21 15:22:41 2009
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
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetTables;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonJoin;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonApercuAuto;
    QToolButton *toolButtonExecuteRequete;
    QToolButton *toolButtonAddTables;
    QSpacerItem *verticalSpacer_2;
    customGraphicsView *graphicsView;
    QWidget *layoutWidget1;
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
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
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

        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonJoin = new QToolButton(layoutWidget);
        toolButtonJoin->setObjectName(QString::fromUtf8("toolButtonJoin"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tables-relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonJoin->setIcon(icon);

        verticalLayout_2->addWidget(toolButtonJoin);

        toolButtonMove = new QToolButton(layoutWidget);
        toolButtonMove->setObjectName(QString::fromUtf8("toolButtonMove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/arrow-move.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonMove->setIcon(icon1);

        verticalLayout_2->addWidget(toolButtonMove);

        toolButtonApercuAuto = new QToolButton(layoutWidget);
        toolButtonApercuAuto->setObjectName(QString::fromUtf8("toolButtonApercuAuto"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/previewOn"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonApercuAuto->setIcon(icon2);
        toolButtonApercuAuto->setCheckable(true);
        toolButtonApercuAuto->setChecked(true);

        verticalLayout_2->addWidget(toolButtonApercuAuto);

        toolButtonExecuteRequete = new QToolButton(layoutWidget);
        toolButtonExecuteRequete->setObjectName(QString::fromUtf8("toolButtonExecuteRequete"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/make"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonExecuteRequete->setIcon(icon3);

        verticalLayout_2->addWidget(toolButtonExecuteRequete);

        toolButtonAddTables = new QToolButton(layoutWidget);
        toolButtonAddTables->setObjectName(QString::fromUtf8("toolButtonAddTables"));
        toolButtonAddTables->setArrowType(Qt::RightArrow);

        verticalLayout_2->addWidget(toolButtonAddTables);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        graphicsView = new customGraphicsView(layoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setContextMenuPolicy(Qt::ActionsContextMenu);
        graphicsView->setAcceptDrops(true);
        graphicsView->setDragMode(QGraphicsView::NoDrag);

        horizontalLayout_4->addWidget(graphicsView);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditQuery = new QLineEdit(layoutWidget1);
        lineEditQuery->setObjectName(QString::fromUtf8("lineEditQuery"));

        horizontalLayout->addWidget(lineEditQuery);


        verticalLayout_3->addLayout(horizontalLayout);

        tableWidgetPreview = new QTableWidget(layoutWidget1);
        tableWidgetPreview->setObjectName(QString::fromUtf8("tableWidgetPreview"));

        verticalLayout_3->addWidget(tableWidgetPreview);

        splitter->addWidget(layoutWidget1);

        verticalLayout_4->addWidget(splitter);

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
#ifndef QT_NO_TOOLTIP
        listWidgetTables->setToolTip(QApplication::translate("dialogRelation", "Table's list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        listWidgetTables->setStatusTip(QApplication::translate("dialogRelation", "choose tables you need", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        listWidgetTables->setWhatsThis(QApplication::translate("dialogRelation", "Tables you need", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        toolButtonJoin->setToolTip(QApplication::translate("dialogRelation", "oin tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonJoin->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonMove->setToolTip(QApplication::translate("dialogRelation", "move tables", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonMove->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonApercuAuto->setToolTip(QApplication::translate("dialogRelation", "automatic update of result", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonApercuAuto->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonExecuteRequete->setToolTip(QApplication::translate("dialogRelation", "execute the query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonExecuteRequete->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonAddTables->setToolTip(QApplication::translate("dialogRelation", "add tables to query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonAddTables->setText(QString());
        label->setText(QApplication::translate("dialogRelation", "Result:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditQuery->setToolTip(QApplication::translate("dialogRelation", "the sql query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tableWidgetPreview->setToolTip(QApplication::translate("dialogRelation", "The query's rows ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Q_UNUSED(dialogRelation);
    } // retranslateUi

};

namespace Ui {
    class dialogRelation: public Ui_dialogRelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELATION_H
