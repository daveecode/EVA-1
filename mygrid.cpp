#include "mygrid.h"
#include <QTextEdit>

MyGrid::MyGrid(QWidget *parent) : QWidget(parent)

{
    setWindowTitle("Királynők - Játék");
    setFixedSize(400-frameSize().width(), 600);
    setGeometry(300, 0, 400, 400);

    dial = new SizeDialog;
    grid = new QGridLayout;
    main = new QVBoxLayout;
    labels = new QHBoxLayout;

    _buttons.clear();
    _senders.clear();
    _coordinates.clear();
    _isQueen.clear();

    _queens = dial->getSize();
    _steps = 0;

    playButton = new QPushButton(tr("&Játék"), this);
    playButton->setGeometry(0,0, 400-frameSize().width(), 20);
    playButton->show();

    aboutButton = new QPushButton(tr("&Szabályok"), this);
    aboutButton->setGeometry(0, 50, this->width(), 20);
    aboutButton->show();

    settingsButton = new QPushButton(tr("&Beállítások"), this);
    settingsButton->setGeometry(0, 100, this->width(), 20);
    settingsButton->show();

    exitButton = new QPushButton(tr("&Kilépés"), this);
    exitButton->setGeometry(0, 150, this->width(), 20);
    exitButton->show();

    queens = new QLabel("A megmaradt királynők száma: ", this);
    queens->setText(queens->text() + QString::number(_queens));

    steps = new QLabel("A lépések száma: ", this);
    steps->setText(steps->text() + QString::number(_steps));

    labels->addWidget(steps);
    labels->addWidget(queens);

    main->addWidget(playButton);
    main->addWidget(aboutButton);
    main->addWidget(settingsButton);
    main->addWidget(exitButton);
    main->addLayout(labels);

    connect(playButton, SIGNAL(clicked(bool)), this, SLOT(play()));
    connect(aboutButton, SIGNAL(clicked(bool)), this, SLOT(info()));
    connect(settingsButton, SIGNAL(clicked(bool)), dial, SLOT(exec()));
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    for(int i = 0; i < dial->getSize(); ++i) {

        for(int j = 0; j < dial->getSize(); ++j) {

            QPushButton *button = new QPushButton(this);
            button->setFixedSize(90, 90);
            button->setStyleSheet("margin: 2px");
            button->show();
            grid->addWidget(button,i,j);

            _buttons.append(button);
            gridCoordinates.x = i;
            gridCoordinates.y = j;
            gridCoordinates.isSet = false;
            _coordinates.append(gridCoordinates);

            connect(button, SIGNAL(clicked(bool)), this, SLOT(Click()));
            connect(button, SIGNAL(clicked(bool)), this, SLOT(updateLabels()));
        }
    }

    connect(dial, SIGNAL(accepted()), this, SLOT(play()));  ///Connect


    main->addLayout(grid);
    setLayout(main);

}

void MyGrid::Click()
{

    QObject *senderObject = sender();

    QPushButton *senderButton = qobject_cast<QPushButton*>(senderObject);

    senderButton->setStyleSheet("QPushButton {background: lightgreen} ");
    _senders.append(senderButton);

    int ind = 0;
    for(int i = 0; i < _isQueen.size(); ++i) {

        if(_isQueen[i] == senderButton) {

            ind = i;
        }
    }

    if(_isQueen.contains(senderButton)) {

        _isQueen.remove(ind);
        _queens += 1;
        _steps += 1;
        senderButton->setStyleSheet("QPushButton {background: white} ");
    }
    else {
        _queens -= 1;
        _steps += 1;
        _isQueen.append(senderButton);

          ///Lerakás felvevés kérdését megoldani!!!!!

    }

    senderButton->setText(QString::number(getColumn(senderButton)) + QString::number(getRow(senderButton)));

       // for(int i = 0; i < _buttons.length(); ++i) {

           // _buttons[i]->setText(QString::number(_coordinates[i].x) + QString::number(_coordinates[i].y));
       // }
    //senderButton->setEnabled(false);

}

int MyGrid::getColumn(QPushButton *button) {

    for(int i = 0; i < _buttons.size(); ++i) {

        if(_buttons[i] == button) {

            return _coordinates[i].y;
        }
    }

}

int MyGrid::getRow(QPushButton *button) {

    for(int i = 0; i < _buttons.size(); ++i) {

        if(_buttons[i] == button) {

            return _coordinates[i].x;
        }
    }
}

void MyGrid::play()
{

    foreach(QPushButton* button, _buttons) {

        grid->removeWidget(button);
        delete button;
    }

    _buttons.clear();
    _coordinates.clear();
    _senders.clear();



    for(int i = 0; i < dial->getSize(); ++i) {

        for(int j = 0; j < dial->getSize(); ++j) {

            QPushButton *button = new QPushButton(this);
            button->setFixedSize(90, 90);
            button->show();
            button->setStyleSheet("margin : 2px");
            grid->addWidget(button, i, j);
            _buttons.append(button);
            gridCoordinates.x = i;
            gridCoordinates.y = j;
            _coordinates.append(gridCoordinates);
            this->setFixedHeight(dial->getSize() * 100 + 200);

            connect(button, SIGNAL(clicked(bool)), this, SLOT(Click()));
            connect(button, SIGNAL(clicked(bool)), this, SLOT(updateLabels()));

        }

    }

    _queens = dial->getSize();
    _steps = 0;
    updateLabels();

}

void MyGrid::info()
{

    QTextEdit *edit;
    edit = new QTextEdit;

    edit->setText(tr("A játék lényege, hogy egy nxn-es táblán helyezzünk le n királynőt úgy,"
                     " hogy azok a sakk szabályai szerint ne üssék egymást. "
                     "A tábla méretét a Beállítások menüben választhatjuk ki. Jó játékot!"));

    edit->setFixedSize(200, 200);
    edit->setWindowTitle(tr("Szabályok"));
    edit->show();
}

void MyGrid::updateLabels()
{

    queens->setText("A megmaradt királynők száma: " + QString::number(_queens));
    steps->setText("A lépések száma: " + QString::number(_steps));

    if(_queens <= 0) {

        foreach(QPushButton *button, _buttons) {
            button->setEnabled(false);
        }

        queens->setText("A megmaradt királynők száma: " + QString::number(0));
    }
}

bool MyGrid::isWin()
{

    if(_queens == 0) return true;

    return false;
}
