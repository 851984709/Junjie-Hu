#ifndef RESOURCESELECTDIALOG_H
#define RESOURCESELECTDIALOG_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

#include <globalvariable.h>

class ResourceSelectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ResourceSelectDialog(QWidget *parent = nullptr);

    QGridLayout *layout;
    QListWidget *listWidget;
    QPushButton *buttonOK;
    QPushButton *buttonCANCEL;

    void initListWidget();

signals:
    void okClicked();
public slots:
    void buttonOkClicked();
    void buttonCANCELClicked();
};

#endif // RESOURCESELECTDIALOG_H
