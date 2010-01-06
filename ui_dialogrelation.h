/********************************************************************************
** Form generated from reading ui file 'dialogrelation.ui'
**
** Created: Tue Jan 5 09:25:36 2010
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
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
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
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetTables;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBarResultat;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonJoin;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonApercuAuto;
    QToolButton *toolButtonExecuteRequete;
    QToolButton *toolButtonAddTables;
    QToolButton *toolButtonFitInView;
    QSpacerItem *verticalSpacer_2;
    customGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditQuery;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *tableWidgetPreview;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBoxGroupBy;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *lineEditAgregate;
    QPushButton *pushButtonAddAgregate;
    QListWidget *listWidgetAggregates;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_2;
    QLineEdit *lineEditHaving;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonQuitter;

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
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidgetTables = new QListWidget(widget);
        listWidgetTables->setObjectName(QString::fromUtf8("listWidgetTables"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidgetTables->sizePolicy().hasHeightForWidth());
        listWidgetTables->setSizePolicy(sizePolicy);
        listWidgetTables->setDragEnabled(true);
        listWidgetTables->setAlternatingRowColors(true);
        listWidgetTables->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listWidgetTables);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        progressBarResultat = new QProgressBar(widget);
        progressBarResultat->setObjectName(QString::fromUtf8("progressBarResultat"));
        progressBarResultat->setValue(0);

        verticalLayout->addWidget(progressBarResultat);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        toolButtonJoin = new QToolButton(widget1);
        toolButtonJoin->setObjectName(QString::fromUtf8("toolButtonJoin"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tables-relation.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonJoin->setIcon(icon);

        verticalLayout_2->addWidget(toolButtonJoin);

        toolButtonMove = new QToolButton(widget1);
        toolButtonMove->setObjectName(QString::fromUtf8("toolButtonMove"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/arrow-move.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonMove->setIcon(icon1);

        verticalLayout_2->addWidget(toolButtonMove);

        toolButtonApercuAuto = new QToolButton(widget1);
        toolButtonApercuAuto->setObjectName(QString::fromUtf8("toolButtonApercuAuto"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/previewOn"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonApercuAuto->setIcon(icon2);
        toolButtonApercuAuto->setCheckable(true);
        toolButtonApercuAuto->setChecked(true);

        verticalLayout_2->addWidget(toolButtonApercuAuto);

        toolButtonExecuteRequete = new QToolButton(widget1);
        toolButtonExecuteRequete->setObjectName(QString::fromUtf8("toolButtonExecuteRequete"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/make"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonExecuteRequete->setIcon(icon3);

        verticalLayout_2->addWidget(toolButtonExecuteRequete);

        toolButtonAddTables = new QToolButton(widget1);
        toolButtonAddTables->setObjectName(QString::fromUtf8("toolButtonAddTables"));
        toolButtonAddTables->setArrowType(Qt::RightArrow);

        verticalLayout_2->addWidget(toolButtonAddTables);

        toolButtonFitInView = new QToolButton(widget1);
        toolButtonFitInView->setObjectName(QString::fromUtf8("toolButtonFitInView"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/zoom-fit-best.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonFitInView->setIcon(icon4);

        verticalLayout_2->addWidget(toolButtonFitInView);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        graphicsView = new customGraphicsView(widget1);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setContextMenuPolicy(Qt::ActionsContextMenu);
        graphicsView->setAcceptDrops(true);
        graphicsView->setDragMode(QGraphicsView::NoDrag);

        horizontalLayout_4->addWidget(graphicsView);

        splitter->addWidget(widget1);

        verticalLayout_4->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(dialogRelation);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditQuery = new QLineEdit(dialogRelation);
        lineEditQuery->setObjectName(QString::fromUtf8("lineEditQuery"));

        horizontalLayout->addWidget(lineEditQuery);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        tableWidgetPreview = new QTableWidget(dialogRelation);
        tableWidgetPreview->setObjectName(QString::fromUtf8("tableWidgetPreview"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidgetPreview->sizePolicy().hasHeightForWidth());
        tableWidgetPreview->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(tableWidgetPreview);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        checkBoxGroupBy = new QCheckBox(dialogRelation);
        checkBoxGroupBy->setObjectName(QString::fromUtf8("checkBoxGroupBy"));

        verticalLayout_3->addWidget(checkBoxGroupBy);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(dialogRelation);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        lineEditAgregate = new QLineEdit(dialogRelation);
        lineEditAgregate->setObjectName(QString::fromUtf8("lineEditAgregate"));

        horizontalLayout_6->addWidget(lineEditAgregate);

        pushButtonAddAgregate = new QPushButton(dialogRelation);
        pushButtonAddAgregate->setObjectName(QString::fromUtf8("pushButtonAddAgregate"));

        horizontalLayout_6->addWidget(pushButtonAddAgregate);


        verticalLayout_3->addLayout(horizontalLayout_6);

        listWidgetAggregates = new QListWidget(dialogRelation);
        listWidgetAggregates->setObjectName(QString::fromUtf8("listWidgetAggregates"));
        listWidgetAggregates->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

        verticalLayout_3->addWidget(listWidgetAggregates);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_2 = new QLabel(dialogRelation);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_7->addWidget(label_2);

        lineEditHaving = new QLineEdit(dialogRelation);
        lineEditHaving->setObjectName(QString::fromUtf8("lineEditHaving"));

        horizontalLayout_7->addWidget(lineEditHaving);


        verticalLayout_3->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonQuitter = new QPushButton(dialogRelation);
        pushButtonQuitter->setObjectName(QString::fromUtf8("pushButtonQuitter"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonQuitter->setIcon(icon5);

        horizontalLayout_2->addWidget(pushButtonQuitter);


        verticalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(dialogRelation);

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
#ifndef QT_NO_TOOLTIP
        toolButtonFitInView->setToolTip(QApplication::translate("dialogRelation", "best fit in view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonFitInView->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dialogRelation", "SQL:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditQuery->setToolTip(QApplication::translate("dialogRelation", "the sql query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tableWidgetPreview->setToolTip(QApplication::translate("dialogRelation", "The query's rows ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBoxGroupBy->setText(QApplication::translate("dialogRelation", "Group By", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dialogRelation", "Aggregate:", 0, QApplication::UnicodeUTF8));
        pushButtonAddAgregate->setText(QApplication::translate("dialogRelation", "&Add", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dialogRelation", "Postcondition", 0, QApplication::UnicodeUTF8));
        pushButtonQuitter->setText(QApplication::translate("dialogRelation", "&Quit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(dialogRelation);
    } // retranslateUi

};

namespace Ui {
    class dialogRelation: public Ui_dialogRelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELATION_H
