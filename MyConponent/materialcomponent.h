#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include <QWidget>
#include <qtmaterialcheckbox.h>
#include <qtmaterialdrawer.h>
#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>
#include <qtmaterialcircularprogress.h>
#include <qtmaterialprogress.h>
#include <qtmaterialslider.h>
#include <qtmaterialsnackbar.h>
#include <qtmaterialtextfield.h>
#include <lineeditwidget.h>
#include <pushbutton.h>


class MaterialComponent : public QWidget
{
    Q_OBJECT
public:
    explicit MaterialComponent(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MATERIALCOMPONENT_H
