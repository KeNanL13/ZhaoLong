#ifndef OCCREAD_H
#define OCCREAD_H

#include <QObject>
#include <QString>
#include <QStandardItem>
#include <QDebug>
#include <QMap>
/*******************OpenCascade Include *****************/
#include <NCollection_DataMap.hxx>
#include <NCollection_List.hxx>
#include <TCollection_ExtendedString.hxx>
#include <Resource_Unicode.hxx>
#include <AIS_ConnectedInteractive.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_PointCloud.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDocStd_Document.hxx>
#include <TopoDS_Iterator.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <XCAFPrs_Style.hxx>
#include <TDataStd_Name.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFApp_Application.hxx>
#include <AIS_ViewCube.hxx>
#include <Graphic3d_TransformPers.hxx>
class TDF_LabelMapHasher;
class TopLoc_Location;
class XCAFPrs_Style;
class TCollection_AsciiString;
class AIS_InteractiveObject;


typedef NCollection_DataMap<TDF_Label,
                            NCollection_List<Handle(AIS_InteractiveObject)>,
                            TDF_LabelMapHasher> LabelPrsMap;

class occRead:/*public Standard_Transient,*/public QObject
{
    Q_OBJECT
public:
    occRead(const Handle(AIS_InteractiveContext)& ctx,QObject *parent = nullptr);
    void ReadStep(QString path);
    Handle(TDocStd_Document)getDoc();
    QStandardItem * getTreeNode();
    LabelPrsMap mapOfOriginals;
    LabelPrsMap mapOfPresentions;
    QMap<QString,TDF_Label> mapOfItemToLabel;
//    QMap<Handle(AIS_InteractiveObject), TopLoc_Location> mapOfLocation;

    NCollection_List<Handle(AIS_ConnectedInteractive)> createdObjects;

//成员
private:
    Handle(AIS_InteractiveContext) m_ctx;
    Handle(TDocStd_Document)m_doc;
//成员函数
private:
    bool IsEmptyShape(const TopoDS_Shape& shape);
    QString toQString(TCollection_ExtendedString string);
    QStandardItem * m_treeNode;
    void displayItem(const TDF_Label&               label,
                     const TopLoc_Location&         parentTrsf,
                     const XCAFPrs_Style&           parentStyle,
                     const TCollection_AsciiString& parentId,
                     LabelPrsMap&                   mapOfOriginals,
                     QStandardItem*                 parentItem);
private:
//    NCollection_List<Handle(AIS_ConnectedInteractive)> createdObjects;
//    LabelPrsMap mapOfOriginals;
//    QMap<QString,TDF_Label> mapOfItemToLabel;

};

#endif // OCCREAD_H
