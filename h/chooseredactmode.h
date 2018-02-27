#ifndef CHOOSEREDACTMODE_H
#define CHOOSEREDACTMODE_H

#include <QWidget>
#include "mainwindowredactdatabase.h"
#include "dialogchoosemode.h"
#include "dialogredactgraph.h"
namespace Ui {
class ChooseRedactMode;
}

class ChooseRedactMode : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseRedactMode (QWidget *parent = 0);
    ~ChooseRedactMode();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ChooseRedactMode              *ui;
};

#endif // CHOOSEREDACTMODE_H



