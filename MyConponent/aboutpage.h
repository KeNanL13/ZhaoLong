#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QPair>
#include <pagewidget.h>
#include <lineeditwidget.h>


class AboutPage : public PageWidget
{
    Q_OBJECT
public:
    explicit AboutPage(QWidget *parent = nullptr);
private:
    //PushButton icons
    QLabel *iconButtonLabel=nullptr;
    QWidget* textButtonWidget=nullptr;
    QHBoxLayout * textButtonLayout=nullptr;
    QLabel*textButtonIcon=nullptr;
    QLabel*textButtonLabel=nullptr;

    //UI elements
    QVBoxLayout * titleLayout=nullptr;
    const QFont titleFont=QFont("DengXian",26,QFont::ExtraLight);
    QLabel * titleLabel=nullptr;

    QWidget* mainWidget=nullptr;
    QVBoxLayout * mainLayout=nullptr;

    LineEditWidget * authorLabel=nullptr;
    LineEditWidget * versionLabel=nullptr;
    LineEditWidget * dateLabel=nullptr;

    LineEditWidget * skyTerLabel=nullptr;
    LineEditWidget * lightLabel=nullptr;
    LineEditWidget * coreLabel=nullptr;
    LineEditWidget * uiDesignerLabel=nullptr;

    LineEditWidget * license=nullptr;
    LineEditWidget * qtVersion=nullptr;
    LineEditWidget * usedLib=nullptr;
    LineEditWidget * githubLink=nullptr;

public:
    virtual PushButton *getPageIconButton(QWidget* context)override;
    virtual PushButton *getPageTextButton(QWidget *context)override;

signals:

public slots:
};

#endif // ABOUTPAGE_H
