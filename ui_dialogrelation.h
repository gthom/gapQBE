/********************************************************************************
** Form generated from reading ui file 'dialogrelation.ui'
**
** Created: Mon Feb 1 14:30:22 2010
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
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidgetTables;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBarResultat;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QToolButton *toolButtonJoin;
    QToolButton *toolButtonMove;
    QToolButton *toolButtonApercuAuto;
    QToolButton *toolButtonExecuteRequete;
    QToolButton *toolButtonAddTables;
    QToolButton *toolButtonFitInView;
    QToolButton *toolButtonSO;
    QToolButton *toolButtonDistinct;
    QSpacerItem *verticalSpacer_2;
    customGraphicsView *graphicsView;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditQuery;
    QPushButton *pushButtonQueryState;
    QWidget *layoutWidget3;
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
    QPushButton *pushButtonExportCsv;
    QWidget *layoutWidget4;
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
        actionZoom_in = new QAction(dialogRelation);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        actionZoom_in->setShortcutContext(Qt::ApplicationShortcut);
        actionZoom_out = new QAction(dialogRelation);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        actionZoom_out->setShortcutContext(Qt::ApplicationShortcut);
        verticalLayout_4 = new QVBoxLayout(dialogRelation);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        splitter_2 = new QSplitter(dialogRelation);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidgetTables = new QListWidget(layoutWidget);
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

        progressBarResultat = new QProgressBar(layoutWidget);
        progressBarResultat->setObjectName(QString::fromUtf8("progressBarResultat"));
        progressBarResultat->setValue(0);

        verticalLayout->addWidget(progressBarResultat);

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

        toolButtonApercuAuto = new QToolButton(layoutWidget1);
        toolButtonApercuAuto->setObjectName(QString::fromUtf8("toolButtonApercuAuto"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/previewOn"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonApercuAuto->setIcon(icon2);
        toolButtonApercuAuto->setCheckable(true);
        toolButtonApercuAuto->setChecked(true);

        verticalLayout_2->addWidget(toolButtonApercuAuto);

        toolButtonExecuteRequete = new QToolButton(layoutWidget1);
        toolButtonExecuteRequete->setObjectName(QString::fromUtf8("toolButtonExecuteRequete"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/make"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonExecuteRequete->setIcon(icon3);

        verticalLayout_2->addWidget(toolButtonExecuteRequete);

        toolButtonAddTables = new QToolButton(layoutWidget1);
        toolButtonAddTables->setObjectName(QString::fromUtf8("toolButtonAddTables"));
        toolButtonAddTables->setArrowType(Qt::RightArrow);

        verticalLayout_2->addWidget(toolButtonAddTables);

        toolButtonFitInView = new QToolButton(layoutWidget1);
        toolButtonFitInView->setObjectName(QString::fromUtf8("toolButtonFitInView"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/zoom-fit-best.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonFitInView->setIcon(icon4);

        verticalLayout_2->addWidget(toolButtonFitInView);

        toolButtonSO = new QToolButton(layoutWidget1);
        toolButtonSO->setObjectName(QString::fromUtf8("toolButtonSO"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/stock_sort-criteria.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButtonSO->setIcon(icon5);

        verticalLayout_2->addWidget(toolButtonSO);

        toolButtonDistinct = new QToolButton(layoutWidget1);
        toolButtonDistinct->setObjectName(QString::fromUtf8("toolButtonDistinct"));
        toolButtonDistinct->setCheckable(true);
        toolButtonDistinct->setChecked(true);

        verticalLayout_2->addWidget(toolButtonDistinct);

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
        splitter_2->addWidget(splitter);
        layoutWidget2 = new QWidget(splitter_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditQuery = new QLineEdit(layoutWidget2);
        lineEditQuery->setObjectName(QString::fromUtf8("lineEditQuery"));

        horizontalLayout->addWidget(lineEditQuery);

        pushButtonQueryState = new QPushButton(layoutWidget2);
        pushButtonQueryState->setObjectName(QString::fromUtf8("pushButtonQueryState"));

        horizontalLayout->addWidget(pushButtonQueryState);

        splitter_2->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        tableWidgetPreview = new QTableWidget(layoutWidget3);
        tableWidgetPreview->setObjectName(QString::fromUtf8("tableWidgetPreview"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidgetPreview->sizePolicy().hasHeightForWidth());
        tableWidgetPreview->setSizePolicy(sizePolicy1);
        tableWidgetPreview->setDragDropMode(QAbstractItemView::DragOnly);
        tableWidgetPreview->setAlternatingRowColors(true);

        horizontalLayout_8->addWidget(tableWidgetPreview);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        checkBoxGroupBy = new QCheckBox(layoutWidget3);
        checkBoxGroupBy->setObjectName(QString::fromUtf8("checkBoxGroupBy"));

        verticalLayout_3->addWidget(checkBoxGroupBy);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        lineEditAgregate = new QLineEdit(layoutWidget3);
        lineEditAgregate->setObjectName(QString::fromUtf8("lineEditAgregate"));

        horizontalLayout_6->addWidget(lineEditAgregate);

        pushButtonAddAgregate = new QPushButton(layoutWidget3);
        pushButtonAddAgregate->setObjectName(QString::fromUtf8("pushButtonAddAgregate"));
        pushButtonAddAgregate->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAddAgregate->setIcon(icon6);

        horizontalLayout_6->addWidget(pushButtonAddAgregate);


        verticalLayout_3->addLayout(horizontalLayout_6);

        listWidgetAggregates = new QListWidget(layoutWidget3);
        listWidgetAggregates->setObjectName(QString::fromUtf8("listWidgetAggregates"));
        listWidgetAggregates->setContextMenuPolicy(Qt::CustomContextMenu);
        listWidgetAggregates->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

        verticalLayout_3->addWidget(listWidgetAggregates);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_7->addWidget(label_2);

        lineEditHaving = new QLineEdit(layoutWidget3);
        lineEditHaving->setObjectName(QString::fromUtf8("lineEditHaving"));
        lineEditHaving->setEnabled(false);

        horizontalLayout_7->addWidget(lineEditHaving);


        verticalLayout_3->addLayout(horizontalLayout_7);

        pushButtonExportCsv = new QPushButton(layoutWidget3);
        pushButtonExportCsv->setObjectName(QString::fromUtf8("pushButtonExportCsv"));
        pushButtonExportCsv->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonExportCsv->setIcon(icon7);

        verticalLayout_3->addWidget(pushButtonExportCsv);


        horizontalLayout_8->addLayout(verticalLayout_3);

        splitter_2->addWidget(layoutWidget3);
        layoutWidget4 = new QWidget(splitter_2);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonQuitter = new QPushButton(layoutWidget4);
        pushButtonQuitter->setObjectName(QString::fromUtf8("pushButtonQuitter"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonQuitter->setIcon(icon8);

        horizontalLayout_2->addWidget(pushButtonQuitter);

        splitter_2->addWidget(layoutWidget4);

        verticalLayout_4->addWidget(splitter_2);


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
        actionZoom_in->setText(QApplication::translate("dialogRelation", "zoom in", 0, QApplication::UnicodeUTF8));
        actionZoom_in->setShortcut(QApplication::translate("dialogRelation", "Ctrl++", 0, QApplication::UnicodeUTF8));
        actionZoom_out->setText(QApplication::translate("dialogRelation", "zoom out", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZoom_out->setToolTip(QApplication::translate("dialogRelation", "zoom out", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionZoom_out->setShortcut(QApplication::translate("dialogRelation", "Ctrl+-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listWidgetTables->setToolTip(QApplication::translate("dialogRelation", "Table's list from database", 0, QApplication::UnicodeUTF8));
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
        toolButtonExecuteRequete->setToolTip(QApplication::translate("dialogRelation", "execute  query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonExecuteRequete->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonAddTables->setToolTip(QApplication::translate("dialogRelation", "addselected  tables to work space", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonAddTables->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonFitInView->setToolTip(QApplication::translate("dialogRelation", "best fit in view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonFitInView->setText(QApplication::translate("dialogRelation", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonSO->setToolTip(QApplication::translate("dialogRelation", "define result's sort order ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonSO->setText(QApplication::translate("dialogRelation", "SO", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonDistinct->setToolTip(QApplication::translate("dialogRelation", "remove result's doubles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonDistinct->setText(QApplication::translate("dialogRelation", "D", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        graphicsView->setToolTip(QApplication::translate("dialogRelation", "Workspace: tables you need", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("dialogRelation", "SQL:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditQuery->setToolTip(QApplication::translate("dialogRelation", "the sql query", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonQueryState->setText(QApplication::translate("dialogRelation", "?", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableWidgetPreview->setToolTip(QApplication::translate("dialogRelation", "The query's rows ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        checkBoxGroupBy->setToolTip(QApplication::translate("dialogRelation", "Check this if you want to compute results by that is displayed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkBoxGroupBy->setText(QApplication::translate("dialogRelation", "Group By", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dialogRelation", "Aggregate:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditAgregate->setToolTip(QApplication::translate("dialogRelation", "type here some function like sum or avg or ...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonAddAgregate->setText(QApplication::translate("dialogRelation", "&Add", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dialogRelation", "Postcondition", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEditHaving->setToolTip(QApplication::translate("dialogRelation", "this is a  s\303\251lection on aggregates's result", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButtonExportCsv->setToolTip(QApplication::translate("dialogRelation", "Export query's result as csv file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonExportCsv->setText(QApplication::translate("dialogRelation", "&Export csv", 0, QApplication::UnicodeUTF8));
        pushButtonQuitter->setText(QApplication::translate("dialogRelation", "&Quit", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(dialogRelation);
    } // retranslateUi

};

namespace Ui {
    class dialogRelation: public Ui_dialogRelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELATION_H
