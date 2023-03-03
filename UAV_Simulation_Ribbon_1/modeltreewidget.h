#ifndef MODELTREEWIDGET_H
#define MODELTREEWIDGET_H

#include <QWidget>
#include <occread.h>
#include <occview.h>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractItemModel>
//#include <qtpropertybrowser.h>
#include <qtpropertymanager.h>
#include <qtvariantproperty.h>
#include <qttreepropertybrowser.h>


class ModelTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelTreeWidget(QWidget *parent = nullptr);
    Handle(V3d_View) getView();
    Handle(V3d_Viewer)getViewer();
    Handle(AIS_InteractiveContext)getContext();

    void readModel(const QString &path);
    void shadingModelShow();

    ~ModelTreeWidget();

private:
    OccView * occWidget;
    QTreeView * ModelTree;
    occRead *reader;

    QStandardItemModel * model;
    QtTreePropertyBrowser * materialProperty;
    QtVariantPropertyManager*m_pVarManager;
    QtVariantEditorFactory*m_pVarFactory;
    QtVariantProperty * materialItem;
    QtVariantProperty * typeItem;

    QList<Handle(AIS_Shape)>listShapes;

    QModelIndex currentIndex;

    QMap<QtProperty*,QString> map;
    QMap<QString,double> modelToElectri;
    QMap<QString,int > modelToMaterial;
    QMap<QString,QList<Handle(AIS_Shape)>>nameToModel;
    bool isShowMaterial=false;
public slots:
    void clicked(QModelIndex index);
    void valueChanged(QtProperty*,const QVariant&);
};

#endif // MODELTREEWIDGET_H
