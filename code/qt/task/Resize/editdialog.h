#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QPoint>
#include <QComboBox>

class EditDialog : public QWidget
{
    Q_OBJECT
public:
    explicit EditDialog(QWidget *parent = nullptr);

public:
    QGridLayout *layout;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QLineEdit *widthText;
    QLineEdit *heightText;
    QPushButton *okButton;
    QComboBox *combobox;

signals:
    void resultSignal(int width,int height);

public slots:
    void okButtonSlot();
};

#endif // EDITDIALOG_H
