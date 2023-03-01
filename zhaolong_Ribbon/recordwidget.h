#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QPushButton>

namespace Ui {
class recordWidget;
}

class recordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit recordWidget(QWidget *parent = nullptr);
    ~recordWidget();
    void insert(QString type,QVector<double>parameters,QString path);
    void deleteAllData();
signals:
    void recordRun(int type,QStringList parametersList);

private:
    Ui::recordWidget *ui;
    QSqlDatabase dataBase;
    void connectDb();
    void createTable();


    void updateTableWidget();

    void deleteDataAt(int index);
    int typeStringToInt(QString type);

};

#endif // RECORDWIDGET_H
