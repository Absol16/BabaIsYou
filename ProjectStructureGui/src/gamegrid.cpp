#include "gamegrid.h"
#include <QLabel>
#include <QString>
#include <QPixmap>

GameGrid::GameGrid(Level* model, QWidget* parent) : QWidget(parent) {
    this->model = model;
    gridLayout = new QGridLayout(this);
    gameOverWidget = new QWidget;
    gridLayout->setSpacing(0);   // Définit l'espacement entre les éléments à 0
    gridLayout->parentWidget()->setStyleSheet("background-color: black;");
}

void GameGrid::showGame() {
    model->startUi();
    this->setObjects();
}

void GameGrid::showSaveGame() {
    this->model->IsSave();
    model->startUi();
    this->model->IsSave();
    this->setObjects();
}

void GameGrid::gameOver() {
    clearGrid();

    QLabel* over = new QLabel;
    over->setText("Game is Over");
    over->setStyleSheet("font-size: 30px;"
                        "font-weight: bold; "
                        "color: black;");

    QPushButton* playAgain = new QPushButton("Play Again");
    connect(playAgain, &QPushButton::clicked, this, &GameGrid::startAgain);

    QPushButton* quit = new QPushButton("Quit");
    connect(quit, &QPushButton::clicked, this, &GameGrid::quit);
    applyButtonStyle(playAgain, "#4CAF50");
    applyButtonStyle(quit, "#f44336");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(over);
    layout->addWidget(playAgain);
    layout->addWidget(quit);

    gameOverWidget->setLayout(layout);
    gameOverWidget->show();
}


void GameGrid::setObjects() {
    clearGrid();
    vector<vector<vector<ObjectGame>>> objGame = this->model->getBoard().getTabBoard();
    for (int row = 0; row < objGame.size(); ++row) {
        for (int col = 0; col < objGame[0].size(); ++col) {
            for (auto& objectGame : objGame[row][col]) {
                placeObject(objectGame,row,col);
            }
        }
    }
}

void GameGrid::placeObject(ObjectGame objectGame,int row,int col){

    Material material = objectGame.getTypeObject();
    string nameMats = MaterialUtils::materialToString(objectGame.getTypeObject());
    QLabel* label = new QLabel(this);
    label->setText(QString::fromStdString(nameMats));
    QPixmap pixmap;

    if (material == Material::BABA) {
        pixmap.load(":/img/baba.png");
    } else if (material == Material::FLAG) {
        pixmap.load(":/img/flag.png");
    } else if (material == Material::ROCK) {
        pixmap.load(":/img/rock.png");
    } else if (material == Material::WALL) {
        pixmap.load(":/img/wall.png");
    } else if (material == Material::WATER) {
        pixmap.load(":/img/water.png");
    } else if (material == Material::METAL) {
        pixmap.load(":/img/metal.PNG");
    } else if (material == Material::GRASS) {
        pixmap.load(":/img/grass.png");
    } else if (material == Material::LAVA) {
        pixmap.load(":/img/lava.png");
    } else if (material == Material::NOTHING) {
        pixmap.load(":/img/nothing.png");
    } else if (material == Material::ASPECT_YOU) {
        pixmap.load(":/img/you.png");
    } else if (material == Material::ASPECT_WALL) {
        pixmap.load(":/img/wallText.png");
    } else if (material == Material::ASPECT_BABA) {
        pixmap.load(":/img/babaText.png");
    } else if (material == Material::ASPECT_KILL) {
        pixmap.load(":/img/killText.png");
    } else if (material == Material::ASPECT_WIN) {
        pixmap.load(":/img/winText.png");
    } else if (material == Material::ASPECT_IS) {
        pixmap.load(":/img/is.png");
    } else if (material == Material::ASPECT_ROCK) {
        pixmap.load(":/img/rockText.png");
    } else if (material == Material::ASPECT_PUSH) {
        pixmap.load(":/img/push.png");
    } else if (material == Material::ASPECT_STOP) {
        pixmap.load(":/img/stopText.png");
    } else if (material == Material::ASPECT_SINK) {
        pixmap.load(":/img/sinkText.png");
    } else if (material == Material::ASPECT_LAVA) {
        pixmap.load(":/img/lavaText.png");
    } else if (material == Material::ASPECT_WATER) {
        pixmap.load(":/img/waterText.png");
    } else if (material == Material::ASPECT_BEST) {
        pixmap.load(":/img/bestText.png");
    } else if (material == Material::ASPECT_FLAG) {
        pixmap.load(":/img/flagText.png");
    }
    // Ajuster la taille de l'image
    pixmap = pixmap.scaled(QSize(30, 30));
    // Définir la pixmap comme image du QLabel
    label->setPixmap(pixmap);
    gridLayout->addWidget(label, col, row);
}

void GameGrid::clearGrid() {
    // Supprime les widget de la grille
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void GameGrid::quit(){
    exit(0);
}

void GameGrid::startAgain(){
    gameOverWidget->hide();
    int lvl = 0;
    model->setLevel(lvl);
    this->model->startUi();
}

void GameGrid::updateUi() {
    // Clear the grid layout
    clearGrid();
    this->model->getBoard().checkBuildRule();
    if(model->getBoard().gameIsLoose()){
        model->getBoard().clearRule();
        model->startUi();
    }
    if(!this->model->getBoard().gameIsWin()){
        setObjects();
    }else{
        if(model->getLevel()<4){
            model->getBoard().clearRule();
            model->upLevel();
            model->startUi();
        }else{
            gameOver();
        }
    }
}

void GameGrid::applyButtonStyle(QPushButton* button, const QString& backgroundColor) {
    button->setStyleSheet("padding: 10px 20px;"
                          "font-size: 18px;"
                          "font-weight: bold;"
                          "background-color: " + backgroundColor + ";"
                                                                   "color: white;"
                                                                   "border-radius: 5px;");
}

