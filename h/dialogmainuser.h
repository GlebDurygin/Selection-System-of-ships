#ifndef DIALOGMAINUSER_H
#define DIALOGMAINUSER_H
#include <QDialog>
#include <QDataWidgetMapper>
#include <QPainter>

#include "dialogchoosemode.h"
#include "dialoguserresult.h"

namespace Ui {
class DialogMainUser;
}

class DialogMainUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMainUser(QWidget *parent=0);
    DialogMainUser(QString name,QWidget *parent=0);
    //DialogMainUser(QString name);
    ~DialogMainUser();

signals:
    void signalReady();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::DialogMainUser          *ui;
    QDataWidgetMapper           *mapper;
    DataBaseMain                *db;
    QList<Vertex*>              vertex_list;
    QList<Edge*>                edge_list;
    QString                     map_name;

private:
    void setupMapper();
    void createUI();
    QVariantList getDistance(QString Dest1,QString Dest2);
};
#endif // DIALOGMAINUSER_H
