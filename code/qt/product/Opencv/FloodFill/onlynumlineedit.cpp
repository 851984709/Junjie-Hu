#include "onlynumlineedit.h"

QString OnlyNumLineEdit::textLast = "";

OnlyNumLineEdit::OnlyNumLineEdit(QWidget *parent) : QLineEdit(parent)
{
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
}

void OnlyNumLineEdit::textChanged(QString text)
{
    //判断是否为空
    if(text.isEmpty())
    {
        textLast = QString::number(0);
        setText(textLast);

        emit textExactlyChanged();

        return;
    }
    /*
    //不能判断 0
    if(!text.toInt())
    {
        qDebug()<<"不是纯数字";
        setText(textLast);
    }
    else{
    textLast =text;
    }
    */

    //可以判断 0
    QByteArray ba = text.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        qDebug()<<"不是纯数字";
        setText(textLast);
        return ;
    }
    else{
        int num = text.toInt();
        //判断数值是否在范围内
        if(num<0)
            num = 0;
        else if(num > 255)
            num = 255;

        textLast = QString::number(num);
        setText(textLast);//防止数值的第一位为0

        emit textExactlyChanged();
    }
}
