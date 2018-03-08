#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QPoint>

class EditDialog : public QWidget
{
    Q_OBJECT
public:
    explicit EditDialog(QWidget *parent = nullptr);

public:
    QGridLayout *layout;
    QLabel *startLabel;
    QLabel *endLabel;
    QLineEdit *x1Text;
    QLineEdit *y1Text;
    QLineEdit *x2Text;
    QLineEdit *y2Text;
    QLabel *rLabel;
    QLabel *gLabel;
    QLabel *bLabel;
    QLineEdit *rText;
    QLineEdit *gText;
    QLineEdit *bText;
    QPushButton *okButton;

signals:
    void resultSignal(QPoint,QPoint,QColor);
public slots:
    void okButtonSlot();
};

#endif // EDITDIALOG_H
