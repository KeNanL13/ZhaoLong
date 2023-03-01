#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <occview.h>
#include <QCheckBox>
#include <QLineEdit>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>


namespace Ui {
class contentWidget;
}

class contentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit contentWidget(QWidget *parent = nullptr);
    ~contentWidget();
    Handle(V3d_View)getView();
    Handle(V3d_Viewer)getViewer();
    void changeCablePage(int index);
    QVector<double> getInputParameters(int index);
    QCheckBox * getFixtureCheckBox();
    QLineEdit * getLineEditPath();
    int getHighSpeedType();

    void setProject(int i);

private:
    Ui::contentWidget *ui;
    OccView * occWidget;
    QVector<QLineEdit*>currentShapeLine;
    bool isFitAll(QVector<QLineEdit*>);
    //建模高速线
    TopoDS_Face makeHoleFace(gp_Pnt pos,double bigRadius,double radius);
    TopoDS_Face makeCircle(gp_Pnt pos, double Radius);
    void display(TopoDS_Shape shape,Quantity_NameOfColor colorName);
    TopoDS_Wire makeOuter(gp_Pnt right,gp_Pnt ground,double rightRadius,double groundRadius);
    TopoDS_Face makeOuterMain(gp_Pnt right,gp_Pnt ground,double rightRadius,double leftRadius,double epsi);
    void createHighSpeedCable(double r1,double d,double r2,double h,double l);

};

#endif // CONTENTWIDGET_H
