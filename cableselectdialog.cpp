#include "cableselectdialog.h"
#include "ui_cableselectdialog.h"

CableSelectDialog::CableSelectDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CableSelectDialog)
{
    ui->setupUi(this);
    QVBoxLayout * layout=new QVBoxLayout();
    QSplitter * splitter=new QSplitter();
    splitter->addWidget(ui->widgetLeft);
    splitter->addWidget(ui->widgetRight);
    splitter->setStretchFactor(0,5);
    splitter->setStretchFactor(1,6);
    splitter->setContentsMargins(5,5,20,5);
    QSplitter * splitter1=new QSplitter();
    splitter1->setOrientation(Qt::Orientation::Vertical);
    splitter1->addWidget(ui->widgetTop);
    splitter1->addWidget(splitter);
    splitter1->setStretchFactor(0,1);
    splitter1->setStretchFactor(1,9);

    layout->addWidget(splitter1);
    this->setLayout(layout);
    item1UIChange();
    ui->pictureLabel->setScaledContents(true);

    QListWidgetItem * item1 = new QListWidgetItem("平行线");
    QListWidgetItem * item2 = new QListWidgetItem("双绞线");
    QListWidgetItem * item3 = new QListWidgetItem("带夹具的线缆");
    QListWidgetItem * item4 = new QListWidgetItem("高速线缆");
//    QListWidgetItem * item5 = new QListWidgetItem("双绞线束");
    connect(ui->listWidget,&QListWidget::itemClicked,this,&CableSelectDialog::itemCliked);
    ui->listWidget->addItem(item1);
    ui->listWidget->addItem(item2);
    ui->listWidget->addItem(item3);
    ui->listWidget->addItem(item4);
//    ui->listWidget->addItem(item5);
    connect(ui->pushButton,&QPushButton::clicked,this,&CableSelectDialog::confirmBtn);
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        QString path1=QFileDialog::getOpenFileName(this,"寻找夹具S参数文件","E:/");
        ui->lineEdit3_1->setText(path1);
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        QString path1=QFileDialog::getOpenFileName(this,"寻找夹具S参数文件","E:/");
        ui->lineEdit3_2->setText(path1);
    });

}

CableSelectDialog::~CableSelectDialog()
{
    delete ui;
}

void CableSelectDialog::itemCliked(QListWidgetItem *item)
{
    if(item->text()=="平行线")
    {
        item1UIChange();
    }
    else if(item->text()=="双绞线") {
        item2UIChange();
    }
    else if(item->text()=="带夹具的线缆")
    {
        item3UIChange();
    }
    else if(item->text()=="高速线缆")
    {
        item4UIChange();
    }
}

void CableSelectDialog::item1UIChange()
{
    ui->pictureLabel->setPixmap(QPixmap(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CablePicture/parrell.png"))));
    ui->stackedWidget->setCurrentIndex(0);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("模型描述：");
    ui->plainTextEdit->appendPlainText("计算平行线模型在远场平面波激励后的响应，表示为不同频率下的感应电流，包括差模电流和共模电流");

}

void CableSelectDialog::item2UIChange()
{
    ui->pictureLabel->setPixmap(QPixmap(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CablePicture/TWP.png"))));
    ui->stackedWidget->setCurrentIndex(1);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("模型描述：");
    ui->plainTextEdit->appendPlainText("计算双绞线线模型在远场平面波激励后的响应，表示为不同频率下的感应电流，包括差模电流和共模电流");
}

void CableSelectDialog::item3UIChange()
{
    ui->pictureLabel->setPixmap(QPixmap(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CablePicture/fixtureAndcable.png"))));
    ui->stackedWidget->setCurrentIndex(2);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("模型描述：");
    ui->plainTextEdit->appendPlainText("导入夹具和线缆S参数数据文件(S4G格式),计算出总体系统的S参数");
}

void CableSelectDialog::item4UIChange()
{
    ui->pictureLabel->setPixmap(QPixmap(QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CablePicture/cable.png"))));
    ui->stackedWidget->setCurrentIndex(3);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("模型描述：");
    ui->plainTextEdit->appendPlainText("计算高速线缆的S参数，并导出S4P文件");
}

void CableSelectDialog::confirmBtn()
{
    receiveMessage();
    switch (ui->stackedWidget->currentIndex()) {
    case 0:
        emit CableSignal(ParallelCable,QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CableModels/parallel cable.stp")));
        break;
    case 1:
        emit CableSignal(TWP_Cable,QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CableModels/TWP.stp")));
        break;
    case 2:
        emit CableSignal(SystemS_parameters,"");
        break;
    case 3:
        emit CableSignal(HighSpped,QDir::cleanPath(QCoreApplication::applicationDirPath() + QDir::separator() + QString("/CableModels/cable.step")));
        break;
    case 4:
        emit CableSignal(TBTWBcable,"");
        break;
    default:
        break;
    }
    this->close();
}

void CableSelectDialog::receiveMessage()
{
    if(ui->stackedWidget->currentIndex()==0){
        parameters<<ui->lineEdit->text()<<ui->lineEdit_2->text()<<ui->lineEdit_3->text();
        parameters<<ui->lineEdit_4->text()<<ui->lineEdit_5->text()<<ui->lineEdit_6->text();
        parameters<<ui->lineEdit_7->text()<<ui->lineEdit_8->text()<<ui->lineEdit_9->text();}
    else if (ui->stackedWidget->currentIndex()==1)
    {
        parameters<<ui->lineEdit2_1->text()<<ui->lineEdit2_2->text()<<ui->lineEdit2_3->text();
        parameters<<ui->lineEdit2_4->text()<<ui->lineEdit2_5->text()<<ui->lineEdit2_6->text();
        parameters<<ui->lineEdit2_7->text()<<ui->lineEdit2_8->text()<<ui->lineEdit2_9->text();
        parameters<<ui->lineEdit2_10->text();
    }
    else if(ui->stackedWidget->currentIndex()==2)
    {
        parameters<<ui->lineEdit3_1->text()<<ui->lineEdit3_2->text();
    }
    else if(ui->stackedWidget->currentIndex()==3)
    {
        parameters<<ui->lineEdit4_1->text()<<ui->lineEdit4_2->text()<<ui->lineEdit4_3->text();
        parameters<<ui->lineEdit4_4->text()<<ui->lineEdit4_5->text()<<ui->lineEdit4_6->text();
        parameters<<ui->lineEdit4_7->text()<<ui->comboBox_12->itemText(0)<<ui->comboBox_11->itemText(0);
        parameters<<ui->lineEdit4_10->text();
    }
}
