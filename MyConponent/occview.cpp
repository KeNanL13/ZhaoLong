#include "occview.h"
#include <QSurfaceFormat>
namespace
{
  //! Map Qt buttons bitmask to virtual keys.
  static Aspect_VKeyMouse qtMouseButtons2VKeys(Qt::MouseButtons theButtons)
  {
    Aspect_VKeyMouse aButtons = Aspect_VKeyMouse_NONE;
    if ((theButtons & Qt::LeftButton) != 0)
    {
      aButtons |= Aspect_VKeyMouse_LeftButton;
    }
    if ((theButtons & Qt::MiddleButton) != 0)
    {
      aButtons |= Aspect_VKeyMouse_MiddleButton;
    }
    if ((theButtons & Qt::RightButton) != 0)
    {
      aButtons |= Aspect_VKeyMouse_RightButton;
    }
    return aButtons;
  }

  //! Map Qt mouse modifiers bitmask to virtual keys.
  static Aspect_VKeyFlags qtMouseModifiers2VKeys(Qt::KeyboardModifiers theModifiers)
  {
    Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
    if ((theModifiers & Qt::ShiftModifier) != 0)
    {
      aFlags |= Aspect_VKeyFlags_SHIFT;
    }
    if ((theModifiers & Qt::ControlModifier) != 0)
    {
      aFlags |= Aspect_VKeyFlags_CTRL;
    }
    if ((theModifiers & Qt::AltModifier) != 0)
    {
      aFlags |= Aspect_VKeyFlags_ALT;
    }
    return aFlags;
  }

  static QCursor* defCursor = NULL;
  static QCursor* handCursor = NULL;
  static QCursor* panCursor = NULL;
  static QCursor* globPanCursor = NULL;
  static QCursor* zoomCursor = NULL;
  static QCursor* rotCursor = NULL;

}
OccView::OccView(QWidget *parent) :
    QWidget(parent)

{

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
            contextDrawer->SetMaximalParameterValue(50000);
        }
//        m_viewer->ActivateGrid(Aspect_GT_Rectangular,Aspect_GDM_Lines);
        m_view->SetBackgroundColor(Quantity_NOC_GRAY);
        m_view->MustBeResized();
//        m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,Quantity_NOC_GOLD,0.08,V3d_ZBUFFER);
        m_view->SetShadingModel(V3d_PHONG);

        // Configure rendering parameters
        Graphic3d_RenderingParams& RenderParams = m_view->ChangeRenderingParams();
        //Set RayTracing
        RenderParams.Method=Graphic3d_RM_RAYTRACING;
        RenderParams.RaytracingDepth=3;
        RenderParams.IsReflectionEnabled=true;
        RenderParams.IsTransparentShadowEnabled=true;
        //Standard setting
        RenderParams.IsAntialiasingEnabled = true;
        RenderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
        RenderParams.IsShadowEnabled = true;
        RenderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_NONE;

        m_context->SetDisplayMode(AIS_Shaded,Standard_True);
//        m_context->SetDisplayMode(AIS_WireFrame,Standard_True);
        // Adjust selection style.
//        AdjustSelectionStyle(m_context);


        // Activate selection modes.
        m_context->Activate(4, true); // faces
       m_context->Activate(2, true); // edges

       // ViewCube 设置
      axisCube=new AIS_ViewCube();
       Handle(Graphic3d_TransformPers) gtrans=new Graphic3d_TransformPers(
           Graphic3d_TMF_TriedronPers,
           Aspect_TOTP_RIGHT_UPPER,
           Graphic3d_Vec2i(65, 65));
       axisCube->SetTransformPersistence(gtrans);
       axisCube->SetAutoHilight(true);
       axisCube->SetFixedAnimationLoop (true);
       axisCube->SetAutoStartAnimation(true);
       axisCube->SetSize(50);

//       axisCube->SetSize(60,true);
//       axisCube->SetTextColor(Quantity_NOC_RED);

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

}

void OccView::clearAll()
{
    m_context->RemoveAll(true);
    m_context->Display(axisCube,true);
}

QPaintEngine *OccView::paintEngine() const
{
    return 0;
}

 Handle(V3d_Viewer)OccView::getViewer()
{
    return  m_viewer;
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
//    m_view->Redraw();
//   m_evtmgr->ProcessExpose();
    m_view->InvalidateImmediate();
    FlushViewEvents(m_context,m_view,true);
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
//    if(event->button()==Qt::LeftButton)
//    {
//        m_x=event->pos().x();
//        m_y=event->pos().y();
//        m_Current_Mode=CurAction3d_DynamicPanning;
//    }
//    else if(event->button()==Qt::MidButton)
//    {

//        m_Current_Mode = CurAction3d_DynamicRotation;
//        m_view->StartRotation(event->pos().x(),event->pos().y());

//    }
    Qt::MouseButtons aMouseButtons = event->buttons();
      const Graphic3d_Vec2i aPnt(event->pos().x(), event->pos().y());
      const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(event->modifiers());
      if (!m_view.IsNull()
        && UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false))
      {
//          UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false);
        update();
      }
      myClickPos = aPnt;
}

void OccView::mouseReleaseEvent(QMouseEvent *event)
{
//   m_Current_Mode=CurrentAction_Nothing;
    Qt::MouseButtons aMouseButtons = event->buttons();
      const Graphic3d_Vec2i aPnt(event->pos().x(), event->pos().y());
      const Aspect_VKeyFlags aFlags = qtMouseModifiers2VKeys(event->modifiers());
      if (!m_view.IsNull()
        && UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false))
      {
//          UpdateMouseButtons(aPnt, qtMouseButtons2VKeys(aMouseButtons), aFlags, false);
        update();
      }

//      if (myCurrentMode == CurrentAction3d_GlobalPanning)
//      {
//        m_view->Place(aPnt.x(), aPnt.y(), myCurZoom);
//      }
//      if (myCurrentMode != CurrentAction3d_Nothing)
//      {
//        setCurrentAction(CurrentAction3d_Nothing);
//      }
}

void OccView::mouseMoveEvent(QMouseEvent *e)
{
//    m_context->MoveTo(event->pos().x(),event->pos().y(),m_view,true);
//      if(m_Current_Mode==CurAction3d_DynamicPanning)
//      {
//          m_view->Pan(event->pos().x()-m_x,-event->pos().y()+m_y);
//          m_x=event->pos().x();
//          m_y=event->pos().y();
//      }
//      else if(m_Current_Mode==CurAction3d_DynamicRotation)
//      {
//          m_view->Rotation(event->pos().x(),event->pos().y());
//      }
    Qt::MouseButtons aMouseButtons = e->buttons();
     const Graphic3d_Vec2i aNewPos(e->pos().x(), e->pos().y());
     if (!m_view.IsNull()
       && UpdateMousePosition(aNewPos, qtMouseButtons2VKeys(aMouseButtons), qtMouseModifiers2VKeys(e->modifiers()), false))
     {
//         UpdateMousePosition(aNewPos, qtMouseButtons2VKeys(aMouseButtons), qtMouseModifiers2VKeys(e->modifiers()), false);
       update();

     }
}

void OccView::wheelEvent(QWheelEvent *e)
{
//    Standard_Integer aFactor = 16;

//    Standard_Integer aX = event->pos().x();
//    Standard_Integer aY = event->pos().y();

//    if (event->delta() > 0)
//    {
//        aX += aFactor;
//        aY += aFactor;
//    }
//    else
//    {
//        aX -= aFactor;
//        aY -= aFactor;
//    }

//    m_view->Zoom(event->pos().x(), event->pos().y(), aX, aY);
    const Graphic3d_Vec2i aPos(e->pos().x(),e->pos().y());
    if(!m_view.IsNull()
            &&UpdateZoom(Aspect_ScrollDelta(aPos,e->delta()/8)))
    {
        update();
    }
}

//void OccView::AdjustSelectionStyle(const Handle(AIS_InteractiveContext)& context)
//{
//    Handle(Prs3d_Drawer) selDrawer = new Prs3d_Drawer;
//        //
//        selDrawer->SetLink                ( context->DefaultDrawer() );
//        selDrawer->SetFaceBoundaryDraw    ( true );
//        selDrawer->SetDisplayMode         ( 1 ); // Shaded
//        selDrawer->SetTransparency        ( 0.5f );
//        selDrawer->SetZLayer              ( Graphic3d_ZLayerId_Topmost );
//        selDrawer->SetColor               ( Quantity_NOC_GOLD );
//        selDrawer->SetBasicFillAreaAspect ( new Graphic3d_AspectFillArea3d() );

//        // Adjust fill area aspect.
//        const Handle(Graphic3d_AspectFillArea3d)&
//          fillArea = selDrawer->BasicFillAreaAspect();
//        //
//        fillArea->SetInteriorColor     (Quantity_NOC_RED);
//        fillArea->SetBackInteriorColor (Quantity_NOC_RED);
//        //
//        fillArea->ChangeFrontMaterial() .SetMaterialName(Graphic3d_NOM_NEON_GNC);
//        fillArea->ChangeFrontMaterial() .SetTransparency(0.4f);
//        fillArea->ChangeBackMaterial()  .SetMaterialName(Graphic3d_NOM_NEON_GNC);
//        fillArea->ChangeBackMaterial()  .SetTransparency(0.4f);

//        selDrawer->UnFreeBoundaryAspect()->SetWidth(1.0);

//        // Update AIS context.
//        context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalSelected, selDrawer);
//}
