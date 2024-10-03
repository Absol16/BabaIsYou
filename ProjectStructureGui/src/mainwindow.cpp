#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Level *facade,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _scene (this),
    game (facade)
{
    game->setLevel(0);
    gameGrid = new GameGrid(game, parent);
    game->addObserver(*gameGrid);
    initUI();
}

void  MainWindow::hideMenu(){

    ui->startButton->hide();
    ui->saveButton->hide();
    ui->label->hide();

    ui->down->show();
    ui->up->show();
    ui->right->show();
    ui->left->show();
    ui->restart->show();
    gameGrid->show();
}

void MainWindow::applyButtonStyle(QPushButton* button, const QString& backgroundColor) {
    button->setStyleSheet("padding: 10px 20px;"
                          "font-size: 18px;"
                          "font-weight: bold;"
                          "background-color: " + backgroundColor + ";"
                                                                   "color: white;"
                                                                   "border-radius: 5px;");
}

void MainWindow::initUI() {

    ui->setupUi(this);
    ui->myGraphicsView->setStyleSheet("background-color: black;");
    ui->label->setStyleSheet("font-size: 30px; font-weight: bold; color: white;");

    connectAllSlot();
    applyButtonStyle(ui->startButton, "#4CAF50");
    applyButtonStyle(ui->saveButton, "#f44336");

    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget();
    proxyWidget->setWidget(gameGrid);

    ui->myGraphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
    QRect viewContentsRect = ui->myGraphicsView->contentsRect();
    _scene.setSceneRect(viewContentsRect);
    ui->myGraphicsView->setScene(&_scene);
    _scene.addItem(proxyWidget);
    setCentralWidget(ui->centralwidget);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
    // Logique de gestion des événements ici
    return QMainWindow::eventFilter(object, event);
}

void MainWindow::connectAllSlot(){
    ui->down->hide();
    ui->up->hide();
    ui->right->hide();
    ui->left->hide();
    ui->restart->hide();

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::hideMenu);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::hideMenu);


    connect(ui->saveButton, &QPushButton::clicked, gameGrid, &GameGrid::showSaveGame);
    connect(ui->startButton, &QPushButton::clicked, gameGrid, &GameGrid::showGame);
    connect(ui->left, SIGNAL(clicked()),SLOT(leftClicked()));
    connect(ui->right, SIGNAL(clicked()),SLOT(rightClicked()));
    connect(ui->up, SIGNAL(clicked()),SLOT(upClicked()));
    connect(ui->down, SIGNAL(clicked()),SLOT(downClicked()));
    connect(ui->restart, SIGNAL(clicked()),SLOT(restartClicked()));
}


void MainWindow::leftClicked()
{
    Direction direction = Direction::LEFT;
    game->movementUi(direction);
}

void MainWindow::rightClicked()
{
    Direction direction = Direction::RIGHT;
    game->movementUi(direction);
}

void MainWindow::upClicked()
{
    Direction direction = Direction::UP;
    game->movementUi(direction);
}

void MainWindow::downClicked()
{
    Direction direction = Direction::DOWN;
    game->movementUi(direction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restartClicked()
{
    int lvl = game->getLevel();
    game->setLevel(lvl);
    game->startUi();
}
