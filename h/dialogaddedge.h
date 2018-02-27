#ifndef DIALOGADDEDGE_H
#define DIALOGADDEDGE_H
#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include "database.h"


namespace Ui {
class DialogAddEdge;
}

class DialogAddEdge : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEdge(int row=-1, QWidget *parent=0);
    ~DialogAddEdge();

signals:
    void signalReady();

private slots:
    void updateButtons(int row);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::DialogAddEdge           *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper;
    QVariantList                list;
    bool                        flag;

private:
    void setupModel();
    void createUI();
};
#endif // DIALOGADDEDGE_H
