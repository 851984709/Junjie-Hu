#ifndef DOCKWIDGETLIST_H
#define DOCKWIDGETLIST_H

#include <QWidget>
#include <QDockWidget>
#include <QListWidget>
#include <QPixmap>
#include <QFileInfo>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QMessageBox>

#include "globalvariable.h"

class ResourceView : public QDockWidget
{
    Q_OBJECT
public:
    explicit ResourceView(QWidget *parent = nullptr);

    QListWidget *listWidget;//列表控件
    QMenu *contextMenu;//右键菜单
    QAction *actEdit;

signals:
    void refresh();
    void saveEnable();

public slots:
    void addImage();
    void customContextMenuRequested(QPoint);
    void editImage();
};

#endif // DOCKWIDGETLIST_H
