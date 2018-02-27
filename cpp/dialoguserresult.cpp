#include "dialoguserresult.h"
#include "ui_dialoguserresult.h"

DialogUserResult::DialogUserResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUserResult)
{
    ui->setupUi(this);
    this->setWindowTitle("Finding results");
    createUI();
}

DialogUserResult::DialogUserResult(QVariantList List, QWidget *parent):
    QDialog(parent),
    list(List),
    ui(new Ui::DialogUserResult)
{
    ui->setupUi(this);
    this->setWindowTitle("Finding results");
    db =new DataBaseMain();
    db->connectToDataBase();
    this->createUI();
}

DialogUserResult::~DialogUserResult()
{
    delete ui;
}

void DialogUserResult::createUI()
{
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()       << trUtf8("Название судна")
                                               << trUtf8("Время в пути")
                                               << trUtf8("Цена (руб.)"));
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);



    this->showValues();
}

void DialogUserResult::showValues()
{
    QVariantList result_price_list = db->getShips(list.value(0).toString(),list.value(1).toDouble(),list.value(2).toString(),list.value(3).toString(),list.value(4).toString());
    ui->tableWidget->setRowCount(result_price_list.size()/3);
    int i=0;
    for (int row =0; row<ui->tableWidget->rowCount();row++)
        for(int column=0; column<ui->tableWidget->columnCount();column++)
        {
            QTableWidgetItem* cell = new QTableWidgetItem();
            if (column==0) cell->setText(result_price_list.value(i).toString());
            else if (column==1){
                div_t value = div (result_price_list.value(i).toInt(),60);
                QString string=QString("%1 ч. %2 мин.").arg(QString::number(value.quot),QString::number(value.rem));
                cell->setData(0,string);
            }
            else cell->setData(0,result_price_list.value(i).toDouble());
            ui->tableWidget->setItem(row,column,cell);
            i++;
        }
    ui->tableWidget->sortItems(2);
    ui->tableWidget->setSortingEnabled(false);

}

void DialogUserResult::on_pushButton_clicked()
{
    int row = ui->tableWidget->selectionModel()->currentIndex().row();
    QString str_name = ui->tableWidget->model()->data(ui->tableWidget->model()->index(row,0)).toString();
    QString str_time = ui->tableWidget->model()->data(ui->tableWidget->model()->index(row,1)).toString();
    QString str_price = ui->tableWidget->model()->data(ui->tableWidget->model()->index(row,2)).toString();
    QMessageBox::information(this, trUtf8("ВАШ ЗАКАЗ:"),
                         trUtf8("Название судна:                    %1"
                              "\nДлительность поездки:        %2"
                              "\nЦена:                                      %3 руб."
                              "\n\n      ПРИЯТНОГО ПУТЕШЕСТВИЯ!!!").arg(str_name,str_time,str_price));
    this->close();
}


void DialogUserResult::on_pushButton_2_clicked()
{
    ui->tableWidget->sortItems(1);
    ui->tableWidget->setSortingEnabled(false);
}

void DialogUserResult::on_pushButton_3_clicked()
{
    ui->tableWidget->sortItems(2);
    ui->tableWidget->setSortingEnabled(false);
}

