#include "gridwidget.h"


GridWidget::GridWidget(QWidget *parent) : QWidget(parent)

{

    setWindowTitle("Királynők - Játék");
    setFixedSize(400-frameSize().width(), 600);

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

    dial = new SizeDialog;
    //end = new EndDialog;
    grid = new QGridLayout;
    main = new QVBoxLayout;
    labels = new QHBoxLayout;

    _buttons.clear();
    steps = 0;
    queens = dial->getSize();

    countS = new QLabel("A lépések száma: ", this);
    countS->setText(countS->text() + QString::number(steps));

    countQ = new QLabel("A megmaradt királynők száma: ", this);
    countQ->setText(countQ->text() + QString::number(queens));

    labels->addWidget(countS);
    labels->addWidget(countQ);

    main->addWidget(playButton);
    main->addWidget(aboutButton);
    main->addWidget(settingsButton);
    main->addWidget(exitButton);
    main->addLayout(labels);

    connect(playButton, SIGNAL(clicked(bool)), this, SLOT(play()));
    connect(aboutButton, SIGNAL(clicked(bool)), this, SLOT(info()));
    connect(settingsButton, SIGNAL(clicked(bool)), dial, SLOT(exec()));
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(dial, SIGNAL(accepted()), this, SLOT(play()));

    //connect(end)

    _buttons.clear();
    steps = 0;
    queens = dial->getSize();

    for(int i = 0; i < dial->getSize(); ++i) {

        for(int j = 0; j < dial->getSize(); ++j) {

            MyButton *button = new MyButton(Coordinate(i,j, false),this);
            grid->addWidget(button, i, j);
            _buttons.append(button);
            connect(button, SIGNAL(clicked(bool)), this, SLOT(click()));
            connect(button, SIGNAL(clicked(bool)), this, SLOT(updateLabels()));
        }
    }

    main->addLayout(grid);
    setLayout(main);

}

GridWidget::~GridWidget()
{

    delete end;
    delete dial;
}

void GridWidget::click()
{

    QObject *senderObject = sender();

    MyButton *senderButton = qobject_cast<MyButton*>(senderObject);
    int ind = 0;

    for(int i = 0; i < _queens.size(); ++i) {

        if(senderButton == _queens[i]) {

            ind = i;
        }
    }

    if(_queens.contains(senderButton)) {

        _queens.remove(ind);
        queens += 1;
        steps += 1;
        backQueen(senderButton->getCoordinate());
    }
    else {

        queens -= 1;
        steps += 1;
        _queens.append(senderButton);
        setQueen(senderButton->getCoordinate());
    }

    if(isWin()) {

        end = new EndDialog(steps);
        connect(end, SIGNAL(rejected()), this, SLOT(close()));
        connect(end, SIGNAL(accepted()), this, SLOT(play()));
        end->exec();
        end->deleteLater();
    }

}

void GridWidget::setQueen(Coordinate cord)
{

    foreach(MyButton *button, _buttons) {

        if(button->getCoordinate().x == cord.x || button->getCoordinate().y == cord.y ||
                qAbs(cord.x - button->getCoordinate().x) == qAbs(cord.y - button->getCoordinate().y)) {

            button->setEnabled(false);
            button->setStyleSheet("background : red");
        }

        if(cord.x == button->getCoordinate().x && cord.y == button->getCoordinate().y) {

            button->setEnabled(true);
            button->setStyleSheet("background : lightgreen");
           // button->getCoordinate().isQueen = true;
        }
    }
}

void GridWidget::backQueen(Coordinate cord)
{

    foreach(MyButton *button, _buttons) {

        if(cord.x == button->getCoordinate().x && cord.y == button->getCoordinate().y) {

            button->setStyleSheet("background : white");
        }

        if(button->getCoordinate().x == cord.x || button->getCoordinate().y == cord.y ||
                qAbs(cord.x - button->getCoordinate().x) == qAbs(cord.y - button->getCoordinate().y)) {

            button->setStyleSheet("background : white");
            button->setEnabled(true);
        }
    }

    foreach(MyButton *button, _queens) {

        setQueen(button->getCoordinate());
    }
}

void GridWidget::play()
{

    foreach(MyButton *button, _buttons) {

        grid->removeWidget(button);
        delete button;
    }

    _buttons.clear();
    _queens.clear();

    for(int i = 0; i < dial->getSize(); ++i) {

        for(int j = 0; j < dial->getSize(); ++j) {

            MyButton *button = new MyButton(Coordinate(i,j,false), this);
            grid->addWidget(button, i, j);
            _buttons.append(button);
            this->setFixedHeight(dial->getSize() * 100 + 200);

            connect(button, SIGNAL(clicked(bool)), this, SLOT(click()));
            connect(button, SIGNAL(clicked(bool)), this, SLOT(updateLabels()));
        }
    }

    steps = 0;
    queens = dial->getSize();
    updateLabels();


}

bool GridWidget::isWin()
{

    if(queens <= 0) {
        return true;
    }

    return false;
}

void GridWidget::info()
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

void GridWidget::updateLabels()
{

    countQ->setText("A megmaradt királynők száma: " + QString::number(queens));
    countS->setText("A lépések száma: " + QString::number(steps));

    if(queens <= 0) {

        foreach(MyButton *button, _buttons) {
            button->setEnabled(false);
        }

        countQ->setText("A megmaradt királynők száma: " + QString::number(0));
    }
}
