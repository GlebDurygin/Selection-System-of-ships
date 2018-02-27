#ifndef DIALOGADDVERTEX_H
#define DIALOGADDVERTEX_H
#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include "database.h"


namespace Ui {
class DialogAddVertex;
}

class DialogAddVertex : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddVertex(int row = -1, QWidget *parent = 0);
    ~DialogAddVertex();

signals:
    void signalReady();

private slots:
    void on_buttonBox_2_accepted();
    void on_buttonBox_2_rejected();
    void updateButtons(int row);

private:
    Ui::DialogAddVertex         *ui;
    QSqlTableModel              *model;
    QDataWidgetMapper           *mapper; //Для отображения данных в виджет с произвольной формой
    bool                        flag;

private:
    void setupModel();
    void createUI();
};
#endif // DIALOGADDVERTEX_H
