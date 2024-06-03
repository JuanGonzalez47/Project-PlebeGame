#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>
#include <cstdlib>
#include <ctime>

int numRandom(int limiteInferior, int limiteSuperior) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr))); // Inicializa la semilla una sola vez
        seeded = true;
    }
    int random_number = limiteInferior + rand() % (limiteSuperior - limiteInferior + 1);
    return random_number;
}

int abs(int num) {
    if (num < 0) {
        return -num; // Si el valor es negativo, devuelve su negativo
    }
    return num; // Si el valor es positivo o cero, lo devuelve tal cual
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1500, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1500+2* ui->graphicsView->frameWidth(),800+2* ui->graphicsView->frameWidth());

    QPixmap backgroundImage(":/escena_final2.png");
    //scene->addPixmap(backgroundImage);

    // Escalar la imagen de fondo (por ejemplo, 3x en X y 2x en Y)
    QPixmap scaledBackgroundImage = backgroundImage.scaled(
        backgroundImage.width() * 1.45,
        backgroundImage.height() * 2,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    // Crear un QGraphicsPixmapItem con la imagen escalada
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(scaledBackgroundImage);

    // Agregar el QGraphicsPixmapItem a la escena
    scene->addItem(background);
    background->setPos(0, 170);

   // fondo();

    marco=new prota(400,400,10,10,10,scene);



}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::fondo(){

    QPixmap backgroundImage(":/escena_final2.png");
    //scene->addPixmap(backgroundImage);

    // Escalar la imagen de fondo (por ejemplo, 3x en X y 2x en Y)
    QPixmap scaledBackgroundImage = backgroundImage.scaled(
        backgroundImage.width() * 1.45,
        backgroundImage.height() * 2,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    // Crear un QGraphicsPixmapItem con la imagen escalada
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(scaledBackgroundImage);

    // Agregar el QGraphicsPixmapItem a la escena
    scene->addItem(background);
    background->setPos(0, 170);

}

// prota
void MainWindow::rechargeProta(){

    qDebug("NOOOOO");
    t_prota_recharge = new QTimer(this);
      qDebug("1");
    sprite_prota->setAttributes(200,115,10);
       qDebug("2");
    sprite_prota->setCont(0);
     qDebug("3");

    connect(t_prota_recharge, &QTimer::timeout, [=]() {

        marco->methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==9) t_prota_recharge->stop();
    });

    t_prota_recharge->start(60);

}

void MainWindow::shootProta()
{
    t_prota_shoot = new QTimer(this);
    sprite_prota->setAttributes(100,120,4);
    sprite_prota->setCont(0);
    connect( t_prota_shoot, &QTimer::timeout, [=]() {

        marco->methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==3)  t_prota_shoot->stop();

    });

    t_prota_shoot->start(60);
}

//enemy

void MainWindow::shootEnemy(enemy *ene){

    t_enemy_move->stop();

    t_enemy_shoot = new QTimer(this);
    sprite_enemy_rifle->setAttributes(0,140,6);
    sprite_enemy_rifle->setCont(0);
    connect(t_enemy_shoot, &QTimer::timeout, [=]() {

        ene->methodCharacter( sprite_enemy_rifle);

        if( sprite_enemy_rifle->getCont()==5){
            sprite_enemy_rifle->setCont(0);
            t_enemy_shoot->stop();
            t_enemy_move->start();
        }
    });

    t_enemy_shoot->start(100);
}


void MainWindow::moveAndShootEnemy(enemy *ene) {

    t_enemy_move = new QTimer(this);
    connect(t_enemy_move, &QTimer::timeout, [=]() {

        ene->setMovRan();
        ene->moveUpEnemy();

        if (ene->getMov_ran() == ene->getN_ran()) {

            if(sprite_enemy_rifle->gety()<480){
                ene->setN_ran(numRandom(0, (sprite_enemy_rifle->gety() - 280)) / abs(ene->getSpeed())) ;
            }
            else{

                ene->setN_ran(numRandom(0, (670-sprite_enemy_rifle->gety())) / abs(ene->getSpeed()));
            }
            if(sprite_enemy_rifle->gety()<=320 || sprite_enemy_rifle->gety()>=640){
                ene->setSpeed();
                ene->setN_ran(10);
            }else if(numRandom(1,2)==1){
                ene->setSpeed();
            }
            ene->shootEnemy();
            ene->setMovRan();
        }

    });

    t_enemy_move->start(100);
}






void MainWindow::keyPressEvent(QKeyEvent *event){

    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:

        marco->moveLeft();

        break;
    case Qt::Key_D:

       marco->moveRihgt();

        break;
    case Qt::Key_W:

        marco->moveUp();

        break;

    case Qt::Key_S:

       marco->moveDown();

        break;

    case Qt::Key_R:

        rechargeProta();

        break;

    case Qt::Key_Return:

        shootProta();


        break;

    default:

        QMainWindow::keyPressEvent(event);
    }

}


