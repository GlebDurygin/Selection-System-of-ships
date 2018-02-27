#include "mainwindowredactedge.h"
#include "ui_mainwindowredactEdge.h"
#include <QTableView>

MainWindowRedactEdge::MainWindowRedactEdge(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedactEdge)
{
    ui->setupUi(this);
    this->setWindowTitle("Data Base of Edges");
    db = new DataBaseMain();
    db->connectToDataBase();

    this->setupModel(RECORD_EDGE,
                     QStringList()   << trUtf8("id")
                                         << trUtf8("Начальный пункт")
                                         << trUtf8("Конечный пункт")
                                         << trUtf8("Расстояние")
               );
    this->createUI();
}

MainWindowRedactEdge::~MainWindowRedactEdge()
{
    delete ui;
}

void MainWindowRedactEdge::setupModel(const QString &tableName, const QStringList &headers)
{
    modelTable = new QSqlTableModel(this);
    modelTable->setTable(tableName);
    modelTable->select();
    for(int i = 0, j = 0; i < modelTable->columnCount(); i++, j++){
        modelTable->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}


void MainWindowRedactEdge::createUI()
{
    ui->RecordTableView->setModel(modelTable);
    ui->RecordTableView->setColumnHidden(0, true);
    ui->RecordTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->RecordTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->RecordTableView->resizeColumnsToContents();
    ui->RecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->RecordTableView->horizontalHeader()->setStretchLastSection(true);

    ui->RecordTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->RecordTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord()));
    connect(ui->RecordTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

void MainWindowRedactEdge::on_addRecordButton_clicked()
{
    DialogAddEdge *addEdgeDialog = new DialogAddEdge();
    connect(addEdgeDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addEdgeDialog->setWindowTitle(trUtf8("Добавить Ребро"));
    addEdgeDialog->exec();
}

void MainWindowRedactEdge::slotCustomMenuRequested(QPoint point)
{
    QMenu * menu = new QMenu(this);
    QAction * editEdge = new QAction(trUtf8("Редактировать запись"), this);
    QAction * deleteEdge = new QAction(trUtf8("Удалить запись"), this);
    connect(editEdge, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
    connect(deleteEdge, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
    menu->addAction(editEdge);
    menu->addAction(deleteEdge);
    menu->popup(ui->RecordTableView->viewport()->mapToGlobal(point));
}

void MainWindowRedactEdge::slotRemoveRecord()
{
    int row = ui->RecordTableView->selectionModel()->currentIndex().row();
    modelTable->removeRow(row);
    modelTable->select();
    ui->RecordTableView->setCurrentIndex(modelTable->index(-1, -1));
}

void MainWindowRedactEdge::slotUpdateModels()
{
    modelTable->select();
    ui->RecordTableView->resizeColumnsToContents();
}

void MainWindowRedactEdge::slotEditRecord()
{
    DialogAddEdge *addRecordEdge = new DialogAddEdge(ui->RecordTableView->selectionModel()->currentIndex().row());
    connect(addRecordEdge, SIGNAL(signalReady()), this, SLOT(slotUpdateModel()));
    addRecordEdge->setWindowTitle(trUtf8("Редактировать Ребро"));
    addRecordEdge->exec();
    slotUpdateModels();
}


void MainWindowRedactEdge::on_CloseWindow_triggered()
{
    close();
}

void MainWindowRedactEdge::on_ReturnAction_triggered()
{
    DialogRedactGraph *RedactGraph = new DialogRedactGraph();
    RedactGraph->show();
    close();
}
