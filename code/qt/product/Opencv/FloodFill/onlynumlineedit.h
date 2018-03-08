#ifndef ONLYNUMLINEEDIT_H
#define ONLYNUMLINEEDIT_H

#include <QLineEdit>
#include <QString>
#include <QDebug>

class OnlyNumLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit OnlyNumLineEdit(QWidget *parent = nullptr);

    static QString textLast;

signals:
    void textExactlyChanged();
public slots:
    void textChanged(QString);
};

#endif // ONLYNUMLINEEDIT_H
