#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>
#include <occview.h>
#include <modeltreewidget.h>
#include <QSplitter>

namespace Ui {
class ModelWidget;
}

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelWidget(QWidget *parent = nullptr);
    ~ModelWidget();
    OccView* getAntannaWidget();
    OccView* getCableWidget();
    ModelTreeWidget * getModelTreeWidget();
    void setShadingDisplay();
    void setMeshDisPlay();
    void setWireFrameDisplay();
    void setProject(int i);
    void loadCableModel(QString path);
    void loadAntannaModel(QString path);
    void loadUAVModel(QString path);
    void leftWidgetAnimation(int index, bool isOut);
//    void generateMesh();
private:
    Ui::ModelWidget *ui;
    OccView * antannaWidget;
    OccView * cableWidget;
    ModelTreeWidget * uavWidget;
    void loadMesh(QString path);
    Handle(AIS_Shape)meshModel;
    Handle(AIS_Shape)faceModel;
    QString currentModelPath;
    QString meshPath;
    void createMesh(QString path,int refineNumm,int method);
    QByteArray state;

    QSplitter * splitterMain;
    QSplitter * splitterRight;

//    Handle(AIS_Shape)currentShape;
};

#endif // MODELWIDGET_H
