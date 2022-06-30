#include "occread.h"

occRead::occRead(const Handle(AIS_InteractiveContext)& ctx,QObject *parent )
    : /*Standard_Transient (),*/
      QObject            (parent),
      m_ctx              (ctx)
{

}


void occRead::ReadStep(QString path)
{
    //声明一个阅读器
     STEPCAFControl_Reader reader1;
     //配置阅读器
     reader1.SetNameMode(true);
     reader1.SetColorMode(true);
     //读取文件
     if(!reader1.ReadFile(path.toStdString().c_str()))
     {
         qDebug()<<"未成功读取文件";
     }
     //从读取文件中生成文档
     Handle(XCAFApp_Application) anApp=XCAFApp_Application::GetApplication();
     anApp->NewDocument("MDTV-XCAF",m_doc);
     if(!reader1.Transfer(m_doc))
     {
         qDebug()<<"未成功转换成文档";
         return;
     }
     //清除所有显示物体
     m_ctx->RemoveAll(false);

     // 获得XDE工具
     Handle(XCAFDoc_ShapeTool)ShapeTool = XCAFDoc_DocumentTool::ShapeTool(m_doc->Main());
     // Get root shapes to visualize.
     TDF_LabelSequence roots;
     ShapeTool->GetFreeShapes(roots);
     // 默认风格
     XCAFPrs_Style defaultStyle;
     defaultStyle.SetColorSurf(Quantity_NOC_GREEN);
     defaultStyle.SetColorCurv(Quantity_Color(0.0, 0.4, 0.0, Quantity_TOC_sRGB));
     //原始数据映射
     LabelPrsMap mapOfOriginals;
     //遍历根形状
     for ( TDF_LabelSequence::Iterator lit(roots); lit.More(); lit.Next() )
     {
       const TDF_Label& L         = lit.Value();
       TopLoc_Location  parentLoc = ShapeTool->GetLocation(L);
       //获得根目录树节点
       Handle(TDataStd_Name) name1;
       L.FindAttribute(TDataStd_Name::GetID(),name1);
       m_treeNode=new QStandardItem(toQString(name1->Get()));
       //遍历子节点，找到所有形状
       this->displayItem(L, parentLoc, defaultStyle, "", mapOfOriginals,m_treeNode);
     }

     emit readDone(m_treeNode);
}

void occRead::displayItem(const TDF_Label &label, const TopLoc_Location &parentTrsf, const XCAFPrs_Style &parentStyle, const TCollection_AsciiString &parentId, LabelPrsMap &mapOfOriginals, QStandardItem *parentItem)
{
    // Get XDE tools.
    Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool( m_doc->Main() );
    Handle(XCAFDoc_ColorTool) ColorTool = XCAFDoc_DocumentTool::ColorTool(  m_doc->Main() );
    // Get referred label for instances or root refs.
    TDF_Label refLabel = label;
    if ( ShapeTool->IsReference(label) )
        ShapeTool->GetReferredShape(label, refLabel);
    //获取ID
    TCollection_AsciiString itemId;
    TDF_Tool::Entry(label, itemId);
    //判断标签是否是Assembly
    if ( !ShapeTool->IsAssembly(refLabel) )
    {
        Handle(AIS_ConnectedInteractive)                   brepConnected;
        NCollection_List<Handle(AIS_ConnectedInteractive)> createdObjects;
        //在map中寻找refLabel是否有对应的值
        NCollection_List<Handle(AIS_InteractiveObject)>*aisListPtr = mapOfOriginals.ChangeSeek(refLabel);
        //如果返回的是空指针，说明refLabel是新标签，创造形状连接并储存起来
        if ( aisListPtr == nullptr )
        {
            NCollection_List<Handle(AIS_InteractiveObject)> itemRepresList;//存储展示物体的列表
            TopoDS_Shape shape = ShapeTool->GetShape(refLabel);//获得标签的形状
            //如果形状不为空
            if(!this->IsEmptyShape(shape))
            {
                Handle(AIS_ColoredShape) brepPrs = new XCAFPrs_AISObject(refLabel);//显示物体
                brepConnected = new AIS_ConnectedInteractive();//源物体
                brepConnected->Connect(brepPrs);//连接显示物体
                itemRepresList.Append(brepPrs);
                aisListPtr = mapOfOriginals.Bound( refLabel, itemRepresList );//在map中绑定label和list
            }
        }
        else {
            NCollection_List<Handle(AIS_InteractiveObject)>::Iterator it(*aisListPtr);
            for ( ; it.More(); it.Next() )
            {
                const Handle(AIS_InteractiveObject)& aisOriginal = it.Value();

                if ( aisOriginal->IsKind( STANDARD_TYPE(XCAFPrs_AISObject) ) )
                {
                    Handle(XCAFPrs_AISObject) brepPrs = Handle(XCAFPrs_AISObject)::DownCast( it.Value() );
                    brepConnected = new AIS_ConnectedInteractive();
                    brepConnected->Connect(brepPrs);
                }
            }
        }
        if ( !brepConnected.IsNull() )
        {
          brepConnected->SetDisplayMode         ( AIS_Shaded );
          brepConnected->SetLocalTransformation ( parentTrsf.Transformation() );
          try
          {
            m_ctx->Display(brepConnected, false);
            createdObjects.Append(brepConnected);
          }
          catch (...)
          {
            m_ctx->Remove(brepConnected, Standard_False);
            mapOfOriginals.UnBind(refLabel);
          }
        }
        return;
    }
    //设置风格
    XCAFPrs_Style defStyle = parentStyle;
    Quantity_ColorRGBA color;
    if ( ColorTool->GetColor(refLabel, XCAFDoc_ColorGen, color) )
    {
      defStyle.SetColorCurv( color.GetRGB() );
      defStyle.SetColorSurf( color );
    }
    if ( ColorTool->GetColor(refLabel, XCAFDoc_ColorSurf, color) )
    {
      defStyle.SetColorSurf( color );
    }
    if ( ColorTool->GetColor(refLabel, XCAFDoc_ColorCurv, color) )
    {
      defStyle.SetColorCurv( color.GetRGB() );
    }

    // In case of an assembly, move on to the nested component.
    for ( TDF_ChildIterator childIt(refLabel); childIt.More(); childIt.Next() )
    {
      TDF_Label childLabel = childIt.Value();
      Handle(TDataStd_Name) name1;
      childLabel.FindAttribute(TDataStd_Name::GetID(),name1);
      QStandardItem * item=new QStandardItem(toQString(name1->Get()));
      parentItem->appendRow(item);


      if ( !childLabel.IsNull() && ( childLabel.HasAttribute() || childLabel.HasChild() ) )
      {
        TopLoc_Location trsf = parentTrsf * ShapeTool->GetLocation(childLabel);
        this->displayItem(childLabel, trsf, defStyle, itemId, mapOfOriginals,item);
      }
    }

}

QString occRead::toQString(TCollection_ExtendedString string)
{
    char* str = new char[string.LengthOfCString() + 1];
    string.ToUTF8CString(str);
    QString string1=QString::fromUtf8(str);
    return string1;
}

bool occRead::IsEmptyShape(const TopoDS_Shape& shape)
{
  if ( shape.IsNull() )
    return true;

  if ( shape.ShapeType() >= TopAbs_FACE )
    return false;

  int numSubShapes = 0;
  for ( TopoDS_Iterator it(shape); it.More(); it.Next() )
    numSubShapes++;

  return numSubShapes == 0;
}
