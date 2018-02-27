#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QList>
#include "edge.h"

#define DATABASE_HOSTNAME         "DataBase"
#define DATABASE_NAME             "DataBase.db"
#define DATABASE_HOSTNAMEEDGE     "DataBaseOfEdges"
#define DATABASE_HOSTNAMEVERTEX   "DataBaseOfVertexes"

#define RECORD_SHIP                 "RecordTableShip"
#define RECORD_EDGE                 "RecordTableEdge"
#define RECORD_VERTEX               "RecordTableVertex"
#define RECORD_NAME                 "Name"
#define RECORD_TYPEOFSHIP           "TypeOfShip"
#define RECORD_PASSENGERCAPACITY    "PassengerCapacity"
#define RECORD_PIER                 "Pier"
#define RECORD_AVERAGESPEED         "AverageSpeed"
#define RECORD_PRICE                "Price"
#define RECORD_DESTINATION1         "Destination1"
#define RECORD_DESTINATION2         "Destination2"
#define RECORD_DISTANCE             "Distance"
#define RECORD_COORDINATE_X         "CoordinateX"
#define RECORD_COORDINATE_Y         "CoordinateY"

class DataBaseMain : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseMain(QObject *parent = 0);
    ~DataBaseMain();
    void connectToDataBase();
    bool insertIntoRecordTable(const QVariantList &data);
    QVariantList getRecordsName();
    QList<Vertex*> getVertexes();
    QList<Edge*> getEdges();
    bool ExistsOfVertex(QString name);
    void deleteEdgesConnectsWithVertex(QString name);
    QVariantList getShips(QString type,double distance, QString human,QString pier1,QString pier2);
private:
    QSqlDatabase    db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createRecordTable();
    double getTime(double distance,double speed);
    double getPrice(double time,double price);
};
#endif // DATABASE_H
