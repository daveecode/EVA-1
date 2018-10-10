#ifndef ENDDIALOG_H
#define ENDDIALOG_H
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QLayout>
#include "gridwidget.h"
#include "sizedialog.h"

class EndDialog : public QDialog

{
    Q_OBJECT

public:

    EndDialog(int steps, QWidget *parent = 0);
    int winSteps;

private:

    QLabel *label;
    QPushButton *newGameButton;
    QPushButton *quitButton;
    QHBoxLayout *buttons;
    QVBoxLayout *main;
    QTimer *timer;

private slots:

    void update();
};
#endif // ENDDIALOG_H
