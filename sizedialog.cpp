#include "sizedialog.h"

SizeDialog::SizeDialog(QWidget *parent) : QDialog(parent)

{

    setWindowTitle(tr("Beállítások"));
    setFixedSize(300, 150);
    setModal(true);

    lab = new QLabel(tr("Hány királynőt szeretne elhelyezni?"), this);
    box = new QSpinBox;
    box->setMinimum(4);
    box->setMaximum(8);
    box->setValue(4);
    box->setSingleStep(2);

    okButton = new QPushButton(tr("&OK"), this);
    okButton->setFixedWidth(70);

    cancelButton = new QPushButton(tr("&Cancel"), this);
    cancelButton->setFixedWidth(70);



    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));


    felso = new QHBoxLayout;
    felso->addWidget(lab);
    felso->addWidget(box);

    also = new QHBoxLayout;
    also->addWidget(okButton);
    also->addWidget(cancelButton);

    _main = new QVBoxLayout;
    _main->addLayout(felso);
    _main->addLayout(also);
    setLayout(_main);
}

int SizeDialog::getSize()
{

    return box->value();
}
