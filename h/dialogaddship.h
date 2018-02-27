#ifndef DIALOGADDSHIP_H
#define DIALOGADDSHIP_H
#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <database.h>
#include "mainwindowredactdatabase.h"

namespace Ui {
class DialogAddShip;
}

class DialogAddShip : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddShip(int row = -1, QWidget *parent = 0);
    ~DialogAddShip();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void updateButtons(int row);

private:
    Ui::DialogAddShip         *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;
    bool                        flag;

private:
    void setupModel();
    void createUI();
};
#endif // DIALOGADDSHIP_H
