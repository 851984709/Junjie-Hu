#ifndef OPERATIONVIEW_H
#define OPERATIONVIEW_H

#include <QWidget>
#include <QDockWidget>

#include "blendcomponent.h"

class OperationView : public QDockWidget
{
    Q_OBJECT
public:
    explicit OperationView(QWidget *parent = nullptr);

    BlendComponent *blendComponent; //混合组件



signals:

public slots:
};

#endif // OPERATIONVIEW_H
