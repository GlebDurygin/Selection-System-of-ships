#include "mainwindowredactvertex.h"
#include "ui_mainwindowredactvertex.h"
#include <QTableView>

MainWindowRedactVertex::MainWindowRedactVertex(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRedactVertex)
{
    ui->setupUi(this);
    this->setWindowTitle("Data Base of Vertexes");
    db = new DataBaseMain();
    db->connectToDataBase();

    this->setupModel(RECORD_VERTEX,
                     QStringList()   << trUtf8("id")
                                         << trUtf8("Название")
                                         << trUtf8("Пристань")
                                         << trUtf8("Координата X")
                                         << trUtf8("Координата Y")
               );
    this->createUI();
}

MainWindowRedactVertex::~MainWindowRedactVertex()
{
    delete ui;
}

void MainWindowRedactVertex::setupModel(const QString &tableName, const QStringList &headers)
{
    modelTable = new QSqlTableModel(this);
    modelTable->setTable(tableName);
    modelTable->select();
    for(int i = 0, j = 0; i < modelTable->columnCount(); i++, j++){
        modelTable->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}


void MainWindowRedactVertex::createUI()
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

void MainWindowRedactVertex::on_addRecordButton_clicked()
{
    DialogAddVertex *addVertexDialog = new DialogAddVertex();
    connect(addVertexDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addVertexDialog->setWindowTitle(trUtf8("Добавить Вершину"));
    addVertexDialog->exec();
}

void MainWindowRedactVertex::slotCustomMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    QAction * editVertex = new QAction(trUtf8("Редактировать запись"), this);
    QAction * deleteVertex = new QAction(trUtf8("Удалить запись"), this);
    connect(editVertex, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
    connect(deleteVertex, SIGNAL(triggered()), this, SLOT(slotRemoveRecord()));
    menu->addAction(editVertex);
    menu->addAction(deleteVertex);
    menu->popup(ui->RecordTableView->viewport()->mapToGlobal(pos));
}

void MainWindowRedactVertex::slotRemoveRecord()
{
    int row = ui->RecordTableView->selectionModel()->currentIndex().row();
    QString str = ui->RecordTableView->model()->data(ui->RecordTableView->model()->index(row,1)).toString();
    db->deleteEdgesConnectsWithVertex(str);
    modelTable->removeRow(row);
    modelTable->select();
    ui->RecordTableView->setCurrentIndex(modelTable->index(-1, -1));
}

void MainWindowRedactVertex::slotUpdateModels()
{
    modelTable->select();
    ui->RecordTableView->resizeColumnsToContents();
}

void MainWindowRedactVertex::slotEditRecord()
{
    DialogAddVertex *addRecordVertex = new DialogAddVertex(ui->RecordTableView->selectionModel()->currentIndex().row());
    connect(addRecordVertex, SIGNAL(signalReady()), this, SLOT(slotUpdateModel()));
    addRecordVertex->setWindowTitle(trUtf8("Редактировать Вершину"));
    addRecordVertex->exec();
    slotUpdateModels();
}


void MainWindowRedactVertex::on_CloseWindow_triggered()
{
    close();
}

void MainWindowRedactVertex::on_ReturnAction_triggered()
{
    DialogRedactGraph *RedactGraph = new DialogRedactGraph();
    RedactGraph->show();
    close();
}

