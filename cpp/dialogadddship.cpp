#include "dialogaddship.h"
#include "ui_dialogaddship.h"

DialogAddShip::DialogAddShip(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddShip)
{
    ui->setupUi(this);
    setupModel();
    if(row == -1){
        flag =true;
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    } else {
        flag =false;
        mapper->setCurrentModelIndex(model->index(row,0));
    }

    createUI();
}

DialogAddShip::~DialogAddShip()
{
    delete ui;
}

void DialogAddShip::setupModel()
{

    model = new QSqlTableModel(this);
    model->setTable(RECORD_SHIP);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->NameLineEdit, 1);
    mapper->addMapping(ui->comboBox, 2);
    mapper->addMapping(ui->PassengerCapacityLineEdit, 3);
    mapper->addMapping(ui->comboBox_2, 4);
    mapper->addMapping(ui->AverageSpeedLineEdit, 5);
    mapper->addMapping(ui->PriceLineEdit, 6);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}


void DialogAddShip::createUI()
{
    QRegExp RegexName("[0-9A-Za-zА-Яа-я,-,_]{1,20}");
    QRegExp RegexPassengerCapacity("[0-9]{1,10}");
    QRegExp RegexAverageSpeed("[0-9]{1,4}");
    QRegExp RegexPrice("[0-9]{1,10}");
    QRegExpValidator *nameValidator = new QRegExpValidator(RegexName, this);
    ui->NameLineEdit->setValidator(nameValidator);
    ui->comboBox->addItem("катер");
    ui->comboBox->addItem("теплоход");
    ui->comboBox->addItem("плавдача");
    QRegExpValidator *passengerCapacityValidator = new QRegExpValidator(RegexPassengerCapacity, this);
    ui->PassengerCapacityLineEdit->setValidator(passengerCapacityValidator);
    ui->comboBox_2->addItem("true");
    ui->comboBox_2->addItem("false");
    QRegExpValidator *averageSpeedValidator = new QRegExpValidator(RegexAverageSpeed, this);
    ui->AverageSpeedLineEdit->setValidator(averageSpeedValidator);
    QRegExpValidator *priceValidator = new QRegExpValidator(RegexPrice, this);
    ui->PriceLineEdit->setValidator(priceValidator);
}

void DialogAddShip::on_buttonBox_accepted()
{
     QSqlQuery query;
     QString str =QString ("SELECT " RECORD_NAME " FROM " RECORD_SHIP
                           " WHERE " RECORD_NAME " = '%1' ").arg(ui->NameLineEdit->text());
     query.prepare(str);
     query.exec();
     query.next();
     if(query.first() && flag){
             QMessageBox::information(this, trUtf8("Ошибка ввода"),
                                      trUtf8("Судно с таким названием уже существует\nПовторите ввод заново"));
     }
     else {
         if (ui->NameLineEdit->text()=="" || ui->PassengerCapacityLineEdit->text()=="" || ui->AverageSpeedLineEdit->text()=="" || ui->PriceLineEdit->text()==""){
              QMessageBox::information(this, trUtf8("Ошибка ввода"),
                                       trUtf8("Некоторые поля не заполнены\nПовторите ввод заново"));
          }
         else{
              mapper->submit();
              model->submitAll();
              emit signalReady();
              this->close();
         }
     }
}

void DialogAddShip::on_buttonBox_rejected()
{
     this->close();
}

void DialogAddShip::updateButtons(int row)
{
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}

