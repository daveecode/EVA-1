#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "coordinate.h"

class MyButton : public QPushButton

{
    Q_OBJECT

public:

    MyButton(Coordinate coordinate, QWidget *parent = 0);
    Coordinate getCoordinate();
    Coordinate coord;
};

#endif // MYBUTTON_H
