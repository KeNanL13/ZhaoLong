#include "settingwidget_base.h"

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <gp_Circ.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GC_MakeSegment.hxx>
#include <GC_MakeArcOfCircle.hxx>

#include <AIS_Shape.hxx>

SettingWidget_Base::SettingWidget_Base(QWidget *parent) : MyShadowWidget(parent)
{

}

TopoDS_Face SettingWidget_Base::makeHoleFace(gp_Pnt pos, double bigRadius, double radius)
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

TopoDS_Face SettingWidget_Base::makeCircle(gp_Pnt pos, double Radius)
{
    gp_Ax2 ax(pos,gp_Dir(0,0,1));//方向默认Z
//        Handle(Geom_Circle) circle=new Geom_Circle(ax,bigRadius);

    BRepBuilderAPI_MakeEdge edgeMaker(gp_Circ(ax,Radius));
    BRepBuilderAPI_MakeWire wireMaker(edgeMaker.Edge());
    BRepBuilderAPI_MakeFace faceMaker(wireMaker.Wire());
    return faceMaker.Face();
}

TopoDS_Wire SettingWidget_Base::makeOuter(gp_Pnt right, gp_Pnt ground, double rightRadius, double groundRadius)
{

     TopoDS_Wire wire;
     double distance=right.Distance(ground);
     //    groundRadius=distance-rightRadius;
     double cosTheta=(rightRadius-groundRadius)/distance;
     double sinTheta=sqrt(1-pow(cosTheta,2));
     double sinAlpha=-right.X()/distance;
     double cosAlpha=sqrt(1-pow(sinAlpha,2));


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

TopoDS_Face SettingWidget_Base::makeOuterMain(gp_Pnt right, gp_Pnt left, double rightRadius, double leftRadius, double epsi)
{
    TopoDS_Wire outer1=makeOuter(right,left,rightRadius,leftRadius);
    TopoDS_Wire outer2=makeOuter(right,left,rightRadius+epsi/2,leftRadius+epsi/2);
    BRepBuilderAPI_MakeFace faceMaker(outer2);
    outer1.Reverse();
    faceMaker.Add(outer1);
    return faceMaker.Face();
}
