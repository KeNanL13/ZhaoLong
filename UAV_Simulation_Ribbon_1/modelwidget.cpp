#include "modelwidget.h"
#include "ui_modelwidget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <Poly_Triangulation.hxx>
#include <RWStl.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Edge.hxx>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <gmsh.h>

ModelWidget::ModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelWidget)
{
    ui->setupUi(this);
    antannaWidget=new OccView();
    cableWidget=new OccView;
    uavWidget=new ModelTreeWidget;
    QVBoxLayout * layoutMain=new QVBoxLayout;
    splitterMain=new QSplitter;
    splitterRight=new QSplitter(Qt::Vertical);
    splitterRight->addWidget(antannaWidget);
    splitterRight->addWidget(cableWidget);
    splitterMain->addWidget(ui->scrollArea);//
    splitterMain->addWidget(uavWidget);
    splitterMain->addWidget(splitterRight);

    QList<int>list;
    list<<1000<<4000<<4000;
    splitterMain->setSizes(list);

    ui->scrollArea->setVisible(false);
    state=splitterMain->saveState();
    splitterRight->setVisible(false);

    layoutMain->addWidget(splitterMain);
    this->setLayout(layoutMain);
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){

        QString MeshPath=currentModelPath.split(".")[0]+".msh";

        this->createMesh(MeshPath,ui->spinBox->value(),ui->comboBox->currentIndex());
        this->loadMesh(meshPath);
        this->setMeshDisPlay();
        uavWidget->getView()->FitAll();
    });
}

ModelWidget::~ModelWidget()
{
    delete ui;
}

OccView *ModelWidget::getAntannaWidget()
{
    if(antannaWidget==nullptr)
    {
        return antannaWidget=new OccView;
    }
     return antannaWidget;
}

OccView *ModelWidget::getCableWidget()
{
     if(cableWidget==nullptr)
     {
         return cableWidget=new OccView;
     }
     return  cableWidget;
}

ModelTreeWidget *ModelWidget::getModelTreeWidget()
{
    if(uavWidget==nullptr)
    {
        return uavWidget=new ModelTreeWidget;
    }
    return  uavWidget;
}

void ModelWidget::setShadingDisplay()
{
    uavWidget->shadingModelShow();
}

void ModelWidget::setMeshDisPlay()
{
    uavWidget->getContext()->RemoveAll(false);
//    this->loadMesh("C:/Users/Administrator/Desktop/stepModels/Model/Assem1gg.stl");
    uavWidget->getContext()->Display(meshModel,false);
    uavWidget->getContext()->Display(faceModel,true);
}

void ModelWidget::setWireFrameDisplay()
{
    uavWidget->getContext()->RemoveAll(false);
//    this->loadMesh("C:/Users/Administrator/Desktop/stepModels/Model/Assem1gg.stl");
    uavWidget->getContext()->Display(meshModel,true);
}

void ModelWidget::setProject(int i)
{
    qDebug()<<i;
    switch (i) {
    case 0:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Front);
        uavWidget->getView()->Update();
        break;
    case 1:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Left);
        uavWidget->getView()->Update();
        break;
    case 2:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Right);
        uavWidget->getView()->Update();
        break;
    case 3:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Top);
        uavWidget->getView()->Update();
        break;
    case 4:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Bottom);
        uavWidget->getView()->Update();
        break;
    case 5:uavWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Back);
        uavWidget->getView()->Update();
        break;
    case 6:uavWidget->getView()->FitAll();
        uavWidget->getView()->Update();
        break;
    default:
        break;
    }
}

void ModelWidget::loadCableModel(QString path)
{
    STEPCAFControl_Reader reader1;
    TDF_LabelSequence roots;
    IFSelect_ReturnStatus status= reader1.ReadFile(path.toStdString().c_str());
    if(status==false)
    {
        return ;
    }
    Handle(XCAFApp_Application) anApp=XCAFApp_Application::GetApplication();
    Handle(TDocStd_Document)doc;
    anApp->NewDocument("MDTV-XCAF",doc);
    bool yes=reader1.Transfer(doc);
    qDebug()<<yes;

    TDF_Label mainLabel=doc->Main();
    Handle(XCAFDoc_ShapeTool)ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    // Get root shapes to visualize.
    ShapeTool->GetFreeShapes(roots);


    Handle(XCAFPrs_AISObject) model=new XCAFPrs_AISObject(roots.First());
    cableWidget->getContext()->Display(model,true);

}

void ModelWidget::loadAntannaModel(QString path)
{
    STEPCAFControl_Reader reader1;
    TDF_LabelSequence roots;
    IFSelect_ReturnStatus status= reader1.ReadFile(path.toStdString().c_str());
    if(status==false)
    {
        return ;
    }
    Handle(XCAFApp_Application) anApp=XCAFApp_Application::GetApplication();
    Handle(TDocStd_Document)doc;
    anApp->NewDocument("MDTV-XCAF",doc);
    bool yes=reader1.Transfer(doc);
    qDebug()<<yes;

    TDF_Label mainLabel=doc->Main();
    Handle(XCAFDoc_ShapeTool)ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    // Get root shapes to visualize.
    ShapeTool->GetFreeShapes(roots);


    Handle(XCAFPrs_AISObject) model=new XCAFPrs_AISObject(roots.First());
    antannaWidget->getContext()->Display(model,true);
}

void ModelWidget::loadUAVModel(QString path)
{
    currentModelPath=path;
    uavWidget->readModel(path);
    uavWidget->getView()->FitAll();
//    if(!meshModel.IsNull())
//    {
//        meshModel->Delete();
//        meshModel=nullptr;
//    }
//    if(!faceModel.IsNull())
//    {
//        faceModel->Delete();
//        faceModel=nullptr;
//    }
}

void ModelWidget::loadMesh(QString path)
{
    QString pathMesh(path);
//    this->createMesh(shape,pathMesh);
    Handle(Poly_Triangulation) aSTLMesh = RWStl::ReadFile (pathMesh.toStdString().c_str());


    TopoDS_Compound compound;
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(compound);
    for(Standard_Integer i=1;i<=aSTLMesh->NbTriangles();i++)
    {
        const Poly_Triangle trian=aSTLMesh->Triangle(i);
        Standard_Integer index1,index2,index3,M=0,N=0;
        trian.Get(index1,index2,index3);
        for(Standard_Integer j=1;j<=3;j++)
        {
            switch (j) {
            case 1:M=index1;
                N=index2;

                break;
            case 2:N=index3;
                break;
            case 3:M=index2;
                break;
            default:
                break;
            }
            BRepBuilderAPI_MakeEdge anEdgeMaker(aSTLMesh->Node(M),aSTLMesh->Node(N));
            if(anEdgeMaker.IsDone())
            {
                aBuilder.Add(compound,anEdgeMaker.Edge());
            }
        }
        qDebug()<<"第"<<i<<"个三角形了";
    }
    meshModel=new AIS_Shape(compound);
    meshModel->SetColor(Quantity_NOC_BLACK);
    BRep_Builder builder;
    TopoDS_Face face;
    TopoDS_Shape shapeStl;
    builder.MakeFace(face);
    builder.UpdateFace(face,aSTLMesh);



    faceModel=new AIS_Shape(face);
    faceModel->SetColor(Quantity_NOC_SNOW);
}

void ModelWidget::createMesh(QString path, int refineNum,int method)
{
    using namespace gmsh;
    initialize();

    gmsh::open(path.toStdString());
    option::setNumber("General.Terminal", 1);
    option::setNumber("General.Verbosity", 5);
    option::setNumber("Mesh.Algorithm", method+1);
    option::setNumber("Mesh.Algorithm3D", 1);
//    option::setNumber("Mesh.CharacteristicLengthMax", 20);
//    option::setNumber("Mesh.CharacteristicLengthScale",20);
//    option::setNumber("Mesh.SurfaceFaces", 1);





    std::vector<std::pair<int,int>> dimTags;

//    model::occ::importShapes(path.toStdString(),dimTags);
//    model::occ::importShapes("Boeing F A-18 E F Super Hornet.msh",dimTags);
//    model::occ::synchronize();

//    model::mesh::setSize(dimTags,1);
//    model::mesh::generate(3);

    for(int i=0;i<refineNum;i++)
    {
        model::mesh::refine();
    }


    write("cl.stl");
    meshPath="cl.stl";


    finalize();
}

void ModelWidget::leftWidgetAnimation(int index, bool isOut)
{
    Q_UNUSED(index);
   if(isOut)
   {
       ui->scrollArea->setVisible(false);

   }
   else {
       ui->scrollArea->setVisible(true);
       splitterMain->restoreState(state);
   }
}

