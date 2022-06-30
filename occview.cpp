#include "occview.h"
#include "ui_occview.h"

OccView::OccView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OccView)
{
    ui->setupUi(this);
    if(m_context.IsNull())
    {
    Handle(Aspect_DisplayConnection) m_displayConnection=new Aspect_DisplayConnection();
    if(m_graphicDriver.IsNull())
    {
        m_graphicDriver=new OpenGl_GraphicDriver(m_displayConnection);
    }
    WId window_handle=winId();
    Handle(WNT_Window) wind= new WNT_Window((Aspect_Handle)window_handle);

    m_viewer=new V3d_Viewer(m_graphicDriver);
    m_view=m_viewer->CreateView();
    m_view->SetWindow(wind);

    if(!wind->IsMapped())
    {
        wind->Map();
    }

    m_context=new AIS_InteractiveContext(m_viewer);
    //设置光照
    Handle(V3d_DirectionalLight) LightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color (Quantity_NOC_GRAY97), 1);
    Handle(V3d_AmbientLight)     LightAmb = new V3d_AmbientLight();
    LightDir->SetDirection(1.0, -2.0, -10.0);
    m_viewer->AddLight(LightDir);
    m_viewer->AddLight(LightAmb);
    m_viewer->SetLightOn(LightDir);
    m_viewer->SetLightOn(LightAmb);
     //全局设置
    const Handle(Prs3d_Drawer)& contextDrawer = m_context->DefaultDrawer();
    if ( !contextDrawer.IsNull() )
    {
        const Handle(Prs3d_ShadingAspect)&        SA = contextDrawer->ShadingAspect();
        const Handle(Graphic3d_AspectFillArea3d)& FA = SA->Aspect();
//            contextDrawer->SetFaceBoundaryDraw(true); // Draw edges.
        FA->SetEdgeOff();

        // Fix for inifinite lines has been reduced to 1000 from its default value 500000.
        contextDrawer->SetMaximalParameterValue(1000);
    }
//        m_viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);
    m_view->SetBackgroundColor(Quantity_NOC_GRAY);
    m_view->MustBeResized();
//    m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,Quantity_NOC_GOLD,0.08,V3d_ZBUFFER);
    m_view->SetShadingModel(V3d_PHONG);

    // Configure rendering parameters
    Graphic3d_RenderingParams& RenderParams = m_view->ChangeRenderingParams();
    RenderParams.IsAntialiasingEnabled = true;
    RenderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
    RenderParams.IsShadowEnabled = true;
    RenderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_NONE;

    m_context->SetDisplayMode(AIS_Shaded,Standard_True);
    // Adjust selection style.
//        AdjustSelectionStyle(m_context);


    // Activate selection modes.
    m_context->Activate(4, true); // faces
   m_context->Activate(2, true); // edges

   // ViewCube 设置
  Handle(AIS_ViewCube)axisCube=new AIS_ViewCube();
   Handle(Graphic3d_TransformPers) gtrans=new Graphic3d_TransformPers(
       Graphic3d_TMF_TriedronPers,
       Aspect_TOTP_RIGHT_UPPER,
       Graphic3d_Vec2i(85, 85));
   axisCube->SetTransformPersistence(gtrans);
   axisCube->SetAutoHilight(true);
   axisCube->SetFixedAnimationLoop (false);
   axisCube->SetAutoStartAnimation(true);
   m_context->Display(axisCube,Standard_True);
}
setAttribute(Qt::WA_PaintOnScreen);
setAttribute(Qt::WA_NoSystemBackground);
setBackgroundRole(QPalette::NoRole);
setFocusPolicy(Qt::StrongFocus);

setMouseTracking(true);
}

OccView::~OccView()
{
    delete ui;
}

QPaintEngine *OccView::paintEngine() const
{
    return 0;
}

Handle(AIS_InteractiveContext) OccView::getContext()
{
    return m_context;
}

Handle(V3d_View) OccView::getView()
{
    return m_view;
}

void OccView::paintEvent(QPaintEvent *event)
{
    m_view->Redraw();
}

void OccView::resizeEvent(QResizeEvent *event)
{
    if(!m_view.IsNull())
    {
        m_view->MustBeResized();
    }
}

void OccView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_x=event->pos().x();
        m_y=event->pos().y();
        m_Current_Mode=CurAction3d_DynamicPanning;
    }
    else if(event->button()==Qt::MidButton)
    {

        m_Current_Mode = CurAction3d_DynamicRotation;
        m_view->StartRotation(event->pos().x(),event->pos().y());

    }
}

void OccView::mouseReleaseEvent(QMouseEvent *event)
{
    m_Current_Mode=CurrentAction_Nothing;
}

void OccView::mouseMoveEvent(QMouseEvent *event)
{
    m_context->MoveTo(event->pos().x(),event->pos().y(),m_view,true);
      if(m_Current_Mode==CurAction3d_DynamicPanning)
      {
          m_view->Pan(event->pos().x()-m_x,-event->pos().y()+m_y);
          m_x=event->pos().x();
          m_y=event->pos().y();
      }
      else if(m_Current_Mode==CurAction3d_DynamicRotation)
      {
          m_view->Rotation(event->pos().x(),event->pos().y());
      }

}

void OccView::wheelEvent(QWheelEvent *event)
{
    Standard_Integer aFactor = 16;

    Standard_Integer aX = event->pos().x();
    Standard_Integer aY = event->pos().y();

    if (event->delta() > 0)
    {
        aX += aFactor;
        aY += aFactor;
    }
    else
    {
        aX -= aFactor;
        aY -= aFactor;
    }

    m_view->Zoom(event->pos().x(), event->pos().y(), aX, aY);
}
