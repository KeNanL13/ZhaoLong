#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QWidget>
#include <QComboBox>


class Combobox : public QWidget
{
    Q_OBJECT
public:
    explicit Combobox(QWidget *parent = nullptr);
private:
    QComboBox * box;
private:
    void setAutoFitWidth(QComboBox *box);
signals:

public slots:

    // QWidget interface
protected:
    void showEvent(QShowEvent *event);
};

#endif // COMBOBOX_H
