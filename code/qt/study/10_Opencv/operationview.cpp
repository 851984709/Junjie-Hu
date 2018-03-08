#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("操作视图");

    blendComponent = new BlendComponent(this);

    blendComponent->hide();

    setBaseSize(230,0);

    setMinimumWidth(230);//最小宽度
    setMaximumWidth(230);//最大宽度
}
