#ifndef DIALOGREDACTGRAPH_H
#define DIALOGREDACTGRAPH_H

#include <QWidget>
#include "chooseredactmode.h"
#include "mainwindowredactvertex.h"
#include "mainwindowredactedge.h"

namespace Ui {
class DialogRedactGraph;
}

class DialogRedactGraph : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRedactGraph (QDialog *parent = 0);
    ~DialogRedactGraph();

private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DialogRedactGraph              *ui;
};


#endif // DIALOGREDACTGRAPH_H
