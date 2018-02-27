#include "chooseredactmode.h"
#include "ui_chooseredactmode.h"

ChooseRedactMode::ChooseRedactMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseRedactMode)
{
    ui->setupUi(this);
    this->setWindowTitle("Redact Mode");
}

ChooseRedactMode::~ChooseRedactMode()
{
    delete ui;
}

void ChooseRedactMode::on_pushButton_clicked() //Редактирование графа
{
    DialogRedactGraph *RedactGraph = new DialogRedactGraph();
    RedactGraph->show();
    close();
}

void ChooseRedactMode::on_pushButton_2_clicked() //Редактитрование БД
{
    MainWindowRedactDataBase *ModeRedactor = new MainWindowRedactDataBase();
    ModeRedactor->show();
    close();
}

void ChooseRedactMode::on_pushButton_3_clicked() //назад
{
    ChooseMode *Mode = new ChooseMode();
    Mode->show();
    close();
}
