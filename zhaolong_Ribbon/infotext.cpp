#include "infotext.h"

InfoText::InfoText()
{

}

QString InfoText::getHighSpeedParameterName(unsigned int index)
{
   QString name;
   switch (index) {
   case 0:name="线缆半径";break;
   case 1:name="信号线距离";break;
   case 2:name="屏蔽层半径";break;
   case 3:name="PE相对介电常数";break;
   case 4:name="损耗正切";break;
   case 5:name="屏蔽层厚度";break;
   case 6:name="线缆总长";break;
   case 7:name="沟槽宽度";break;
   case 8:name="最小频率";break;
   case 9:name="最大频率";break;
   case 10:name="线缆分布参数";break;
   default:name="";break;
   }
//    const QString highSpeedParameterName[10]{
//        "线缆半径",
//        "信号线距离",
//        "屏蔽层半径",
//        "PE相对介电常数",
//        "损耗正切",
//        "屏蔽层厚度",
//        "线缆总长",//后面有屏蔽层电导率和线缆电导率
//        "沟槽宽度",
//        "最小频率",
//        "最大频率"
//    };
   return name;
}

QString InfoText::getHighSpeedDefaultParameter(unsigned int index)
{
    QString name;
    switch (index) {
    case 0:name="0.2075";break;
    case 1:name="1.42";break;
    case 2:name="0.71";break;
    case 3:name="2";break;
    case 4:name="0.0005";break;
    case 5:name="0.009";break;
    case 6:name="200";break;
    case 7:name="0.07";break;
    case 8:name="1";break;
    case 9:name="40";break;
    default:name="";break;
    }
//    const QString highSpeedParameterDefault[10]{
//        "0.2075",
//        "1.42",
//        "0.71",
//        "2",
//        "0.0005",
//        "0.009",
//        "200",
//        "0.07",
//        "1",
//        "40"
//    };
    return name;
}

QString InfoText::getComboBoxStyleSheet()
{
    QString styleSheet;
    styleSheet=QString("QComboBox{"
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
    return  styleSheet;
}


