#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QPushButton>
#include <slidewidget_info.h>
namespace Ui {
class recordWidget;
}

class recordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit recordWidget(QWidget *parent = nullptr);
    ~recordWidget();

    void insert(QVector<QString>,QVector<QString>,QVector<QString>);
    void deleteAllData();
signals:
    void recordRun(int type,QStringList parametersList);


private:
    Ui::recordWidget *ui;
    QSqlDatabase dataBase;
    void connectDb();
    void createTable();
    SlideWidget_INFO * infoSlideWidget=nullptr;


    void updateTableWidget();

    void deleteDataAt(int index);
    int typeStringToInt(QString type);


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // RECORDWIDGET_H
