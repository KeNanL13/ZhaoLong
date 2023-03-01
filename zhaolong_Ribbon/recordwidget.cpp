#include "recordwidget.h"
#include "ui_recordwidget.h"
#include <QDebug>
#include <QDateTime>
#include <parameterwidget.h>

recordWidget::recordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recordWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"时间"<<"类型"<<"参数"<<""<<"");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    connectDb();
    updateTableWidget();





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
                  time TEXT NOT NULL,type TEXT NOT NULL,parameters TEXT NOT NULL)";
    if(sq.exec(sql))
    {
        qDebug()<<"建表成功";
    }
    else {
        qDebug()<<sq.lastError().text();
    }
}

void recordWidget::insert( QString type, QVector<double> parameters,QString path)
{
    qDebug()<<"插入操作开始";
    QString parameterString;
    for(int i=0;i<parameters.size();i++)
    {
        QString str;
        str=QString("%1").arg(parameters[i]);
        parameterString+=str+",";
    }
    if(type=="高速线")
    {
        parameterString+=path;
    }
    qDebug()<<parameterString;
    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy/MM/dd hh:mm");
    QString sql="INSERT INTO data(time,type,parameters) VALUES(?,?,?)";

    QSqlQuery sq;
    sq.prepare(sql);
    sq.addBindValue(time);
    sq.addBindValue(type);
    sq.addBindValue(parameterString);

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
            QString parameter=sq.value("parameters").toString();
            QStringList paraList=parameter.split(",");

            qDebug()<<time<<type<<paraList;

            int rowCount=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowCount);
            QPushButton * look=new QPushButton("查看");
            QPushButton * run=new QPushButton("运行");
            QPushButton * clear=new QPushButton("删除");

            ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(time));
            ui->tableWidget->item(rowCount,0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(type));
            ui->tableWidget->item(rowCount,1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            ui->tableWidget->setCellWidget(rowCount,2,look);
            ui->tableWidget->setCellWidget(rowCount,3,run);
            ui->tableWidget->setCellWidget(rowCount,4,clear);
            connect(look,&QPushButton::clicked,this,[=](){
                int t=typeStringToInt(type);
                ParameterWidget * widget=new ParameterWidget(t,paraList);
                widget->setAttribute(Qt::WA_ShowModal, true);
                widget->setAttribute(Qt::WA_DeleteOnClose);
                widget->show();

            });
            connect(clear,&QPushButton::clicked,this,[=](){

                this->deleteDataAt(index);
            });
            connect(run,&QPushButton::clicked,this,[=](){
                emit this->recordRun(typeStringToInt(type),paraList);
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
