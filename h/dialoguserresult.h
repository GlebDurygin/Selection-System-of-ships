#ifndef DIALOGUSERRESULT_H
#define DIALOGUSERRESULT_H
#include <QDialog>
#include <QTableWidgetItem>

#include "database.h"
#include "dialogmainuser.h"

namespace Ui {
class DialogUserResult;
}

class DialogUserResult : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUserResult(QWidget *parent=0);
    DialogUserResult(QVariantList List, QWidget *parent=0);
    ~DialogUserResult();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DialogUserResult        *ui;
    QVariantList                list;
    DataBaseMain                *db;

private:
    void createUI();
    void showValues();
};
#endif // DIALOGUSERRESULT_H
