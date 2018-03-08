#include "editdialog.h"

EditDialog::EditDialog(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    startLabel = new QLabel("start",this);
    endLabel = new QLabel("end",this);
    x1Text = new QLineEdit("0",this);
    y1Text = new QLineEdit("0",this);
    x2Text = new QLineEdit("100",this);
    y2Text = new QLineEdit("100",this);
    rLabel = new QLabel("R:",this);
    gLabel = new QLabel("G:",this);
    bLabel = new QLabel("B:",this);
    rText = new QLineEdit("0",this);
    gText = new QLineEdit("0",this);
    bText = new QLineEdit("0",this);
    okButton = new QPushButton("OK",this);

    layout->addWidget(startLabel,0,0,1,1);
    layout->addWidget(x1Text,0,1,1,1);
    layout->addWidget(y1Text,0,2,1,1);
    layout->addWidget(endLabel,1,0,1,1);
    layout->addWidget(x2Text,1,1,1,1);
    layout->addWidget(y2Text,1,2,1,1);
    layout->addWidget(rLabel,2,0,1,1);
    layout->addWidget(gLabel,3,0,1,1);
    layout->addWidget(bLabel,4,0,1,1);
    layout->addWidget(rText,2,1,1,1);
    layout->addWidget(gText,3,1,1,1);
    layout->addWidget(bText,4,1,1,1);
    layout->addWidget(okButton,2,2,1,1);

    connect(okButton,SIGNAL(clicked()),this,SLOT(okButtonSlot()));
}

void EditDialog::okButtonSlot()
{
    int x1 = x1Text->text().toInt();
    int y1 = y1Text->text().toInt();
    int x2 = x2Text->text().toInt();
    int y2 = y2Text->text().toInt();
    int r = rText->text().toInt();
    int g = gText->text().toInt();
    int b = bText->text().toInt();
    QPoint startPoint = QPoint(x1,y1);
    QPoint endPoint = QPoint(x2,y2);
    QColor color = QColor(r,g,b);

    emit resultSignal(startPoint,endPoint,color);
}
