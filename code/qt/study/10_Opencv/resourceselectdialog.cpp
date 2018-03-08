#include "resourceselectdialog.h"

ResourceSelectDialog::ResourceSelectDialog(QWidget *parent) : QDialog(parent)
{
    layout = new QGridLayout(this);
    listWidget = new QListWidget(this);
    buttonOK = new QPushButton("确定",this);
    buttonCANCEL = new QPushButton("取消",this);

    layout->addWidget(listWidget,0,0,1,2);
    layout->addWidget(buttonOK,1,0,1,1);
    layout->addWidget(buttonCANCEL,1,1,1,1);

    //列表控件
    listWidget->setIconSize(QSize(100,100)); //设置QListWidget中的单元项的图片大小
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setViewMode(QListView::IconMode);  //设置QListWidget的显示模式
    listWidget->setMovement(QListView::Static); //设置QListWidget中的单元项不可被拖动
    listWidget->setSpacing(10);  //设置QListWidget中的单元项的间距

    connect(buttonOK,SIGNAL(clicked()),this,SLOT(buttonOkClicked()));
    connect(buttonCANCEL,SIGNAL(clicked()),this,SLOT(buttonCANCELClicked()));
}

void ResourceSelectDialog::initListWidget()
{
    //加载资源列表
    for(int i = 0;i<Globalvariable::imageObjectList.count();i++)
    {
        QPixmap pixmap(QPixmap::fromImage(*Globalvariable::imageObjectList.at(i).image));//生成图像objPixmap

        QListWidgetItem *item =
                new QListWidgetItem(QIcon(pixmap.scaled(QSize(100,100))),*Globalvariable::imageObjectList.at(i).imageName);  //生成QListWidgetItem对象

        item->setSizeHint(QSize(100,120)); //设置单元项的宽度和高度

        listWidget->addItem(item); //添加QListWidgetItem项
    }

    listWidget->setCurrentRow(0);//设置资源列表默认索引为0
}

void ResourceSelectDialog::buttonOkClicked()
{
    //listWidget->currentIndex().row();//列表控件当前选择索引
    Globalvariable::imageBlend1 =
            new ImageObject(Globalvariable::imageObjectList.at(listWidget->currentRow()));
    emit okClicked();

    this->close();
}

void ResourceSelectDialog::buttonCANCELClicked()
{
    this->close();
}
