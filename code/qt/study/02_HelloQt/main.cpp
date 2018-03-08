#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("你好Qt");//设置标题

    QPushButton b1;
    b1.setText("^_^");//给按钮设置内容
    b1.setParent(& w);//设定父窗口
    b1.move(QPoint(100,100));//移动按钮

    QPushButton b2(&w);
    b2.move(300,300);

    /*如果不指定父对象，对象和对象（窗口和窗口）没有关系，独立
     * a指定b为它的父对象，a放在b上面
     * 指定父对象，有2各种方法：
     *              1）setparent
     *              2)通过构造函数传参
     * 指定父对象，只需要父对象显示，上面的子对象自动显示
    */

    w.show();

    app.exec();
    return 0;
}
