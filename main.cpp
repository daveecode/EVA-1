#include "mybutton.h"
#include "gridwidget.h"
#include "enddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GridWidget *w;
    w = new GridWidget;

    w->show();

    return a.exec();
}
