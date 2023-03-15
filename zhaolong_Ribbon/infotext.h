#ifndef INFOTEXT_H
#define INFOTEXT_H
#include <QString>

class InfoText
{
private:
    InfoText();

public:
    static QString getHighSpeedParameterName(unsigned int index);
    static QString getHighSpeedDefaultParameter(unsigned int index);
    static QString getComboBoxStyleSheet();

};

#endif // INFOTEXT_H
