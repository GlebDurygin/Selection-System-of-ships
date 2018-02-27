#include "dialogaddvertex.h"
#include "ui_dialogaddvertex.h"

DialogAddVertex::DialogAddVertex(int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddVertex)
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

DialogAddVertex::~DialogAddVertex()
{
    delete ui;
}

void DialogAddVertex::setupModel()
{

    model = new QSqlTableModel(this);
    model->setTable(RECORD_VERTEX);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //все изменения будут применены после submitAll()
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->NameLineEdit_2, 1);
    mapper->addMapping(ui->comboBox, 2);
    mapper->addMapping(ui->CoordinateXLineEdit, 3);
    mapper->addMapping(ui->CoordinateYLineEdit, 4);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit); //для отображения данных в модель.

    connect(ui->previousButton_2, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton_2, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}


void DialogAddVertex::createUI()
{
    QRegExp RegexName("[0-9A-Za-zА-Яа-я\_\-]{1,20}");
    QRegExp RegexCoordinateX("[0-9\.]{1,10}");
    QRegExp RegexCoordinateY("[0-9\.]{1,10}");
    QRegExpValidator *nameValidator = new QRegExpValidator(RegexName, this);
    ui->NameLineEdit_2->setValidator(nameValidator);
    ui->comboBox->addItem("true");
    ui->comboBox->addItem("false");
    QRegExpValidator *coordinateXValidator = new QRegExpValidator(RegexCoordinateX, this);
    ui->CoordinateXLineEdit->setValidator(coordinateXValidator);
    QRegExpValidator *coordinateYValidator = new QRegExpValidator(RegexCoordinateY, this);
    ui->CoordinateYLineEdit->setValidator(coordinateYValidator);
}

void DialogAddVertex::on_buttonBox_2_accepted()
{
    QSqlQuery query;
    QString str =QString ("SELECT " RECORD_NAME " FROM " RECORD_VERTEX
                          " WHERE " RECORD_NAME " = '%1' ").arg(ui->NameLineEdit_2->text());
    query.prepare(str);
    query.exec();
    if(query.first() && flag){
            QMessageBox::information(this, trUtf8("Ошибка ввода"),
                                     trUtf8("Вершина с таким названием уже существует\nПовторите ввод заново"));
    }
    else {
       if (ui->NameLineEdit_2->text()=="" || ui->CoordinateXLineEdit->text()=="" || ui->CoordinateYLineEdit->text() == ""){
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

void DialogAddVertex::on_buttonBox_2_rejected()
{
     this->close();
}


void DialogAddVertex::updateButtons(int row)
{
    ui->previousButton_2->setEnabled(row > 0);
    ui->nextButton_2->setEnabled(row < model->rowCount() - 1);
}
