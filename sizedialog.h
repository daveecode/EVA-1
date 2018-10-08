#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QLayout>

class SizeDialog : public QDialog

{

    Q_OBJECT

public:

    SizeDialog(QWidget *parent = 0);
    int getSize();

private:

    QLabel *lab;
    QSpinBox *box;
    QPushButton *okButton;
    QPushButton *cancelButton;

    QHBoxLayout *felso;
    QHBoxLayout *also;
    QVBoxLayout *_main;
    QWidget *table;

};

#endif // SIZEDIALOG_H
