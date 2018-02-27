#include "dialogchoosemode.h"
#include "ui_dialogchoosemode.h"

ChooseMode::ChooseMode(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ChooseMode)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose Mode");

    ui->comboBox->addItem("kazan");
    ui->comboBox->addItem("moscow");
    ui->comboBox->addItem("samara");
    ui->comboBox->addItem("saint-peterburg");
}

ChooseMode::~ChooseMode()
{
    delete ui;
}

void ChooseMode::on_pushButton_clicked()
{
    DialogMainUser* MainUser= new DialogMainUser(ui->comboBox->currentText());
    MainUser->show();
    this->close();
}

void ChooseMode::on_pushButton_2_clicked()
{
    ChooseRedactMode *RedactMode = new ChooseRedactMode();
    RedactMode->show();
    this->close();
}
