#ifndef DIALOGCHOOSEMODE_H
#define DIALOGCHOOSEMODE_H

#include <QDialog>
#include "chooseredactmode.h"
#include "dialogmainuser.h"

namespace Ui {
class ChooseMode;
}

class ChooseMode : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseMode (QDialog *parent = 0);
    ~ChooseMode();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::ChooseMode              *ui;
};

#endif // DIALOGCHOOSEMODE_H
