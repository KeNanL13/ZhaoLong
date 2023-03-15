#include "combobox.h"
#include <QListView>
#include <QBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

Combobox::Combobox(QWidget *parent) : QWidget(parent)
{
    box=new QComboBox();
    QVBoxLayout *layout=new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(box);
    this->setLayout(layout);
    box->addItem("123");
    box->addItem("23");
    box->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    QFont font=QFont("DengXian",12,QFont::Normal);
    box->setFont(font);


    QString boxStyleSheet=QString("QComboBox{"
                                  "border:2px solid #f3f3f3;"
                                  "border-radius:2px;"
                                  "padding:1px 2px 1px 2px;"
                                  "text-align:bottom;"
                                  "padding-left:10px;"
                                  "}"
                                  "QComboBox::drop-down{"
                                  "subcontrol-origin:padding;"
                                  "subcontrol-position:top right;"
                                  "border-top-right-radius: 3px;"
                                  "border-bottom-right-radius: 3px;"
                                  "}"
                                  "QComboBox::down-arrow{"
                                  "border-image:url(:/icons/icons/navigation/svg/production/ic_expand_more_24px.svg);"
                                  "}");
    box->setStyleSheet(boxStyleSheet);
//    this->setAutoFitWidth(box);
}

void Combobox::setAutoFitWidth(QComboBox *box)
{
    if(box==nullptr){
        return;
    }
    int num=box->count();
    int maxLen=0,itemLen=0;
    QFontMetrics fm(box->view()->font());
    for(int i=0;i<num;i++)
    {
        itemLen=fm.width(box->itemText(i));
        maxLen=maxLen>itemLen?maxLen:itemLen;
    }
    box->setMinimumWidth(maxLen+10);
}

void Combobox::showEvent(QShowEvent *event)
{
//    this->setAutoFitWidth(box);
}
