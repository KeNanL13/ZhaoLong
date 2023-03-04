#include "modeltreewidget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QDir>

ModelTreeWidget::ModelTreeWidget(QWidget *parent) : QWidget(parent)
{

    occWidget=new OccView();
    ModelTree=new QTreeView();
    materialProperty=new QtTreePropertyBrowser();
    //生成属性管理和属性编辑
    m_pVarManager=new QtVariantPropertyManager(materialProperty);
    m_pVarFactory=new QtVariantEditorFactory(materialProperty);

    //布局设置
    QSplitter * splitter=new QSplitter();
    QSplitter * splitterVer=new QSplitter(Qt::Orientation::Vertical);
    splitterVer->addWidget(ModelTree);
    splitterVer->addWidget(materialProperty);
    splitterVer->setStretchFactor(0,2);
    splitterVer->setStretchFactor(1,1);
    splitter->addWidget(splitterVer);
    splitter->addWidget(occWidget);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,2);
    QVBoxLayout *layout=new QVBoxLayout();
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
    //新建一个occ模型读取器
    reader=new occRead(occWidget->getContext());
    reader->ReadStep(QDir::currentPath()+QDir::separator()+"Models/Boeing F A-18 E F Super Hornet.step");

    QStandardItem * item=reader->getTreeNode();//从模型读取器中读取树节点
     model=new QStandardItemModel();
    //将itemModel加入树中
    model->appendRow(item);
    ModelTree->setModel(model);
    //设置occ窗口背景和视口，启用网格
    occWidget->getView()->SetBgGradientColors(Quantity_NOC_LIGHTSKYBLUE, Quantity_NOC_LIGHTSKYBLUE4, Aspect_GFM_VER);
    occWidget->getView()->FitAll();
//    occWidget->getViewer()->ActivateGrid(Aspect_GridType::Aspect_GT_Rectangular,Aspect_GridDrawMode::Aspect_GDM_Lines);
    //连接点击TreeView的槽函数
    connect(ModelTree,&QTreeView::clicked,this,&ModelTreeWidget::clicked);
    //通过属性管理器添加属性进属性窗口中
    //添加第一个属性
    typeItem=m_pVarManager->addProperty(QtVariantPropertyManager::enumTypeId(),"类型");//第一个属性，为枚举类，属性名为 类型
    map[typeItem]=QStringLiteral("类型");//将属性名和对应的属性添加进map中
    QStringList materialType;//类型 的列表
    materialType<<"默认（PEC）"<<"铜"<<"铁"<<"四氧化硅"<<"自定义材料";//输入类型的成员
    typeItem->setAttribute(QLatin1String("enumNames"), materialType);
    typeItem->setValue(0);
    materialProperty->addProperty(typeItem);

    //添加第二个属性
    materialItem=m_pVarManager->addProperty(QVariant::Double,"电导率");
    materialItem->setValue(1.0);
    materialProperty->addProperty(materialItem);
    map[materialItem]=QStringLiteral("电导率");
    //连接属性值改变槽函数
    connect(m_pVarManager,&QtVariantPropertyManager::valueChanged,this,&ModelTreeWidget::valueChanged);
    //窗口设置
    ModelTree->setHeaderHidden(true);//隐藏树表头
    materialProperty->setFactoryForManager(m_pVarManager,m_pVarFactory);//连接属性管理和编辑管理
    materialProperty->setVisible(false);//隐藏材料窗口，点击后再显示

}

void ModelTreeWidget::readModel(const QString &path)
{
    if(reader!=nullptr)
    {
        delete reader;
        reader=nullptr;
    }
    if(model!=nullptr)
    {
        delete model;
        model=nullptr;
    }
    reader=new occRead(occWidget->getContext());
    reader->ReadStep(path);
    QStandardItem * item=reader->getTreeNode();//从模型读取器中读取树节点
    model=new QStandardItemModel();
    //将itemModel加入树中
    model->appendRow(item);
    ModelTree->setModel(model);



}

void ModelTreeWidget::shadingModelShow()
{
    occWidget->getContext()->RemoveAll(false);
    for(auto x :reader->createdObjects)
    {
        occWidget->getContext()->Display(x,true);
    }

}

Handle(V3d_Viewer) ModelTreeWidget::getViewer()
{
    return occWidget->getViewer();
}

Handle(AIS_InteractiveContext) ModelTreeWidget::getContext()
{
    return occWidget->getContext();
}

Handle(V3d_View)ModelTreeWidget::getView()
{
 return occWidget->getView();
}

ModelTreeWidget::~ModelTreeWidget()
{

}

//点击函数，根据对应的QModelIndex 来获得 所点击的列表名字，通过名字QString 去寻找对应的label 。
//找到label 后通过occ模型查看器reader中的map看是否是展示模型的label;
//如果是零件的label 就高亮显示，不然就不显示（通过label获得模型 转换位置 线框显示来得到高亮效果）
//如果是零件的label 就显示属性窗口，不然就不显示
//如果是设置过的属性的label，从map中读取信息加载进去，否则设置成默认属性
void ModelTreeWidget::clicked(QModelIndex index)
{
    if(currentIndex==index)
    {
        return;
    }
    //记录目前的index
    currentIndex=index;
    //去除高亮模型
    for(auto x : listShapes)
    {
        occWidget->getContext()->Remove(x,false);
    }

    listShapes.clear();
    //文档 shapeTool 模型树Index的名字 与对应的label
    Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool( reader->getDoc()->Main() );
    QString name=index.data().toString();
    TDF_Label label= reader->mapOfItemToLabel.value(name);
    //检测该label 是否是显示的label，如果是就显示属性，不然就不显示。
    if(reader->mapOfPresentions.IsBound(label))
    {
        materialProperty->setVisible(true);
    }
    else {
        materialProperty->setVisible(false);
    }
    //如果记录过该label 的材料类型和参数。
    if(modelToMaterial.contains(name))
    {
        isShowMaterial=true;
        typeItem->setValue(modelToMaterial.value(name));//记录过就改变类型就可以了
    }
    else {
        //没记录过说明 没显示材料模型，属性设置为默认
        isShowMaterial=false;
        typeItem->setValue(0);
        materialItem->setValue(1.0);
    }
    //获得参考label
    TDF_Label refLabel = label;

    if(ShapeTool->IsReference(label))
    {
        ShapeTool->GetReferredShape(label,refLabel);
    }
    //生成高亮模型
  try {
      NCollection_List<Handle(AIS_InteractiveObject)> list=reader->mapOfPresentions.Find(label);
      TopoDS_Shape shape=ShapeTool->GetShape(refLabel);
            for(auto x : list)
            {
                Handle(AIS_Shape) sha=new AIS_Shape(shape);
                sha->SetWidth(5);
                sha->SetDisplayMode(0);
                sha->SetLocalTransformation(x->LocalTransformation());
                occWidget->getContext()->Display(sha,false);
                listShapes<<sha;
            }
  } catch (...) {
  }
    occWidget->getView()->Redraw();
}
//属性值改变 对应的槽函数
//
void ModelTreeWidget::valueChanged(QtProperty* property, const QVariant &value)
{
    //获取当前index的名字和label 和当前变化属性的值
    QString name=currentIndex.data().toString();
    TDF_Label label=reader->mapOfItemToLabel.value(name);


    if(map[property]=="类型")
    {
        int index=value.toInt();
//       for(auto x :nameToModel[name])
//       {
//           occWidget->getContext()->Remove(x,true);
//       }
//       nameToModel[name].clear();
       if(!isShowMaterial)
       {
           TDF_Label refLabel = label;
           Handle(XCAFDoc_ShapeTool) ShapeTool = XCAFDoc_DocumentTool::ShapeTool( reader->getDoc()->Main() );
           if(ShapeTool->IsReference(label))
           {
               ShapeTool->GetReferredShape(label,refLabel);
           }
           NCollection_List<Handle(AIS_InteractiveObject)> *list=reader->mapOfPresentions.ChangeSeek(label);
           TopoDS_Shape shape=ShapeTool->GetShape(refLabel);
           if(list!=nullptr)
           {
               QList<Handle(AIS_Shape)>listMaterialShapes;
               for(auto x : *list)
               {
                   Handle(AIS_Shape) sha=new AIS_Shape(shape);
                   sha->SetWidth(5);
                   sha->SetLocalTransformation(x->LocalTransformation());
                   listMaterialShapes<<sha;
               }
               nameToModel[name]=listMaterialShapes;
           }
       }
       switch (index) {
       case 0:
           materialItem->setValue(1.0);
           if(isShowMaterial){
           for(auto x :nameToModel[name])
           {
               occWidget->getContext()->Remove(x,true);
           }
           occWidget->getView()->Redraw();
           nameToModel[name].clear();
           }
           modelToElectri.remove(name);
           modelToMaterial.remove(name);
           isShowMaterial=false;
           break;
       case 1:
           materialItem->setValue(2.0);
           for(auto x:nameToModel[name])
           {
               x->SetMaterial(Graphic3d_NameOfMaterial::Graphic3d_NOM_BRONZE);
           }
           break;
       case 2:materialItem->setValue(3.0);
           for(auto x:nameToModel[name])
           {
               x->SetMaterial(Graphic3d_NameOfMaterial::Graphic3d_NOM_STEEL);
           }
           break;
       case 3:materialItem->setValue(0.0);
           for(auto x:nameToModel[name])
           {
               x->SetMaterial(Graphic3d_NameOfMaterial::Graphic3d_NOM_PLASTIC);
           }
           break;
       case 4:
           for(auto x : nameToModel[name])
           {
               x->SetMaterial(Graphic3d_NameOfMaterial::Graphic3d_NOM_GOLD);
           }
           if(modelToElectri.contains(currentIndex.data().toString()))
           {
               materialItem->setValue(modelToElectri[currentIndex.data().toString()]);
           }
       default:
           break;
       }
       if(index!=0)
       {
           for(auto x :nameToModel[name])
           {
               occWidget->getContext()->Display(x,true);
//               isShowMaterial=true;
           }
            isShowMaterial=true;
       }

    }
           if(reader->mapOfPresentions.IsBound(label)&&typeItem->value().toInt()!=0)
           {
               modelToElectri[name]=materialItem->value().toDouble();
               modelToMaterial[name]=typeItem->value().toInt();
           }
}
