#include "editdialog.h"

EditDialog::EditDialog(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    widthLabel = new QLabel("width",this);
    heightLabel = new QLabel("height",this);
    widthText = new QLineEdit("100",this);
    heightText = new QLineEdit("100",this);
    okButton = new QPushButton("OK",this);
    combobox = new QComboBox(this);

    combobox->addItem("临近点法");
    combobox->addItem("线性插值法");

    layout->addWidget(widthLabel,0,0,1,1);
    layout->addWidget(widthText,0,1,1,1);
    layout->addWidget(heightLabel,1,0,1,1);
    layout->addWidget(heightText,1,1,1,1);
    layout->addWidget(okButton,2,0,1,1);
    layout->addWidget(combobox,2,1,1,1);

    connect(okButton,SIGNAL(clicked()),this,SLOT(okButtonSlot()));
}

void EditDialog::okButtonSlot()
{
    int width = widthText->text().toInt();
    int height = heightText->text().toInt();

    emit resultSignal(width,height);
}
