#ifndef SLIDEWIDGET_INFO_H
#define SLIDEWIDGET_INFO_H

#include <QWidget>
#include <MyComponents/lineeditwidget.h>
#include <MyComponents/slidepage.h>


class SlideWidget_INFO : public SlidePage
{
    Q_OBJECT
public:
    explicit SlideWidget_INFO(int radius, QString name, QWidget *parent = nullptr);

    void removeAll();
    void createPage(QStringList names,QStringList parameters,QStringList Metrics);

private:
    LineEditWidget *getLineEditWidget(QString label,QString value,QString Metrics);
    const QFont font=QFont("DengXian",12,QFont::Normal);
    QVector<QWidget*>widgetList;


signals:

public slots:
};

#endif // SLIDEWIDGET_INFO_H
