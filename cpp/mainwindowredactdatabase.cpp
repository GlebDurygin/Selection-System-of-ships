#include "mainwindowredactdatabase.h"
#include "ui_mainwindowredactdatabase.h"
#include <QTableView>

MainWindowRedactDataBase::MainWindowRedactDataBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedactDataBase)
{
    ui->setupUi(this);
    this->setWindowTitle("Data Base of Ships");
    db = new DataBaseMain();
    db->connectToDataBase();

    this->setupModel(RECORD_SHIP,
                     QStringList()       << trUtf8("id")
                                         << trUtf8("Название")
                                         << trUtf8("Тип судна")
                                         << trUtf8("Пассажировместимость")
                                         << trUtf8("Пристань")
                                         << trUtf8("Средняя скорость (км/ч)")
                                         << trUtf8("Цена в час (руб)")
               );
    this->createUI();
}

MainWindowRedactDataBase::~MainWindowRedactDataBase()
{
    delete ui;
}

void MainWindowRedactDataBase::setupModel(const QString &tableName, const QStringList &headers)
{
    modelTable = new QSqlTableModel(this);
    modelTable->setTable(tableName);
    modelTable->select();
    for(int i = 0, j = 0; i < modelTable->columnCount(); i++, j++){
        modelTable->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}


void MainWindowRedactDataBase::createUI()
{
    ui->RecordTableView->setModel(modelTable);
    ui->RecordTableView->setColumnHidden(0, true); //скрыть первый столбец с id
    ui->RecordTableView->setSelectionBehavior(QAbstractItemView::SelectRows); //выделение целой строки
    ui->RecordTableView->setSelectionMode(QAbstractItemView::SingleSelection); //выделение только одной строки
    ui->RecordTableView->resizeColumnsToContents(); //формирование столбцов по данным
    ui->RecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //без редактирования данных в ячейках
    ui->RecordTableView->horizontalHeader()->setStretchLastSection(true); //растянуть последний столбец до размеров таблицы

    ui->RecordTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->RecordTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord()));
    connect(ui->RecordTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

void MainWindowRedactDataBase::on_addRecordButton_clicked()
{
    DialogAddShip *addShipDialog = new DialogAddShip();
    connect(addShipDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addShipDialog->setWindowTitle(trUtf8("Добавить Судно"));
    addShipDialog->exec();
}

void MainWindowRedactDataBase::slotCustomMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    QAction * editShip = new QAction(trUtf8("Редактировать запись"), this);
    QAction * deleteShip = new QAction(trUtf8("Удалить запись"), this);
    connect(editShip, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
    connect(deleteShip, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
    menu->addAction(editShip);
    menu->addAction(deleteShip);
    menu->popup(ui->RecordTableView->viewport()->mapToGlobal(pos));
}

void MainWindowRedactDataBase::slotRemoveRecord()
{
    int row = ui->RecordTableView->selectionModel()->currentIndex().row();
    modelTable->removeRow(row);
    modelTable->select();
    ui->RecordTableView->setCurrentIndex(modelTable->index(-1, -1));
}

void MainWindowRedactDataBase::slotUpdateModels()
{
    modelTable->select();
    ui->RecordTableView->resizeColumnsToContents();
}

void MainWindowRedactDataBase::slotEditRecord()
{
    DialogAddShip *addRecordShip = new DialogAddShip(ui->RecordTableView->selectionModel()->currentIndex().row());
    connect(addRecordShip, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addRecordShip->setWindowTitle(trUtf8("Редактировать Судно"));
    addRecordShip->exec();
    slotUpdateModels();
}

void MainWindowRedactDataBase::on_CloseWindow_triggered()
{
    close();
}

void MainWindowRedactDataBase::on_ReturnAction_triggered()
{
    ChooseRedactMode *RedactMode = new ChooseRedactMode();
    RedactMode->show();
    close();
}
