#include "materialcomponent.h"
#include <QBoxLayout>
#include <QString>
#include <QLabel>
#include <QDebug>

MaterialComponent::MaterialComponent(QWidget *parent) : QWidget(parent)
{
   QVBoxLayout * layout=new QVBoxLayout;
   layout->setAlignment(Qt::AlignmentFlag::AlignRight );
   layout->setSpacing(8);
   this->setLayout(layout);
   resize(600,800);
   //CheckBox
   QtMaterialCheckBox * checkbox=new QtMaterialCheckBox();
   checkbox->setText("checkbox");
   layout->addWidget(checkbox);


   //Drawer
   QtMaterialFlatButton * drawerButton=new QtMaterialFlatButton("drawer open");
   layout->addWidget(drawerButton);


   QtMaterialDrawer * drawer=new QtMaterialDrawer();
   drawer->setParent(this);
   drawer->setOverlayMode(true);
   drawer->setClickOutsideToClose(true);

   connect(drawerButton,&QtMaterialFlatButton::clicked,[=](){
       drawer->openDrawer();
   });
   QVBoxLayout * drawerLayout=new QVBoxLayout();
   for(int i=0;i<10;i++)
   {
       LineEditWidget * lineEdit=new LineEditWidget();
       QString labelText=QString("label %1").arg(i);
       lineEdit->getMainLayout()->insertWidget(0,new QLabel(labelText));
       lineEdit->getMainLayout()->insertSpacing(1,8);
       drawerLayout->addWidget(lineEdit);
   }
   drawerLayout->addStretch(3);
   drawer->setDrawerLayout(drawerLayout);

   //Dialog
   //Loading Dialog
   QtMaterialFlatButton * LoadingButton=new QtMaterialFlatButton("Loading Dialog");//Trigger

   QtMaterialDialog * loadingDialog=new QtMaterialDialog(this);
   QVBoxLayout * loadingDialogLayout=new QVBoxLayout();
   QtMaterialCircularProgress *progress=new QtMaterialCircularProgress();
   QLabel * label=new QLabel("tips:Waiting for the result.");

   QWidget * buttonWidget =new QWidget;
   QtMaterialFlatButton * btn1=new QtMaterialFlatButton("确定");
   QtMaterialFlatButton * btn2=new QtMaterialFlatButton("取消");
   QHBoxLayout * buttonWidgetLayout=new QHBoxLayout();
   buttonWidgetLayout->addWidget(btn1);
   buttonWidgetLayout->addWidget(btn2);
   buttonWidgetLayout->setSpacing(50);
   buttonWidgetLayout->setAlignment(Qt::AlignCenter);
   buttonWidget->setLayout(buttonWidgetLayout);


   loadingDialogLayout->addWidget(progress);
   loadingDialogLayout->addWidget(label);
   loadingDialogLayout->addWidget(buttonWidget);
   label->setAlignment(Qt::AlignCenter);
   loadingDialogLayout->addSpacing(8);
   loadingDialogLayout->setAlignment(Qt::AlignCenter);

   loadingDialog->setWindowLayout(loadingDialogLayout);
   layout->addWidget(LoadingButton);
   connect(LoadingButton,&QtMaterialFlatButton::clicked,[=](){
       qDebug()<<"trigger";
       loadingDialog->showDialog();
   });
   connect(btn1,&QtMaterialFlatButton::clicked,[=](){
      loadingDialog->hideDialog();
   });
   connect(btn2,&QtMaterialFlatButton::clicked,[=](){
      loadingDialog->hideDialog();
   });
//   btn1->setBaseOpacity(0.6);
   btn1->setBackgroundColor(QColor(16,174,194));
   btn1->setCornerRadius(8);
   btn1->setOverlayColor(QColor(16,174,194));
   btn1->setForegroundColor(QColor(16,174,194));

   btn2->setBackgroundColor(QColor(194,31,48));
   btn2->setCornerRadius(8);
   btn2->setOverlayColor(QColor(194,31,48));
   btn2->setForegroundColor(QColor(194,31,48));


   //Snack
   PushButton * snackButton=new PushButton(nullptr);
   QLabel * snackLabel=new QLabel("Snack");
   snackLabel->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
   QFont iconButtonFont("Font Awesome 6 Free Regular",12);
   iconButtonFont.setStyleStrategy(QFont::PreferAntialias);
   snackLabel->setFont(iconButtonFont);
//   snackLabel->setAlignment(Qt::AlignCenter);
   snackButton->setChildWidget(snackLabel);


   snackButton->setMargin(20,18,16,18);
   QtMaterialSnackbar * snackBar=new QtMaterialSnackbar(this);
//   snackBar->setBackgroundOpacity(0.618);
//   snackBar->setClickToDismissMode(true);



   layout->addWidget(snackButton);
   connect(snackButton,&PushButton::onClick,[=](){
        snackBar->addMessage("错误参数!");
   });


   layout->addStretch(3);
}
