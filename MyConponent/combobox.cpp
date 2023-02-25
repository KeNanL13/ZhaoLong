#include "combobox.h"
#include <QListView>

Combobox::Combobox(QWidget *parent) : QWidget(parent)
{
    QComboBox * box=new QComboBox();
    box->setView(new QListView());
    box->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt ::NoDropShadowWindowHint);
    box->view()->window()->setAttribute(Qt::WA_TranslucentBackground);

}
