#ifndef MYGRID_H
#define MYGRID_H

#include "sizedialog.h"
#include "coordinate.h"
#include <QWidget>
#include <QPushButton>

class MyGrid : public QWidget
{
    Q_OBJECT

public:

    MyGrid(QWidget *parent = 0);


private:

    SizeDialog *dial;
    QGridLayout *grid;
    QVBoxLayout *main;
    QHBoxLayout *labels;
    QPushButton *playButton;
    QPushButton *aboutButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QLabel *queens;
    QLabel *steps;
    QVector <QPushButton*> _buttons;
    QVector <Coordinate> _coordinates;
    Coordinate gridCoordinates;
    QVector <QPushButton*> _senders;
    QVector<QPushButton*> _isQueen;
    int _queens;
    int _steps;


    bool isWin();
    bool isSettable();
    int getColumn(QPushButton *button);
    int getRow(QPushButton *button);

private slots:

    void Click();
    void play();
    void info();
    void updateLabels();

};

#endif // MYGRID_H
