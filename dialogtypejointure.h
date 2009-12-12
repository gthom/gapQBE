#ifndef DIALOGTYPEJOINTURE_H
#define DIALOGTYPEJOINTURE_H

#include <QtGui/QDialog>

namespace Ui {
    class DialogTypeJointure;
}

class DialogTypeJointure : public QDialog {
    Q_OBJECT
public:
    DialogTypeJointure(QWidget *parent = 0);
    ~DialogTypeJointure();
    Ui::DialogTypeJointure *m_ui;

protected:
    void changeEvent(QEvent *e);

};

#endif // DIALOGTYPEJOINTURE_H
