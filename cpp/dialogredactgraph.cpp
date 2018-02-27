#include "dialogredactgraph.h"
#include "ui_dialogredactgraph.h"

DialogRedactGraph::DialogRedactGraph(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::DialogRedactGraph)
{
    ui->setupUi(this);
    this->setWindowTitle("Redact Graph");
}

DialogRedactGraph::~DialogRedactGraph()
{
    delete ui;
}

void DialogRedactGraph::on_pushButton_4_clicked() //Редактирование вершин графа
{
    MainWindowRedactVertex *RedactVertex = new MainWindowRedactVertex();
    RedactVertex->show();
    close();
}

void DialogRedactGraph::on_pushButton_5_clicked() //Редактитрование ребер графа
{
    MainWindowRedactEdge *RedactEdge = new MainWindowRedactEdge();
    RedactEdge->show();
    close();
}

void DialogRedactGraph::on_pushButton_6_clicked() //назад
{
    ChooseRedactMode *RedactMode = new ChooseRedactMode();
    RedactMode->show();
    close();
}
