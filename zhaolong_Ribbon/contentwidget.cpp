#include "contentwidget.h"
#include "ui_contentwidget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QFileDialog>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <gp_Circ.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GC_MakeSegment.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <AIS_Shape.hxx>
#include <QDebug>
contentWidget::contentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contentWidget)
{
    ui->setupUi(this);
    occWidget=new OccView();
    occWidget->getView()->SetBgGradientColors(Quantity_NOC_LIGHTSKYBLUE, Quantity_NOC_LIGHTSKYBLUE4, Aspect_GFM_VER);

    QSplitter * splitter=new QSplitter();
    splitter->addWidget(ui->scrollArea);
    splitter->addWidget(occWidget);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,2);
    QVBoxLayout * layout=new QVBoxLayout();
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);
    connect(ui->pushButton_default2,&QPushButton::clicked,[=](){
        ui->lineEdit_2_1->setText("0.2075");
        ui->lineEdit_2_2->setText("1.42");
        ui->lineEdit_2_3->setText("0.71");
        ui->lineEdit_2_4->setText("2");
        ui->lineEdit_2_5->setText("0.0005");
        ui->lineEdit_2_6->setText("0.009");
        ui->lineEdit_2_7->setText("200");
        ui->lineEdit_2_8->setText("0.07");
        ui->lineEdit_2_9->setText("1");
        ui->lineEdit_2_10->setText("40");
        ui->comboBox_RandC->setCurrentIndex(3);

    });
    ui->lineEdit_path->setVisible(ui->checkBox->isChecked());
    ui->pushButton->setVisible(ui->checkBox->isChecked());
    connect(ui->checkBox,&QCheckBox::clicked,this,[=](){
        ui->lineEdit_path->setVisible(ui->checkBox->isChecked());
        ui->pushButton->setVisible(ui->checkBox->isChecked());
    });
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        QString path=QFileDialog::getOpenFileName(this,"查找夹具文件",QDir::currentPath());
        if(!path.isNull()&&!path.isEmpty())
        {
            ui->lineEdit_path->setText(path);
        }
    });
    ui->scrollArea->setVisible(false);
    //setting
    currentShapeLine<<ui->lineEdit_2_1<<ui->lineEdit_2_2<<ui->lineEdit_2_3<<ui->lineEdit_2_6<<ui->lineEdit_2_7;
    for(auto x: currentShapeLine)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
           if(this->isFitAll(currentShapeLine))
           {
               qDebug()<<"start1";
               double r1=currentShapeLine[0]->text().toDouble();
               double d=currentShapeLine[1]->text().toDouble();
               double r2=currentShapeLine[2]->text().toDouble();
               double h=currentShapeLine[3]->text().toDouble();
               double l=currentShapeLine[4]->text().toDouble();
               this->createHighSpeedCable(r1,d,r2,h,l);
           }
           qDebug()<<111;
        });
    }
}

contentWidget::~contentWidget()
{
    delete ui;
}

void contentWidget::changeCablePage(int index)
{
    if(!ui->scrollArea->isVisible())
    {
        ui->scrollArea->setVisible(true);
    }
    ui->stackedWidget->setCurrentIndex(index);
    currentShapeLine.clear();
    switch (index) {
    case 0:

        break;
    case 1:
        break;
    case 2:
        currentShapeLine<<ui->lineEdit_2_1<<ui->lineEdit_2_2<<ui->lineEdit_2_3<<ui->lineEdit_2_6<<ui->lineEdit_2_7;
        break;
    default:
        break;
    }
//    qDebug()<<index;
//    if(index==2)
//    {
//        STEPCAFControl_Reader reader1;
//        TDF_LabelSequence roots;
//        IFSelect_ReturnStatus status= reader1.ReadFile("cable.step");
//        if(status==false)
//        {
//            return ;
//        }
//        Handle(XCAFApp_Application) anApp=XCAFApp_Application::GetApplication();
//        Handle(TDocStd_Document)doc;
//        anApp->NewDocument("MDTV-XCAF",doc);
//        bool yes=reader1.Transfer(doc);
//        qDebug()<<yes;

//        TDF_Label mainLabel=doc->Main();
//        Handle(XCAFDoc_ShapeTool)ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
//        // Get root shapes to visualize.
//        ShapeTool->GetFreeShapes(roots);


//        Handle(XCAFPrs_AISObject) model=new XCAFPrs_AISObject(roots.First());
//        occWidget->getContext()->Display(model,true);
//    }
}

QVector<double> contentWidget::getInputParameters(int index)
{
    QVector<double> parameters;
    switch (index) {
    case 0:

        break;
    case 1:
        break;
    case 2:

        parameters.push_back( ui->lineEdit_2_1->text().toDouble()*(ui->comboBox2_1->currentIndex()?1:1e-3));
        parameters.push_back(ui->lineEdit_2_2->text().toDouble()*(ui->comboBox2_2->currentIndex()?1:1e-3));
        parameters.push_back(ui->lineEdit_2_3->text().toDouble()*(ui->comboBox2_3->currentIndex()?1:1e-3));
        parameters.push_back(ui->lineEdit_2_4->text().toDouble());
        parameters.push_back(ui->lineEdit_2_5->text().toDouble());
        parameters.push_back(ui->lineEdit_2_6->text().toDouble()*(ui->comboBox2_6->currentIndex()?1:1e-3));
        parameters.push_back(ui->lineEdit_2_7->text().toDouble()*(ui->comboBox2_7->currentIndex()?1:1e-3));
        parameters.push_back(ui->comboBox_2_1->currentIndex()?1:38160000);
        parameters.push_back(ui->comboBox_2_2->currentIndex()?1:58130000);
        parameters.push_back(ui->lineEdit_2_8->text().toDouble()*(ui->comboBox2_8->currentIndex()?1:1e-3));
        parameters.push_back(ui->lineEdit_2_9->text().toDouble()*(ui->comboBox2_9->currentIndex()?1:1e9));
        parameters.push_back(ui->lineEdit_2_10->text().toDouble()*(ui->comboBox2_10->currentIndex()?1:1e9));


        for(auto x : parameters)
        {
            qDebug()<<x;
        }
        break;
    default:
        break;
    }
    return parameters;
}

QCheckBox *contentWidget::getFixtureCheckBox()
{
    return ui->checkBox;
}

QLineEdit *contentWidget::getLineEditPath()
{
    return ui->lineEdit_path;
}

int contentWidget::getHighSpeedType()
{
    return ui->comboBox_RandC->currentIndex();
}

void contentWidget::setProject(int i)
{
    switch (i) {
    case 0:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Front);
        occWidget->getView()->Update();
        break;
    case 1:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Left);
        occWidget->getView()->Update();
        break;
    case 2:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Right);
        occWidget->getView()->Update();
        break;
    case 3:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Top);
        occWidget->getView()->Update();
        break;
    case 4:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Bottom);
        occWidget->getView()->Update();
        break;
    case 5:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Back);
        occWidget->getView()->Update();
        break;
    case 6:occWidget->getView()->FitAll();
        occWidget->getView()->Update();
        break;
    default:
        break;
    }
}

bool contentWidget::isFitAll(QVector<QLineEdit *>line)
{
    for(auto x :line)
    {
        if(x->text().isNull()||x->text().isEmpty())
        {
            return false;
        }
    }
    return true;
}

TopoDS_Face contentWidget::makeHoleFace(gp_Pnt pos, double bigRadius, double radius)
{
    //制造一个带孔圆面
        gp_Ax2 ax(pos,gp_Dir(0,0,1));//方向默认Z
//        Handle(Geom_Circle) circle=new Geom_Circle(ax,bigRadius);

        BRepBuilderAPI_MakeEdge edgeMaker(gp_Circ(ax,bigRadius));
        BRepBuilderAPI_MakeWire wireMaker(edgeMaker.Edge());
        BRepBuilderAPI_MakeEdge edgeMaker1(gp_Circ(ax,radius));
        BRepBuilderAPI_MakeWire wireMaker1(edgeMaker1.Edge());

        BRepBuilderAPI_MakeFace faceMaker(wireMaker.Wire());
        TopoDS_Wire wire=wireMaker1.Wire();
        wire.Reverse();
        faceMaker.Add(wire);
        return faceMaker.Face();
}

TopoDS_Face contentWidget::makeCircle(gp_Pnt pos, double Radius)
{
    gp_Ax2 ax(pos,gp_Dir(0,0,1));//方向默认Z
//        Handle(Geom_Circle) circle=new Geom_Circle(ax,bigRadius);

    BRepBuilderAPI_MakeEdge edgeMaker(gp_Circ(ax,Radius));
    BRepBuilderAPI_MakeWire wireMaker(edgeMaker.Edge());
    BRepBuilderAPI_MakeFace faceMaker(wireMaker.Wire());
    return faceMaker.Face();
}

void contentWidget::display(TopoDS_Shape shape, Quantity_NameOfColor colorName)
{
    Handle(AIS_Shape)shape1=new AIS_Shape(shape);
    shape1->SetColor(colorName);
    occWidget->getContext()->Display(shape1,false);
}

TopoDS_Wire contentWidget::makeOuter(gp_Pnt right, gp_Pnt ground, double rightRadius, double groundRadius)
{
   qDebug()<<rightRadius;
    TopoDS_Wire wire;
    double distance=right.Distance(ground);
    //    groundRadius=distance-rightRadius;
    double cosTheta=(rightRadius-groundRadius)/distance;
    double sinTheta=sqrt(1-pow(cosTheta,2));
    double sinAlpha=-right.X()/distance;
    double cosAlpha=sqrt(1-pow(sinAlpha,2));
    qDebug()<<"abs(ground.Y())+groundRadius="<<abs(ground.Y())+groundRadius;
    qDebug()<<"rightRadius="<<rightRadius;

    if(abs(ground.Y())+groundRadius-rightRadius<0.001)
    {

        gp_Pnt sp1(right.X()-rightRadius,0,0);
        gp_Pnt sp2(right.X(),-rightRadius,0);
        gp_Pnt sp3(right.X(),rightRadius,0);
        gp_Pnt sp11(-sp1.X(),sp1.Y(),0);
        gp_Pnt sp22(-sp2.X(),sp2.Y(),0);
        gp_Pnt sp33(-sp3.X(),sp3.Y(),0);
        Handle(Geom_TrimmedCurve)Ssegment=GC_MakeSegment(sp2,sp22);
        Handle(Geom_TrimmedCurve)Ssegment2=GC_MakeSegment(sp3,sp33);
        Handle(Geom_TrimmedCurve)SarcOfCircle=GC_MakeArcOfCircle(sp2,sp1,sp3);
        Handle(Geom_TrimmedCurve)SarcOfCircle2=GC_MakeArcOfCircle(sp22,sp11,sp33);
        TopoDS_Edge Sedge1=BRepBuilderAPI_MakeEdge(Ssegment);
        TopoDS_Edge Sedge2=BRepBuilderAPI_MakeEdge(Ssegment2);
        TopoDS_Edge Sedge3=BRepBuilderAPI_MakeEdge(SarcOfCircle);
        TopoDS_Edge Sedge4=BRepBuilderAPI_MakeEdge(SarcOfCircle2);
        wire=BRepBuilderAPI_MakeWire(Sedge1,Sedge3,Sedge2,Sedge4);
        return wire;
    }


    gp_Pnt p1;p1.SetX(-groundRadius*(sinTheta*cosAlpha-cosTheta*sinAlpha));p1.SetY(ground.Y()-groundRadius*(cosTheta*cosAlpha+sinTheta*sinAlpha));
    gp_Pnt p2;p2.SetX(right.X()-rightRadius*(sinTheta*cosAlpha-cosTheta*sinAlpha));p2.SetY(-rightRadius*(cosTheta*cosAlpha+sinTheta*sinAlpha));
    gp_Pnt p11;p11.SetX(-p1.X());p11.SetY(p1.Y());
    gp_Pnt p22;p22.SetX(-p2.X());p22.SetY(p2.Y());
    gp_Pnt p0;p0.SetX(0);p0.SetY(ground.Y()-groundRadius);
    Handle(Geom_TrimmedCurve)segment=GC_MakeSegment(p1,p2);
    Handle(Geom_TrimmedCurve)segment2=GC_MakeSegment(p11,p22);
    Handle(Geom_TrimmedCurve)arcOfCircle=GC_MakeArcOfCircle(p1,p0,p11);
    TopoDS_Edge edge1=BRepBuilderAPI_MakeEdge(segment);
    TopoDS_Edge edge2=BRepBuilderAPI_MakeEdge(segment2);
    TopoDS_Edge edge3=BRepBuilderAPI_MakeEdge(arcOfCircle);
    TopoDS_Wire wire1=BRepBuilderAPI_MakeWire(edge1,edge3,edge2);

    gp_Pnt leftp1;leftp1.SetX(right.X()-rightRadius);leftp1.SetY(0);
    gp_Pnt leftp2;leftp2.SetX(right.X());leftp2.SetY(rightRadius+right.Y());
    gp_Pnt rightp1;rightp1.SetX(-leftp1.X());rightp1.SetY(leftp1.Y());
    gp_Pnt rightp2;rightp2.SetX(-leftp2.X());rightp2.SetY(leftp2.Y());
    Handle(Geom_TrimmedCurve)edgeLeft1=GC_MakeArcOfCircle(p2,leftp1,leftp2);
    Handle(Geom_TrimmedCurve)edgeRight1=GC_MakeArcOfCircle(p22,rightp1,rightp2);
    Handle(Geom_TrimmedCurve)edgetMiddle=GC_MakeSegment(leftp2,rightp2);
    TopoDS_Edge edgeLeft=BRepBuilderAPI_MakeEdge(edgeLeft1);
    TopoDS_Edge edgeRight=BRepBuilderAPI_MakeEdge(edgeRight1);
    TopoDS_Edge edgeMid=BRepBuilderAPI_MakeEdge(edgetMiddle);
    TopoDS_Wire wire2=BRepBuilderAPI_MakeWire(edgeLeft,edgeMid,edgeRight);
    BRepLib_MakeWire wireMaker;
    wireMaker.Add(wire1);
    wireMaker.Add(wire2);
    wire=wireMaker.Wire();
    return wire;
}

TopoDS_Face contentWidget::makeOuterMain(gp_Pnt right, gp_Pnt left, double rightRadius, double leftRadius, double epsi)
{
    TopoDS_Wire outer1=makeOuter(right,left,rightRadius,leftRadius);
    TopoDS_Wire outer2=makeOuter(right,left,rightRadius+epsi/2,leftRadius+epsi/2);
    BRepBuilderAPI_MakeFace faceMaker(outer2);
    outer1.Reverse();
    faceMaker.Add(outer1);
    return faceMaker.Face();
}

void contentWidget::createHighSpeedCable(double r1, double d, double r2, double h, double l)
{
    if(r1>=r2||d<2*r2||r1==0.0||r2==0.0)
    {
        return;
    }
    occWidget->clearAll();

    double epis=0.001;
    gp_Pnt center1(-d/2,0,0);

    gp_Pnt center2(d/2,0,0);
    gp_Pnt center3;
    if(r2+r1>d/2)
    {
        center3=gp_Pnt(0,-sqrt((pow(r2+r1,2))-(pow(d/2,2))),0);
        if(abs(center3.Y())+r1<r2)
        {
            center3.SetY(r1-r2);
        }
    }
    else{
        center3=gp_Pnt(0,r1-r2,0);
    }


    TopoDS_Face cableDef1=makeHoleFace(center1,r2-epis,r1);
    TopoDS_Face cableDef2=makeHoleFace(center2,r2-epis,r1);

    TopoDS_Face cableLeft=makeCircle(center1,r1-epis);
    TopoDS_Face cableRight=makeCircle(center2,r1-epis);

    TopoDS_Face cableGround=makeCircle(center3,r1);

    TopoDS_Face outer=makeOuterMain(center1,center3,r2,r1,h);



    gp_Vec aPrimVec(0,0,l*0.05);
    TopoDS_Shape cable1=BRepPrimAPI_MakePrism(cableDef1,aPrimVec,false,false);
    TopoDS_Shape cable2=BRepPrimAPI_MakePrism(cableDef2,aPrimVec,false,false);
    TopoDS_Shape cable3=BRepPrimAPI_MakePrism(cableLeft,aPrimVec,false,false);
    TopoDS_Shape cable4=BRepPrimAPI_MakePrism(cableRight,aPrimVec,false,false);
    TopoDS_Shape cable5=BRepPrimAPI_MakePrism(cableGround,aPrimVec,false,false);
    TopoDS_Shape outerShape=BRepPrimAPI_MakePrism(outer,aPrimVec,false,false);
    display(cable1,Quantity_NOC_CYAN);
    display(cable2,Quantity_NOC_CYAN);
    display(cable3,Quantity_NOC_RED);
    display(cable4,Quantity_NOC_RED);
    display(cable5,Quantity_NOC_RED);
    display(outerShape,Quantity_NOC_GOLD);
    occWidget->getView()->FitAll();
}

Handle(V3d_View)contentWidget::getView()
{
    return occWidget->getView();
}

Handle(V3d_Viewer)contentWidget::getViewer()
{
    return  occWidget->getViewer();
}
