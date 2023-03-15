#include "settingwidget_highspeed.h"
#include <QScrollArea>
#include <MyComponents/customWidgets.h>

#include <infotext.h>
#include <qtmaterialscrollbar.h>
#include <qtmaterialflatbutton.h>
#include <MyComponents/pushbutton.h>
#include <qtmaterialcheckbox.h>
#include <BRepPrimAPI_MakePrism.hxx>




SettingWidget_HighSpeed::SettingWidget_HighSpeed(QWidget *parent) : SettingWidget_Base (parent)
{
    //初始化设置
    m_type=HighSpeedCable;
    textLineCount=1;
    numberLineCount=10;
    //配置主界面内容
    QVBoxLayout * mainLayout=new QVBoxLayout;
    QWidget * scrollContentWidget=new QWidget();

    scrollContentWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);




    //Add information group
    singleSelectGroup * group1=new singleSelectGroup("Information",scrollContentWidget);
    LineEditWidget * textCableType=getLineEditWidget("线缆类型");
    textCableType->setText("高速线");
    textCableType->setEnable(false);
    LineEditWidget * textName=getLineEditWidget("实例名称");
    textInputLines.append(textName);
    textLineCount++;
    textName->setPlaceHolderText("输入名称");

    mainLayout->addWidget(group1);
    mainLayout->addWidget(textCableType);
    mainLayout->addWidget(textName);

    PushButton * defaultButton=new PushButton(nullptr,this);
    QLabel * defaultLabel=new QLabel("设置默认参数");

    defaultLabel->setFont(font);
    defaultButton->setMaximumHeight(defaultLabel->height()+20);
    defaultButton->setChildWidget(defaultLabel);
    defaultButton->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
    defaultButton->setBackgroundColor(QColor(0,0,0,20));
    mainLayout->addWidget(defaultButton);
    connect(defaultButton,&PushButton::onClick,this,[=](){
       for(int i=0;i<10;i++)
       {
           cableInputLines[i]->setText(InfoText::getHighSpeedDefaultParameter(mainRange[i]));
       }
    });

    //Add cable geometry parameter group
    singleSelectGroup * group2=new singleSelectGroup("Geometry",scrollContentWidget);
    mainLayout->addWidget(group2);
    QVector<double> metricsValue;
    metricsValue<<1e-3;
    for(unsigned int i=0;i<6;i++)
    {
        LineEditWidget * line=getLineEditWidget(InfoText::getHighSpeedParameterName(mainRange[i]),"mm");

        mapOfMetricsValue.insert(line,metricsValue);

        cableInputLines.push_back(line);

        mainLayout->addWidget(line);

    }
    metricsValue.clear();

    //Add cable material parameter group
    singleSelectGroup * group3=new singleSelectGroup("Material",scrollContentWidget);
    mainLayout->addWidget(group3);
    for(unsigned int i=3;i<5;i++)
    {
        LineEditWidget * line=getLineEditWidget(InfoText::getHighSpeedParameterName(i));
        cableInputLines.push_back(line);

        mainLayout->addWidget(line);
    }
    QWidget * shieldWidget=getSelectionLine("屏蔽层电导率",QStringList("铝(38160000)"),QStringList("S/m"));

    //bad
    metricsValue<<38160000;
    mapOfMetricsValue.insert(comboboxList[0],metricsValue);
    metricsValue.clear();
    QWidget * cableWidget=getSelectionLine("线缆电导率",QStringList("铜(58130000)"),QStringList("S/m"));

    metricsValue<<58130000;
    mapOfMetricsValue.insert(comboboxList[1],metricsValue);
    metricsValue.clear();

    mainLayout->addWidget(shieldWidget);
    mainLayout->addWidget(cableWidget);
    //Add simulation setting group
    singleSelectGroup * group4=new singleSelectGroup("Simulation",scrollContentWidget);
    mainLayout->addWidget(group4);
    metricsValue<<1e9;
    for(unsigned int i=8;i<10;i++)
    {
        LineEditWidget * line=getLineEditWidget(InfoText::getHighSpeedParameterName(i),"GHz");

        mapOfMetricsValue.insert(line,metricsValue);
        cableInputLines.push_back(line);
        mainLayout->addWidget(line);
    }
    metricsValue.clear();

    QList<QString> disPara;
    disPara<<"默认圆形"<<"HFSS结果"<<"非平衡情况"<<"26AWG"<<"26AWG 5%偏移"<<"26 AWG 10%偏移";
    QWidget * distributeWidget=getSelectionLine("线缆分布参数:",disPara);
    mainLayout->addWidget(distributeWidget);

    QWidget * checkWidget=getCheckWidget("夹具");
    mainLayout->addWidget(checkWidget);

    mainLayout->setSpacing(10);

    QScrollArea * scrollArea=new QScrollArea();
    QtMaterialScrollBar * Hor_Scorll=new QtMaterialScrollBar();
    QtMaterialScrollBar * Ver_Scorll=new QtMaterialScrollBar();
    Hor_Scorll->setBackgroundColor(QColor(211,211,211));
    Hor_Scorll->setCanvasColor(QColor(255,255,255));
    Hor_Scorll->setHideOnMouseOut(true);
    Ver_Scorll->setHideOnMouseOut(false);

    Ver_Scorll->setBackgroundColor(QColor(255,255,255));
    Hor_Scorll->setSliderPosition(Qt::Horizontal);

    scrollContentWidget->setObjectName("scrollContentWidget");
    scrollContentWidget->setStyleSheet("QWidget#scrollContentWidget{background-color : #ffffff;}");

    scrollContentWidget->setLayout(mainLayout);
    //！！！Note : Must add all the widget before [scrollarea->setWidget]
    scrollArea->setWidget(scrollContentWidget);

    scrollArea->setVerticalScrollBar(Ver_Scorll);

    scrollArea->setHorizontalScrollBar(Hor_Scorll);

    QVBoxLayout * scrollLayout=new QVBoxLayout;

    scrollLayout->addWidget(scrollArea);

    scrollLayout->setContentsMargins(0,0,0,0);

    scrollArea->setStyleSheet("QScrollArea{background-color:#ffffff;}");
    this->getMainWindow()->setLayout(scrollLayout);


    //设置文件更改发送创建形状信号
    for(int i=0;i<5;i++)
    {

        connect(cableInputLines[i],&LineEditWidget::onTextChanged,this,[=](const QString & ){
            int flag=isShapeInputCompleted();
            if(flag==1)
            {
                emit this->createShape();
            }
            else{
                emit this->clearShape();
            }
        });
    }



//    QHBoxLayout * scrollLayout=new QHBoxLayout();
//    QScrollArea * scrollArea=new QScrollArea(this);
//    QtMaterialScrollBar * barV=new QtMaterialScrollBar;
//    QtMaterialScrollBar * barH=new QtMaterialScrollBar;
//    QWidget * mainWidget=new QWidget;
//    barV->setOrientation(Qt::Vertical);
//    barH->setOrientation(Qt::Horizontal);
//    scrollArea->setHorizontalScrollBar(barH);
//    scrollArea->setVerticalScrollBar(barV);

//    scrollLayout->addWidget(scrollArea);
//    this->getMainWindow()->setLayout(scrollLayout);


//    scrollArea->setWidget(mainWidget);

//    QVBoxLayout * layout_Tool=new QVBoxLayout;
//    layout_Tool->addWidget(new QLabel("test"));
//    mainWidget->setLayout(layout_Tool);


}

LineEditWidget *SettingWidget_HighSpeed::getLineEditWidget(QString label, QString comboboxItem)
{
    LineEditWidget * line=new LineEditWidget;
    QLabel *label1=new QLabel(label+"：");
    QComboBox * combobox=new QComboBox();
    label1->setFont(font);
    combobox->addItem(comboboxItem);
    combobox->setStyleSheet(InfoText::getComboBoxStyleSheet());

    line->getMainLayout()->insertWidget(0,label1);
    line->getMainLayout()->insertSpacing(1,8);
    line->getMainLayout()->insertWidget(3,combobox);

    line->setBackgroundColor(QColor(0,0,0,0));
    line->setHoverColor(QColor(0,0,0,10));
    line->setPressedColor(QColor(0,0,0,20));


    line->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
    mapOfMetricsComboBox.insert(line,combobox);

    return line;
}

LineEditWidget *SettingWidget_HighSpeed::getLineEditWidget(QString label)
{
    LineEditWidget * line=new LineEditWidget;
    QLabel *label1=new QLabel(label+":");

    label1->setFont(font);


    line->getMainLayout()->insertWidget(0,label1);
    line->getMainLayout()->insertSpacing(1,8);


    line->setBackgroundColor(QColor(0,0,0,0));
    line->setHoverColor(QColor(0,0,0,10));
    line->setPressedColor(QColor(0,0,0,20));


    line->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);

    return line;
}

LineEditWidget *SettingWidget_HighSpeed::getLineEditWidget(QString label, QList<QString> comboboxItems)
{
    LineEditWidget * line=new LineEditWidget;
    QLabel *label1=new QLabel(label+":");
    QComboBox * combobox=new QComboBox();
    label1->setFont(font);
    combobox->addItems(comboboxItems);
    combobox->setStyleSheet(InfoText::getComboBoxStyleSheet());

    line->getMainLayout()->insertWidget(0,label1);
    line->getMainLayout()->insertSpacing(1,8);
    line->getMainLayout()->insertWidget(3,combobox);

    line->setBackgroundColor(QColor(0,0,0,0));
    line->setHoverColor(QColor(0,0,0,10));
    line->setPressedColor(QColor(0,0,0,20));


    line->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
    mapOfMetricsComboBox.insert(line,combobox);
    return line;
}

QWidget *SettingWidget_HighSpeed::getSelectionLine(QString label, QList<QString> comboboxItems,QList<QString>comboboxMetrics)
{
    QWidget * widget=new QWidget;
    QVBoxLayout * layout=new QVBoxLayout;
    QHBoxLayout * smallLayout=new QHBoxLayout;
    QWidget * smallWidget=new QWidget;

    smallLayout->setContentsMargins(0,12,0,12);
    smallLayout->setSpacing(8);
    layout->setContentsMargins(12,0,12,0);
    layout->setSpacing(8);
    QLabel * label1=new QLabel(label);
    label1->setAlignment(Qt::AlignLeft);
    label1->setFont(font);
    label1->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
    QComboBox * combobox1=new QComboBox;
    combobox1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    combobox1->setFont(font);
    combobox1->addItems(comboboxItems);
    combobox1->setStyleSheet(InfoText::getComboBoxStyleSheet());

    QComboBox * combobox2=new QComboBox;
    combobox2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);
    combobox2->setFont(font);
    combobox2->addItems(comboboxMetrics);
    combobox2->setStyleSheet(InfoText::getComboBoxStyleSheet());

    layout->addWidget(label1);
    smallLayout->addWidget(combobox1);
    smallLayout->addWidget(combobox2);
    smallWidget->setLayout(smallLayout);
    layout->addWidget(smallWidget);

    widget->setLayout(layout);
    comboboxList.append(combobox1);
    mapOfMetricsComboBox.insert(widget,combobox2);
    return  widget;

}

QWidget *SettingWidget_HighSpeed::getSelectionLine(QString label, QList<QString> comboboxItems)
{
    QWidget * widget=new QWidget();
    QHBoxLayout* layout=new QHBoxLayout;

    layout->setContentsMargins(12,0,12,0);
    layout->setSpacing(8);

    QLabel* label1=new QLabel(label);
    label1->setFont(font);
    QComboBox * combobox=new QComboBox();
    combobox->addItems(comboboxItems);
    combobox->setFont(font);
    combobox->setStyleSheet(InfoText::getComboBoxStyleSheet());

    layout->addWidget(label1);
    layout->addWidget(combobox);
    widget->setLayout(layout);
    comboboxList.append(combobox);

    return widget;
}

QWidget *SettingWidget_HighSpeed::getCheckWidget(QString label)
{
    QWidget * widget=new QWidget();
    QVBoxLayout * mainLayout=new QVBoxLayout;
    QHBoxLayout * layout=new QHBoxLayout;
    QLabel * label1=new QLabel(label);
    label1->setFont(font);
    QtMaterialCheckBox * checkBox=new QtMaterialCheckBox();
    layout->addWidget(label1);
    layout->addStretch(1);
    layout->addWidget(checkBox);
    checkBox->setChecked(true);





    QWidget * smallWidget=new QWidget;

    LineEditWidget * lineEdit=new LineEditWidget;
    lineEdit->close();
    PushButton * button=new PushButton(nullptr,this);
    QLabel * btnName=new QLabel("选择");
    btnName->setFont(font);
    button->setChildWidget(btnName);
    lineEdit->getMainLayout()->insertWidget(1,button);
    lineEdit->getMainLayout()->setContentsMargins(0,0,0,0);
//    lineEdit->setEnable(false);
    connect(button,&PushButton::onClick,this,[=](){
       QString fileName=QFileDialog::getOpenFileName(this,"寻找夹具文件",QApplication::applicationDirPath());
       if(!fileName.isNull() && !fileName.isEmpty())
       {
           lineEdit->setText(fileName);
       }
    });
    connect(checkBox,&QtMaterialCheckBox::toggled,[=](bool checked){
            lineEdit->setVisible(checked);
            if(checked)
            {
                textLineCount++;
                textInputLines.append(lineEdit);
            }
            else{
                textLineCount--;
                textInputLines.removeOne(lineEdit);
            }
//            isFixture=checked;
//            if(checked)
//            {
//                cableInputLines.append(lineEdit);
//            }else{
//                cableInputLines.removeOne(lineEdit);
//            }
//            qDebug()<<cableInputLines.size();

    });
    smallWidget->setLayout(layout);
    mainLayout->addWidget(smallWidget);
    mainLayout->addWidget(lineEdit);
    lineEdit->setAlignment(Qt::AlignLeft);
    lineEdit->setPlaceHolderText("选择夹具文件路径");

    widget->setLayout(mainLayout);
    mainLayout->setContentsMargins(12,0,12,0);
    mainLayout->setSpacing(8);
    layout->setContentsMargins(0,0,0,0);
//    cableInputLines.append(lineEdit);
    textLineCount++;
    textInputLines.append(lineEdit);

    return  widget;


}



bool SettingWidget_HighSpeed::isInputCompleted()
{
    for(auto x : cableInputLines)
    {
        if(x->getText().isNull() || x->getText().isEmpty())
        {
            return  false;
        }
    }


    for(auto x:textInputLines)
    {
        if(x->getText().isNull() || x->getText().isEmpty())
        {
            return false;
        }
    }

    return true;
}

QVector<double> SettingWidget_HighSpeed::getInputNumber()
{
    QVector<double> numberList;

    double temp;


    for(int i=0;i<cableInputLines.size();i++)
    {
        double metrics=1.0;
        //如果输入栏存在单位，则在找到该输入栏表示的数值数组，根据输入栏现在的index来选择;
        if(mapOfMetricsComboBox.contains(cableInputLines[i]))
        {
            if(mapOfMetricsValue.contains(cableInputLines[i]))
            {
                metrics=mapOfMetricsValue[cableInputLines[i]][mapOfMetricsComboBox[cableInputLines[i]]->currentIndex()];
            }
        }
        temp=cableInputLines[i]->getText().toDouble()*metrics;
        numberList.push_back(temp);
    }
    temp=0.0;
    for(int i=0;i<comboboxList.size();i++)
    {

        if(mapOfMetricsValue.contains(comboboxList[i]))
        {
            temp=mapOfMetricsValue[comboboxList[i]][comboboxList[i]->currentIndex()];
        }
        else{
            temp=comboboxList[i]->currentIndex();
        }
        numberList.push_back(temp);
    }
    return numberList;
}

QVector<QString> SettingWidget_HighSpeed::getInputText()
{
    QVector<QString> textList;
    for(int i=0;i<textInputLines.size();i++)
    {
        textList.append(textInputLines[i]->getText());
    }
    return textList;
}



ShapeWithColorList SettingWidget_HighSpeed::getShape()
{
    ShapeWithColorList list;
    double r1=cableInputLines[0]->getText().toDouble();
    double d=cableInputLines[1]->getText().toDouble();
    double r2=cableInputLines[2]->getText().toDouble();
    double h=cableInputLines[3]->getText().toDouble();
    double l=cableInputLines[4]->getText().toDouble();



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

    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(cable1,Quantity_NOC_CYAN));
    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(cable2,Quantity_NOC_CYAN));
    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(cable3,Quantity_NOC_RED));
    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(cable4,Quantity_NOC_RED));
    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(cable5,Quantity_NOC_RED));
    list.push_back(QPair<TopoDS_Shape,Quantity_NameOfColor>(outerShape,Quantity_NOC_GOLD));
    return list;

}

int SettingWidget_HighSpeed::isShapeInputCompleted()
{
    //验证是否输入完整
    for(int i=0;i<5;i++)
    {
        if(cableInputLines[i]->getText().isNull() || cableInputLines[i]->getText().isEmpty())
        {
            return  0;
        }
    }
    //验证参数是否输入正确
    double r1=cableInputLines[0]->getText().toDouble();
    double d=cableInputLines[1]->getText().toDouble();
    double r2=cableInputLines[2]->getText().toDouble();
//    double h=cableInputLines[3]->getText().toDouble();
    double l=cableInputLines[4]->getText().toDouble();

    if(r1>=r2||d<2*r2||r1==0.0||r2==0.0 || l==0.0)
    {
        return -1;
    }
    return 1;
}

void SettingWidget_HighSpeed::sendInputInformation()
{
    qDebug()<<"Start to send input information";
    QVector<QString>name;
    name<<"线缆类型"<<"实例名称";
    for(int i=0;i<10;i++)
    {
        name.push_back(InfoText::getHighSpeedParameterName(mainRange[i]));
    }
    name<<"屏蔽层电导率"<<"线缆电导率"<<"线缆分布参数"<<"夹具名称";
    qDebug()<<"step 1";
    QVector<QString>parameter;
    parameter<<"高速线";
    parameter.push_back(textInputLines[0]->getText());
    for(auto x : getInputNumber())
    {
        parameter.push_back(QString("%1").arg(x));
    }
    qDebug()<<"step 2";
    if(textInputLines.size()>1)
    {
        parameter.push_back(textInputLines[1]->getText().split("/").last());
    }
    else{
        parameter.push_back("无");
    }
    qDebug()<<"step 3";
    QVector<QString>metrics;
    metrics<<""<<"";
    for(int i=0;i<cableInputLines.size();i++)
    {
        if(mapOfMetricsComboBox.contains(cableInputLines[i]))
        {
            metrics.push_back(mapOfMetricsComboBox[cableInputLines[i]]->currentText());
        }
        else{
            metrics.push_back("");
        }
    }
    metrics<<"S/m"<<"S/m"<<""<<"";

    qDebug()<<"end send info";
    emit transInputInfo(name,parameter,metrics);


}
