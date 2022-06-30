#ifndef CABLESELECTDIALOG_H
#define CABLESELECTDIALOG_H

#include <QWidget>
#include <QSplitter>
#include <QDebug>
#include <QListWidgetItem>
#include <QList>
#include <QFileDialog>


namespace Ui {
class CableSelectDialog;
}

class CableSelectDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CableSelectDialog(QWidget *parent = nullptr);
    ~CableSelectDialog();
    QList<QString> parameters;
    enum modelType{None,TWP_Cable,ParallelCable,SystemS_parameters,HighSpped,TBTWBcable};
signals:
    void parallelCableSignal();
    void TWPCableSignal();
    void fixtureAndCable();
    void TBTWBcableSignal();
    void highSpeedCable();
    void CableSignal(enum modelType modeltype,QString stepModelPath);//输入模型类型和对应的模型文件路径
private:
    Ui::CableSelectDialog *ui;
    void itemCliked(QListWidgetItem * item);
    void item1UIChange();
    void item2UIChange();
    void item3UIChange();
    void item4UIChange();
    void confirmBtn();
    void receiveMessage();
};

#endif // WIDGET_H
