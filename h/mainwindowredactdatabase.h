#ifndef MAINWINDOWREDACTDATABASE_H
#define MAINWINDOWREDACTDATABASE_H

#include <QMainWindow>
#include <QSqlTableModel>

#include "database.h"
#include <dialogaddship.h>
#include "chooseredactmode.h"

namespace Ui {
class MainWindowRedactDataBase;
}

class MainWindowRedactDataBase : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRedactDataBase(QWidget *parent = 0);
    ~MainWindowRedactDataBase();

private slots:
    void on_addRecordButton_clicked(); //Метод для активации диалога добавления записей
    void slotUpdateModels(); //Слот для обновления данных при изменении
    void slotEditRecord(); //слот редактирования записей
    void slotRemoveRecord(); //слот удаления записей
    void slotCustomMenuRequested(QPoint pos); //слот обработки вызова контестного меню
    void on_CloseWindow_triggered();
    void on_ReturnAction_triggered();

private:
    Ui::MainWindowRedactDataBase        *ui;
    DataBaseMain                        *db;
    QSqlTableModel                      *modelTable;

private:
    void setupModel(const QString &tableName, const QStringList &headers); // Инициализация модели представления данных
    void createUI(); //создание формы
};

#endif // MAINWINDOWREDACTDATABASE_H
