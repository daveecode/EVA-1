#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include "mybutton.h"
#include "sizedialog.h"
#include "enddialog.h"
#include <QTextEdit>

class GridWidget : public QWidget

{

    Q_OBJECT

public:

    GridWidget(QWidget *parent = 0);
    ~GridWidget();
    int steps;

private:

    QPushButton *playButton;
    QPushButton *aboutButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QLabel *countS;
    QLabel *countQ;
    QGridLayout *grid;
    QHBoxLayout *labels;
    QVBoxLayout *main;

    QVector<MyButton *> _buttons;
    QVector<MyButton *>_queens;
    SizeDialog *dial;
    QDialog *end;

    int queens;

    void setQueen(Coordinate cord);
    void backQueen(Coordinate cord);
    bool isWin();

private slots:

    void click();
    void play();
    void info();
    void updateLabels();

};

#endif // GRIDWIDGET_H
