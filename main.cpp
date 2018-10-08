#include "mygrid.h"
#include "sizedialog.h"
#include "tablewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGrid *w;
    w = new MyGrid;

    w->show();



    return a.exec();
}
