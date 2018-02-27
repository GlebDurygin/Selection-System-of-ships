#ifndef MAINWINDOWREDACTVERTEX_H
#define MAINWINDOWREDACTVERTEX_H
#include <QMainWindow>
#include <QSqlTableModel>

#include "database.h"
#include "dialogaddvertex.h"
#include "dialogredactgraph.h"

namespace Ui {
class MainWindowRedactVertex;
}

class MainWindowRedactVertex : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRedactVertex(QWidget *parent = 0);
    ~MainWindowRedactVertex();

private slots:
    void on_addRecordButton_clicked();
    void slotUpdateModels();
    void slotEditRecord();
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);

    void on_CloseWindow_triggered();
    void on_ReturnAction_triggered();

private:
    Ui::MainWindowRedactVertex  *ui;
    DataBaseMain                *db;
    QSqlTableModel              *modelTable;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};
#endif // MAINWINDOWREDACTVERTEX_H
