#include "dialogaddedge.h"
#include "ui_dialogaddedge.h"

DialogAddEdge::DialogAddEdge(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEdge)
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

DialogAddEdge::~DialogAddEdge()
{
    delete ui;
}

void DialogAddEdge::setupModel()
{

    model = new QSqlTableModel(this);
    model->setTable(RECORD_EDGE);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->comboBox, 1);
    mapper->addMapping(ui->comboBox_2, 2);
    mapper->addMapping(ui->DistanceLineEdit, 3);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}


void DialogAddEdge::createUI()
{
    QRegExp RegexDistance("[0-9]{1,10}");
    QRegExpValidator *distanceValidator = new QRegExpValidator(RegexDistance, this);
    ui->DistanceLineEdit->setValidator(distanceValidator);
    DataBaseMain *db = new DataBaseMain();
    list=db->getRecordsName();
    for (int i=0;i<list.size();i++)
    {
        ui->comboBox->addItem(list.value(i).toString());
        ui->comboBox_2->addItem(list.value(i).toString());
    }
}

void DialogAddEdge::updateButtons(int row)
{
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}

void DialogAddEdge::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString str =QString ("SELECT " RECORD_DESTINATION1 " FROM " RECORD_EDGE
                          " WHERE " RECORD_DESTINATION1 " = '%1' AND " RECORD_DESTINATION2 " = '%2' ").arg(ui->comboBox->currentText(),ui->comboBox_2->currentText());
    query.prepare(str);
    query.exec();
    if(query.first() && flag){
            QMessageBox::information(this, trUtf8("Ошибка ввода"),
                                     trUtf8("Такое ребро уже существует\nПовторите ввод заново"));
    }
    else {
        if (ui->DistanceLineEdit->text()=="" || ui->DistanceLineEdit->text()=="0" || ui->comboBox->currentText() == ui->comboBox_2->currentText()){
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

void DialogAddEdge::on_buttonBox_rejected()
{
     this->close();
}
