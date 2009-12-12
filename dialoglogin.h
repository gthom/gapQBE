#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QtGui/QDialog>
#include <QSqlDatabase>

namespace Ui {
    class DialogLogin;
}

class DialogLogin : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DialogLogin)
public:
    explicit DialogLogin(QWidget *parent,QSqlDatabase&);
    virtual ~DialogLogin();
    QSqlDatabase* db;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::DialogLogin *m_ui;

private slots:
    void on_pushButtonAnnuler_clicked();
    void on_pushButtonOk_clicked();
};

#endif // DIALOGLOGIN_H
