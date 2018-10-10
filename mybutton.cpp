#include "mybutton.h"
#include "ui_mybutton.h"

MyButton::MyButton(Coordinate coordinate, QWidget *parent) : QPushButton(parent), coord(coordinate)

{

    setFixedSize(90,90);
    setStyleSheet("margin : 2px, background: white");
}

Coordinate MyButton::getCoordinate() {

    return coord;
}
