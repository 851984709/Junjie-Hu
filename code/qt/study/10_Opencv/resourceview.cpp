#include "resourceview.h"

ResourceView::ResourceView(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("资源试图");

    listWidget = new QListWidget((QWidget*)this->parent());

    setWidget(listWidget);

    //setWindowFlag(Qt::FramelessWindowHint);

    listWidget->setIconSize(QSize(100,100)); //设置QListWidget中的单元项的图片大小

    listWidget->setResizeMode(QListView::Adjust);

    listWidget->setViewMode(QListView::IconMode);  //设置QListWidget的显示模式

    listWidget->setMovement(QListView::Static); //设置QListWidget中的单元项不可被拖动

    listWidget->setSpacing(10);  //设置QListWidget中的单元项的间距

    //鼠标右键菜单事件
    contextMenu = new QMenu(this);

    actEdit = contextMenu->addAction("编辑");

    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);//设定列表控件有上下文菜单

}

void ResourceView::addImage()
{
    QPixmap pixmap(QPixmap::fromImage(*Globalvariable::imageObjectList.last().image));//生成图像objPixmap

    QListWidgetItem *item =
            new QListWidgetItem(QIcon(pixmap.scaled(QSize(100,100))),*Globalvariable::imageObjectList.last().imageName);  //生成QListWidgetItem对象

    item->setSizeHint(QSize(100,120)); //设置单元项的宽度和高度

    listWidget->addItem(item); //添加QListWidgetItem项
}


void ResourceView::customContextMenuRequested(QPoint pos)//鼠标右键菜单
{
    contextMenu->exec(QCursor::pos());
}

void ResourceView::editImage()
{
    if(!Globalvariable::imageObjectCurrent)//当前图像为空
    {
        Globalvariable::imageObjectCurrent =
                new ImageObject(Globalvariable::imageObjectList.at(listWidget->currentIndex().row()));

        emit refresh();
        emit saveEnable();
    }
    else//当前图像不为空
    {
        int ret = QMessageBox::question(this,
                                        "问题对话框",
                                        "重新编辑图片将删除当前正在编辑的图像，确定要继续编辑吗？");

        if(ret == QMessageBox::Yes)
        {
            Globalvariable::imageObjectCurrent =
                    new ImageObject(Globalvariable::imageObjectList.at(listWidget->currentIndex().row()));

            emit refresh();
            emit saveEnable();
        }
    }
}
