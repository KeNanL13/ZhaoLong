#include "recordwidget.h"
#include "ui_recordwidget.h"
#include <QDebug>
#include <QDateTime>
#include <parameterwidget.h>
#include <qtmaterialflatbutton.h>


recordWidget::recordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"时间"<<"类型"<<"参数"<<""<<"");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    connectDb();
    updateTableWidget();
    infoSlideWidget=new SlideWidget_INFO(15,"参数查看",this);




}

recordWidget::~recordWidget()
{
    delete ui;
}

void recordWidget::connectDb()
{
    dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("simulation_info.db");
    dataBase.setUserName("s1");
    dataBase.setPassword("123");
    if(dataBase.open())
    {
        qDebug()<<"成功";
        createTable();
    }
    else {
        QSqlError error=dataBase.lastError();
        qDebug()<<error.text();
    }
}

void recordWidget::createTable()
{
    QSqlQuery sq;
    QString sql="CREATE TABLE IF NOT EXISTS data(id INTEGER PRIMARY KEY,\
                  time TEXT NOT NULL,type TEXT NOT NULL,title TEXT NOT NULL,value TEXT NOT NULL,metrics TEXT NOT NULL)";
    if(sq.exec(sql))
    {
        qDebug()<<"建表成功";
    }
    else {
        qDebug()<<sq.lastError().text();
    }
}



void recordWidget::insert(QVector<QString> title, QVector<QString>value, QVector<QString> metrics)
{
    qDebug()<<"title size"<<title.size();
    if(title.size()!=value.size() || title.size()!=metrics.size())
    {
        qDebug()<<"size error";
        return;
    }
    qDebug()<<"插入操作开始";
    QString titleString;
    for(int i=0;i<title.size();i++)
    {
        titleString+=title[i]+",";
    }

    QString valueString;
    for(int i=0;i<value.size();i++)
    {
        valueString+=value[i]+",";
    }

    QString metricsString;
    for(int i=0;i<metrics.size();i++)
    {
        metricsString+=metrics[i]+",";
    }

    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy/MM/dd hh:mm");
    QString sql="INSERT INTO data(time,type,title,value,metrics) VALUES(?,?,?,?,?)";

    QSqlQuery sq;
    sq.prepare(sql);
    sq.addBindValue(time);
    sq.addBindValue(value[0]);
    sq.addBindValue(titleString);
    sq.addBindValue(valueString);
    sq.addBindValue(metricsString);
qDebug()<<"data add finish";
    if(sq.exec())
    {
        updateTableWidget();//添加到表中
        qDebug()<<"添加成功";
    }
    else {
        QString errorMsg=sq.lastError().text();
        qDebug()<<errorMsg;
    }
}

void recordWidget::updateTableWidget()
{
    ui->tableWidget->setRowCount(0);

    QSqlQuery sq;
    QString sql="SELECT * FROM data";
    if(sq.exec(sql))
    {
        while(sq.next())
        {
            int index=sq.value("id").toInt();
            QString time=sq.value("time").toString();
            QString type=sq.value("type").toString();
            QString title=sq.value("title").toString();
            QStringList titleList=title.split(",");
            QString value=sq.value("value").toString();
            QStringList valueList=value.split(",");
            QString metrics=sq.value("metrics").toString();
            QStringList metricsList=metrics.split(",");
            titleList.removeLast();
            metricsList.removeLast();
            valueList.removeLast();

//            qDebug()<<time<<type<<titleList;

            int rowCount=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
//            QPushButton * look=new QPushButton("查看");

//            QPushButton * run=new QPushButton("运行");
//            QPushButton * clear=new QPushButton("删除");
            QtMaterialFlatButton * look=new QtMaterialFlatButton("查看");
            QtMaterialFlatButton * run=new QtMaterialFlatButton("运行");
            QtMaterialFlatButton *clear=new QtMaterialFlatButton("删除");

            ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(time));
            ui->tableWidget->item(rowCount,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(type));
            ui->tableWidget->item(rowCount,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->setCellWidget(rowCount,2,look);
            ui->tableWidget->setCellWidget(rowCount,3,run);
            ui->tableWidget->setCellWidget(rowCount,4,clear);
            connect(look,&QPushButton::clicked,this,[=](){
//                int t=typeStringToInt(type);
                infoSlideWidget->removeAll();
                infoSlideWidget->createPage(titleList,valueList,metricsList);
//                ParameterWidget * widget=new ParameterWidget(t,paraList);
                infoSlideWidget->slideIn();

            });
            connect(clear,&QPushButton::clicked,this,[=](){

                this->deleteDataAt(index);
            });
            connect(run,&QPushButton::clicked,this,[=](){
                emit this->recordRun(typeStringToInt(valueList[0]),valueList);
            });


        }
    }
    else {
        qDebug()<<sq.lastError().text();
    }
}

void recordWidget::deleteAllData()
{
    QSqlQuery sq;
    QString sql="DELETE FROM data";

    if(sq.exec(sql))
    {
        updateTableWidget();
        qDebug()<<"删除成功";

    }
    else {
        qDebug()<<sq.lastError().text();
    }

}

void recordWidget::deleteDataAt(int index)
{
    int id=index;
    QSqlQuery sq;
    QString sql="DELETE FROM data WHERE id=:id";
    sq.prepare(sql);
    sq.addBindValue(id);

    if(sq.exec())
    {
        updateTableWidget();
        qDebug()<<"删除成功";

    }
    else {
        qDebug()<<sq.lastError().text();
    }
}

int recordWidget::typeStringToInt(QString type)
{
    int t;
    if(type=="高速线")
    {t=2;}
    else if (type=="绞折线") {
        t=1;}
    else {
        t=0;
    }
    return t;
}

void recordWidget::resizeEvent(QResizeEvent *event)
{
    if(infoSlideWidget)
    {
        infoSlideWidget->resize(this->width() * 0.3 < infoSlideWidget->preferWidth ? infoSlideWidget->preferWidth  : this->width() * 0.3 , this->height());
    }
}
