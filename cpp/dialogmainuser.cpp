#include "dialogmainuser.h"
#include "ui_dialogmainuser.h"

DialogMainUser::DialogMainUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMainUser)
{
    ui->setupUi(this);
    this->setWindowTitle("User Mode");
    db=new DataBaseMain();
    db->connectToDataBase();
    vertex_list = db->getVertexes();
    edge_list = db->getEdges();
    setupMapper();
    mapper->toLast();
    createUI();
}

DialogMainUser::DialogMainUser(QString name,QWidget *parent) :
    QDialog(parent),
    map_name(name),
    ui(new Ui::DialogMainUser)
{
    ui->setupUi(this);
    this->setWindowTitle("User Mode");
    db=new DataBaseMain();
    db->connectToDataBase();
    vertex_list = db->getVertexes();
    edge_list = db->getEdges();
    setupMapper();
    mapper->toLast();
    createUI();
}

DialogMainUser::~DialogMainUser()
{
    delete ui;
}

void DialogMainUser::setupMapper()
{
    mapper = new QDataWidgetMapper();
    mapper->addMapping(ui->comboBox, 1);
    mapper->addMapping(ui->comboBox_2, 2);
    mapper->addMapping(ui->comboBox_3, 3);
    mapper->addMapping(ui->spinBox,4);
    mapper->addMapping(ui->lineEdit,5);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}


void DialogMainUser::createUI()
{
    for (int i=0;i<vertex_list.size();i++)
    {
        ui->comboBox->addItem(vertex_list.value(i)->GetName());
        ui->comboBox_2->addItem(vertex_list.value(i)->GetName());
    }
    ui->comboBox_3->addItem("катер");
    ui->comboBox_3->addItem("теплоход");
    ui->comboBox_3->addItem("плавдача");
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(200);
    ui->lineEdit->setReadOnly(true);
}

void DialogMainUser::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    QImage pic1(width(),height(),QImage::Format_RGB32);
    QString map= QString("C:/Users/Tatyana/Desktop/все/3 курс/Курсовая работа/%1.png").arg(map_name);
    pic1.load(map);
    painter.drawImage(0,10,pic1);
    if (ui->pushButton_3->isEnabled()){
        QVariantList way=getDistance(ui->comboBox->currentText(),ui->comboBox_2->currentText());
        int i=0;
        while (i<vertex_list.size()){
            for(int j=1; j<way.size();j++){
              if (way.value(j).toString() == vertex_list.value(i)->GetName()) {
                  painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
                  break;
              }
              else
                  painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            }
              painter.drawEllipse(vertex_list.value(i)->GetCoordX(),vertex_list.value(i)->GetCoordY(), 10, 10);
              i++;
        }
        i=0;
        while (i<edge_list.size()){
            painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
            for(int j=1; j<way.size()-1;j++){
                if ((way.value(j).toString() == edge_list.value(i)->GetDestination1()->GetName() && way.value(j+1).toString() == edge_list.value(i)->GetDestination2()->GetName()) ||
                        (way.value(j).toString() == edge_list.value(i)->GetDestination2()->GetName() && way.value(j+1).toString() == edge_list.value(i)->GetDestination1()->GetName())) {
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::FlatCap));
                    break;
                }
                else
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
            }
            painter.drawLine(edge_list.value(i)->GetDestination1()->GetCoordX()+5,edge_list.value(i)->GetDestination1()->GetCoordY()+5,edge_list.value(i)->GetDestination2()->GetCoordX()+5,edge_list.value(i)->GetDestination2()->GetCoordY()+5);
            i++;
        }
    }
}

void DialogMainUser::on_pushButton_clicked()
{
    if (ui->comboBox->currentText()==ui->comboBox_2->currentText())
        QMessageBox::warning(this, trUtf8("Ошибка ввода"),
                             trUtf8("Одинаковые начальный и конечный пункты. \nПовторите ввод заново"));
    else {
    QVariantList list1;
    list1.append(ui->comboBox_3->currentText());
    list1.append(getDistance(ui->comboBox->currentText(),ui->comboBox_2->currentText()).value(0).toDouble());
    list1.append(ui->spinBox->value());
    for (int i=0;i<vertex_list.size();i++) {
        if (vertex_list.value(i)->GetName() == ui->comboBox->currentText()) list1.append(vertex_list.value(i)->GetPier());
        if (vertex_list.value(i)->GetName() == ui->comboBox_2->currentText()) list1.append(vertex_list.value(i)->GetPier());
    }
    DialogUserResult* UserResult =new DialogUserResult(list1);
    UserResult->show();
    this->close();
    }
}

void DialogMainUser::on_pushButton_2_clicked()
{
    ChooseMode *chooseMode = new ChooseMode();
    chooseMode->show();
    this->close();
}

QVariantList DialogMainUser::getDistance(QString Dest1,QString Dest2)
{
    const double MAX = 100000;
    double edges[vertex_list.size()*vertex_list.size()];
    QString ways[vertex_list.size()*vertex_list.size()];
    QVariantList result;
    for (int i=0;i<(vertex_list.size()*vertex_list.size());i++) edges[i]=MAX;
    int IDA(-1), IDB(-1);
    for (int i=0;i<vertex_list.size();i++) {
        if (vertex_list.value(i)->GetName() == Dest1) {
            IDA=vertex_list.value(i)->GetId();
            ways[IDA]=vertex_list.value(i)->GetName();
        }
        if (vertex_list.value(i)->GetName() == Dest2) IDB=vertex_list.value(i)->GetId();
    }
    edges[IDA]=0;
    for (int i = 0; i < vertex_list.size() - 1; i++) {
        for (int j=0; j < edge_list.size(); j++) {
            Edge *example = edge_list.value(j);
            if ((edges[example->GetDestination1()->GetId()] + example->GetDistance()) < edges[example->GetDestination2()->GetId()])
            {
                edges[example->GetDestination2()->GetId()] = edges[example->GetDestination1()->GetId()]+example->GetDistance();
                ways[example->GetDestination2()->GetId()] = QString(ways[example->GetDestination1()->GetId()]+";"+example->GetDestination2()->GetName());
            }
            if ((edges[example->GetDestination2()->GetId()] + example->GetDistance()) < edges[example->GetDestination1()->GetId()])
            {
                edges[example->GetDestination1()->GetId()] = edges[example->GetDestination2()->GetId()]+example->GetDistance();
                ways[example->GetDestination1()->GetId()] = QString(ways[example->GetDestination2()->GetId()]+";"+example->GetDestination1()->GetName());
            }
        }
    };
    if (edges[IDB] == MAX) {
        result.append(-1);
        result.append("");
    }
    else {
        result.append(edges[IDB]);
        int j = 0;
        while (j<ways[IDB].size()){
            QString vertex_id_str;
            for (int l=j;ways[IDB][l]!=QChar(';')&&l<ways[IDB].size();l++) {
                vertex_id_str=QString(vertex_id_str+ways[IDB][l]);
                j++;
            }
            result.append(vertex_id_str);
            j++;
        }
    }
    return result;
}

void DialogMainUser::on_pushButton_3_clicked()
{
    repaint();
    ui->lineEdit->setText(getDistance(ui->comboBox->currentText(),ui->comboBox_2->currentText()).value(0).toString());
}
