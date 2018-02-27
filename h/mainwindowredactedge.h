#ifndef MAINWINDOWREDACTEDGE_H
#define MAINWINDOWREDACTEDGE_H
#include <QMainWindow>
#include <QSqlTableModel>

#include "database.h"
#include "dialogaddedge.h"
#include "dialogredactgraph.h"

namespace Ui {
class MainWindowRedactEdge;
}

class MainWindowRedactEdge : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRedactEdge(QWidget *parent = 0);
    ~MainWindowRedactEdge();

private slots:
    void on_addRecordButton_clicked();
    void slotUpdateModels();
    void slotEditRecord();
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);

    void on_CloseWindow_triggered();
    void on_ReturnAction_triggered();

private:
    Ui::MainWindowRedactEdge  *ui;
    DataBaseMain              *db;
    QSqlTableModel            *modelTable;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};
#endif // MAINWINDOWREDACTEDGE_H
