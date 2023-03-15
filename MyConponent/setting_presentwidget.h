#ifndef SETTING_PRESENTWIDGET_H
#define SETTING_PRESENTWIDGET_H

#include <QWidget>
#include <slidepage.h>
#include <lineeditwidget.h>
class Setting_PresentWidget : public SlidePage
{
    Q_OBJECT
public:
    explicit Setting_PresentWidget(int radius, QString name, QWidget *parent = nullptr);

    void createPage(int type,QString name,QVector<QString>names,QVector<QString>parameters,QVector<QString> Metrics);

private:
    LineEditWidget *getLineEditWidget(QString label,QString value,QString Metrics);
    const QFont font=QFont("DengXian",12,QFont::Normal);

signals:

public slots:
};

#endif // SETTING_PRESENTWIDGET_H
