#include "database.h"

DataBaseMain::DataBaseMain(QObject *parent) : QObject(parent)
{
}

DataBaseMain::~DataBaseMain()
{}


void DataBaseMain::connectToDataBase()
{

    if(!QFile("C:/Users/Tatyana/Desktop/все/3 курс/Курсовая работа/" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBaseMain::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createRecordTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DataBaseMain::openDataBase()
{
    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
                db = QSqlDatabase::database();
    } else{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:/Users/Tatyana/Desktop/все/3 курс/Курсовая работа/" DATABASE_NAME);
    }
    if(db.open()){
        return true;
    } else {
        return false;
    }
    this->closeDataBase();
}


void DataBaseMain::closeDataBase()
{
    db.close();
}

bool DataBaseMain::createRecordTable()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE " RECORD_VERTEX " ("
                                                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                               RECORD_NAME              " VARCHAR(255)    NOT NULL,"
                                                               RECORD_PIER              " VARCHAR(18)     NOT NULL,"
                                                               RECORD_COORDINATE_X      " DOUBLE,"
                                                               RECORD_COORDINATE_Y      " DOUBLE"
                  " ) ")) {
        qDebug() << "DataBase: error of create " << RECORD_VERTEX;
        qDebug() << query.lastError().text();
    } ;
    if(!query.exec("CREATE TABLE " RECORD_EDGE " ("
                                                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                               RECORD_DESTINATION1      " VARCHAR(255)    NOT NULL,"
                                                               RECORD_DESTINATION2      " VARCHAR(255)    NOT NULL,"
                                                               RECORD_DISTANCE          " DOUBLE"
                                                           " ) ")) {
        qDebug() << "DataBase: error of create " << RECORD_EDGE;
        qDebug() << query.lastError().text();
    } ;
        if(!query.exec( "CREATE TABLE " RECORD_SHIP " ("
                                                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                                RECORD_NAME              " VARCHAR(255)    NOT NULL,"
                                                                RECORD_TYPEOFSHIP        " VARCHAR(16)     NOT NULL,"
                                                                RECORD_PASSENGERCAPACITY " INTEGER,"
                                                                RECORD_PIER              " VARCHAR(18)     NOT NULL,"
                                                                RECORD_AVERAGESPEED      " DOUBLE,"
                                                                RECORD_PRICE             " DOUBLE"
                        " ) "
                    )){
        qDebug() << "DataBase: error of create " << RECORD_SHIP;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DataBaseMain::insertIntoRecordTable(const QVariantList &data)
{
    QSqlQuery query;
    if (data[5].toString()!=""){
    query.prepare("INSERT INTO " RECORD_SHIP " ( " RECORD_NAME ", "
                                              RECORD_TYPEOFSHIP ", "
                                              RECORD_PASSENGERCAPACITY ", "
                                              RECORD_PIER ", "
                                              RECORD_AVERAGESPEED ", "
                                              RECORD_PRICE " ) "
                  "VALUES (:Name, :TypeOfShip, :PassengerCapacity, :Pier, :AverageSpeed, :Price )");
    query.bindValue(":Name",                      data[0].toString());
    query.bindValue(":TypeOfShip",                data[1].toString());
    query.bindValue(":PassengerCapacity",         data[2].toInt());
    query.bindValue(":Pier",                      data[3].toString());
    query.bindValue(":AverageSpeed",              data[4].toDouble());
    query.bindValue(":Price",                     data[5].toDouble());
    if(!query.exec()){
        qDebug() << "error insert into " << RECORD_SHIP;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
    }
    else if (data[4].toDouble()!=0){
        query.prepare("INSERT INTO " RECORD_VERTEX " ( " RECORD_NAME ", "
                                                  RECORD_PIER ", "
                                                  RECORD_COORDINATE_X ", "
                                                  RECORD_COORDINATE_Y " ) "
                      "VALUES (:Name, :Pier, :CoordinateX, :CoordinateY )");
        query.bindValue(":Name",                     data[0].toString());
        query.bindValue(":Pier",                     data[1].toString());
        query.bindValue(":CoordinateX",              data[3].toDouble());
        query.bindValue(":CoordinateX",              data[4].toDouble());
        if(!query.exec()){
            qDebug() << "error insert into " << RECORD_VERTEX;
            qDebug() << query.lastError().text();
            return false;
        } else {
            return true;
        }
        return false;}
    else {
        query.prepare("INSERT INTO " RECORD_EDGE " ( " RECORD_DESTINATION1 ", "
                                                  RECORD_DESTINATION2 ", "
                                                  RECORD_DISTANCE " ) "
                      "VALUES (:Destination1, :Destination2, :Distance )");
        query.bindValue(":Destination1",                data[0].toString());
        query.bindValue(":Destination2",                data[1].toString());
        query.bindValue(":Distance",                    data[2].toDouble());
        if(!query.exec()){
            qDebug() << "error insert into " << RECORD_EDGE;
            qDebug() << query.lastError().text();
            return false;
        } else {
            return true;
        }
        return false;
    }
}

QVariantList DataBaseMain::getRecordsName()
{
    QSqlQuery query;
    QVariantList List;
    query.exec("SELECT " RECORD_NAME " FROM " RECORD_VERTEX);
    while (query.next()){
        List.append(query.value(0).toString());
    }
    return List;
}

QList<Vertex*> DataBaseMain::getVertexes()
{
    QSqlQuery query;
    QVariantList List_id, List_name, List_pier, List_coordinateX, List_coordinateY;
    QList<Vertex*> result_list;
    query.exec("SELECT id FROM " RECORD_VERTEX);
    while (query.next()){
        List_id.append(query.value(0).toInt());
    }
    query.exec("SELECT " RECORD_NAME " FROM " RECORD_VERTEX);
    while (query.next()){
        List_name.append(query.value(0).toString());
    }
    query.exec("SELECT " RECORD_PIER " FROM " RECORD_VERTEX);
    while (query.next()){
        List_pier.append(query.value(0).toBool());
    }
    query.exec("SELECT " RECORD_COORDINATE_X " FROM " RECORD_VERTEX);
    while (query.next()){
        List_coordinateX.append(query.value(0).toDouble());
    }
    query.exec("SELECT " RECORD_COORDINATE_Y " FROM " RECORD_VERTEX);
    while (query.next()){
        List_coordinateY.append(query.value(0).toDouble());
    }
    int i=0;
    while (i<List_id.size())
    {
        Vertex*  vertex = new Vertex();
        vertex->SetId(List_id.value(i).toInt());
        vertex->SetName(List_name.value(i).toString());
        vertex->SetPier(List_pier.value(i).toBool());
        vertex->SetCoordX(List_coordinateX.value(i).toDouble());
        vertex->SetCoordY(List_coordinateY.value(i).toDouble());
        result_list.append(vertex);
        i++;
    }
    return result_list;
}

QList<Edge*> DataBaseMain::getEdges()
{
    QSqlQuery query;
    QVariantList List_destination1, List_destination2, List_distance;
    QList<Edge*> result_list;
    query.exec("SELECT " RECORD_DESTINATION1 " FROM " RECORD_EDGE);
    while (query.next()){
        List_destination1.append(query.value(0).toString());
    }
    query.exec("SELECT " RECORD_DESTINATION2 " FROM " RECORD_EDGE);
    while (query.next()){
        List_destination2.append(query.value(0).toString());
    }
    query.exec("SELECT " RECORD_DISTANCE " FROM " RECORD_EDGE);
    while (query.next()){
        List_distance.append(query.value(0).toDouble());
    }
    int i=0;
    QList<Vertex*> list_vertex=getVertexes();
    while (i<List_destination1.size())
    {
        Edge* edge = new Edge();
        for (int j=0; j<list_vertex.size(); j++){
            if (list_vertex.value(j)->GetName()==List_destination1.value(i).toString())
                edge->SetDestination1(list_vertex.value(j));
            if (list_vertex.value(j)->GetName()==List_destination2.value(i).toString())
                edge->SetDestination2(list_vertex.value(j));
        }
        edge->SetDistance(List_distance.value(i).toDouble());
        result_list.append(edge);
        i++;
    }
    return result_list;
}

bool DataBaseMain::ExistsOfVertex(QString name)
{
    QSqlQuery query;
    QString str=QString("SELECT " RECORD_NAME " FROM " RECORD_VERTEX " WHERE " RECORD_NAME " = '%1'").arg(name);
    query.prepare(str);
    query.exec();
    if (query.value(0)!="") return true;
    else return false;
}

void DataBaseMain::deleteEdgesConnectsWithVertex(QString name)
{
    QSqlQuery query;
    QString str=QString("DELETE FROM " RECORD_EDGE " WHERE " RECORD_DESTINATION1 " = '%1' "
                        "OR " RECORD_DESTINATION2 " = '%1'" ).arg(name);
    query.prepare(str);
    query.exec();
}

QVariantList DataBaseMain::getShips(QString type,double distance, QString human,QString pier1,QString pier2)
{
    QSqlQuery query;
    QVariantList list_name,list_time,list_price,list_result;
    QString str_name,str_speed,str_price;
    if (pier1=="true" && pier2=="true") {
        str_name=QString("SELECT " RECORD_NAME " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                        RECORD_PASSENGERCAPACITY " >= '%2' ) ").arg(type,human);
        str_speed=QString("SELECT " RECORD_AVERAGESPEED " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                        RECORD_PASSENGERCAPACITY " >= '%2' ) ").arg(type,human);
        str_price=QString("SELECT " RECORD_PRICE " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                        RECORD_PASSENGERCAPACITY " >= '%2' ) ").arg(type,human);
    }
    else {
        str_name=QString("SELECT " RECORD_NAME " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                              RECORD_PASSENGERCAPACITY " >= '%2' AND " RECORD_PIER " = 'false' ) ").arg(type,human);
        str_speed=QString("SELECT " RECORD_AVERAGESPEED " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                              RECORD_PASSENGERCAPACITY " >= '%2' AND " RECORD_PIER " = 'false' ) ").arg(type,human);
        str_price=QString("SELECT " RECORD_PRICE " FROM " RECORD_SHIP " WHERE ( " RECORD_TYPEOFSHIP " = '%1' AND "
                              RECORD_PASSENGERCAPACITY " >= '%2' AND " RECORD_PIER " = 'false' ) ").arg(type,human);
    }
    query.prepare(str_name);
    query.exec();
    while (query.next()){
        list_name.append(query.value(0).toString());
    }
    query.prepare(str_speed);
    query.exec();
    while (query.next()){
        list_time.append(round(this->getTime(distance,query.value(0).toDouble())));
    }
    query.prepare(str_price);
    query.exec();
    int i=0;
    while (query.next()){
        list_price.append(round(this->getPrice(list_time.value(i).toDouble(),query.value(0).toDouble())*10)/10);
        i++;
    }
    i=0;
    while (i<list_name.size())
    {
        list_result.append(list_name.value(i).toString());
        list_result.append(list_time.value(i).toString());
        list_result.append(list_price.value(i).toDouble());
        i++;
    }
    return (list_result);
}

double DataBaseMain::getTime(double distance,double speed)
{
    return(distance*60/speed);
}

double DataBaseMain::getPrice(double time,double price)
{
    return(time*price/60);
}
