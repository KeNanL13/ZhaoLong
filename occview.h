#ifndef OCCVIEW_H
#define OCCVIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <WNT_Window.hxx>
#include <Quantity_NameOfColor.hxx>
#include <V3d_AmbientLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <AIS_ViewController.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_AnimationCamera.hxx>
#include <QDebug>

namespace Ui {
class OccView;
}

class OccView : public QWidget
{
    Q_OBJECT

public:
    explicit OccView(QWidget *parent = nullptr);
    ~OccView();

private:
    Ui::OccView *ui;
    Handle(AIS_InteractiveContext) m_context;
    Handle(V3d_Viewer) m_viewer;
    Handle(V3d_View) m_view;
    Handle(Graphic3d_GraphicDriver) m_graphicDriver;

    // QPaintDevice interface
public:
    QPaintEngine *paintEngine() const;
    Handle(V3d_View) getView();
    Handle(AIS_InteractiveContext) getContext();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

protected:
    enum CurrentAction
    {
        CurrentAction_Nothing,
        CurAction3d_DynamicZooming,
        CurAction3d_WindowZooming,
        CurAction3d_DynamicPanning,
        CurAction3d_GlobalPanning,
        CurAction3d_DynamicRotation
    };
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    Standard_Integer m_x;
    Standard_Integer m_y;
    CurrentAction m_Current_Mode;
};

#endif // OCCVIEW_H
