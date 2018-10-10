#include "enddialog.h"
#include "gridwidget.h"

EndDialog::EndDialog(int steps, QWidget *parent) : QDialog(parent), winSteps(steps)
{

   // setFixedSize(200, 200);
    setModal(true);

    label = new QLabel("A játéknak vége, a játékos " + QString::number(winSteps) + " teljesítette a játékot."
                                                                                   "A játék 5 mperc múlva újraindul! " ,this);
    newGameButton = new QPushButton(tr("&Új játék rögtön"),this);
    quitButton = new QPushButton(tr("&Kilépés"), this);
    //grid = new GridWidget;
    timer = new QTimer;

    connect(newGameButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(timer, SIGNAL(timeout()), this, SLOT(accept()));

    buttons = new QHBoxLayout;
    buttons->addWidget(newGameButton);
    buttons->addWidget(quitButton);

    main = new QVBoxLayout;
    main->addWidget(label);
    main->addLayout(buttons);

    setLayout(main);

    timer->start(7000);
}

void EndDialog::update()
{


}
