#include "comboboxtest.h"
#include <combobox.h>

ComboboxTest::ComboboxTest(QWidget *parent) : QWidget(parent)
{
    this->resize(800,600);
    Combobox * box=new Combobox(this);
    box->move(100,100);


}
