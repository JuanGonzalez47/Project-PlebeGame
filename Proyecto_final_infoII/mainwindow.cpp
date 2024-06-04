#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QLabel>
#include <QVector>
#include <QPixmap>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 98,100,400);

    sprite_prota->setScale(0.8);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena    
    sprite_prota->setPos(100,400);

    sprite_enemy_rifle = new sprite(":/soldado_rifle.png", 0, 110, 85, 110,1000,400);

    sprite_enemy_rifle->setScale(0.8);
    scene->addItem(sprite_enemy_rifle);  // Agregar el sprite a la escena
    sprite_enemy_rifle->setPos(1000,400);


    marco=new prota(100,400,10,10,10,sprite_prota);

    ene=new enemy(1000,400,10,10,10,sprite_enemy_rifle);

    moveAndShootEnemy(ene);


   /* sprite_bullet = new sprite*[4];


    for (int i = 0; i < 4; ++i) {
        sprite_bullet[i] = new sprite(":bala_1.png", 0, 0, 100, 50, 400, 400);
        scene->addItem(sprite_bullet[i]);
    }

    scene->addItem(sprite_bullet[0]);

    timer_bullets = new QTimer*[4];


    for (int i = 0; i < 4; ++i) {
        timer_bullets[i] = new QTimer();
    }*/


    obstacle1.load(":/obstaculo1.png");
    // obstacle2.load(":/obstaculo2.png");


    // Crear una arreglo de 4 pixmaps
    obstacles = new QPixmap[num_obstacle];

    // Inicializar cada entrada de la matriz con obstacle1

    for (unsigned int i = 0; i < num_obstacle; ++i) {
        obstacles[i] = obstacle1;
        obstacleItem = new QGraphicsPixmapItem(obstacles[i]);
        // Configurar la posición y escala
        obstacleItem->setScale(2.5);
        obstacleItem->setPos(700,300+180*i);  // Mover la posición para que no se superpongan
        scene->addItem(obstacleItem);
        obstacleItems.push_back(obstacleItem);
    }


}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::setObstacles(){


    obstacle1.load(":/obstaculo1.png");
    // obstacle2.load(":/obstaculo2.png");

    for (unsigned int i = 0; i < 5; ++i) {

        obstacles[i]=obstacle1;
    }

    for (int i = 0; i < 4; ++i) {

        obstacleItem = new QGraphicsPixmapItem(obstacles[i]);
        // Configura la posición y escala
        obstacleItem->setScale(2.5);
        obstacleItem->setPos(200, 200);
        scene->addItem(obstacleItem);

    }

}



// prota
void MainWindow::rechargeProta(){

    t_prota_recharge = new QTimer(this);
    sprite_prota->setAttributes(200,115,10);
    sprite_prota->setCont(0);
    connect(t_prota_recharge, &QTimer::timeout, [=]() {

        marco->methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==9) t_prota_recharge->stop();
    });

    t_prota_recharge->start(60);

}

/*void MainWindow::shootProta(prota *prot)
{
    t_prota_shoot = new QTimer(this);
    sprite_prota->setAttributes(100,120,4);
    sprite_prota->setCont(0);
    connect( t_prota_shoot, &QTimer::timeout, [=]() {

        marco->methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==3)  t_prota_shoot->stop();

    });

    t_prota_shoot->start(60);

    prot->setCont_bullets();


    // Crea un nuevo temporizador para la bala
    timer_bullets[prot->getCont_bullets()] = new QTimer(this);


    // Configura la posición y escala de la bala
    sprite_bullet[prot->getCont_bullets()]->setScale(0.5);
    sprite_bullet[prot->getCont_bullets()]->setPos(sprite_prota->getx(), sprite_prota->gety());

    // Conecta el temporizador de la bala
    connect(timer_bullets[prot->getCont_bullets()], &QTimer::timeout, [=] {
        // movimiento de la bala
        sprite_bullet[prot->getCont_bullets()]->moveImage(10, 0);

    });
    // Inicia el temporizador de la bala
    timer_bullets[prot->getCont_bullets()]->start(40);


}*/

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

        ene->sumMovran();
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

           shootEnemy(ene);
            ene->setMovRan(-1);
        }

    });

    t_enemy_move->start(100);
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:


        verify_coli=false;

        cont_obstacle=0;

        while(cont_obstacle<num_obstacle){

            if(sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])){

                verify_coli=true;
                break;
            }
            cont_obstacle++;
        }



        if(!verify_coli){

            marco->moveLeft();

        }else{
            QPointF pos=obstacleItems[cont_obstacle]->pos();

            qreal x1 = pos.x(); // Coordenada y



            if(sprite_prota->gety()<x1+50){
                marco->moveLeft();

            }else{
                sprite_prota->setSprite();
                marco->moveRihgt();


            }

        }


        break;
    case Qt::Key_D:



        verify_coli=false;

        cont_obstacle=0;

        while(cont_obstacle<num_obstacle){

            if(sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])){

                verify_coli=true;
                break;
            }
            cont_obstacle++;
        }



        if(!verify_coli){

            marco->moveRihgt();

        }else{

            QPointF pos=obstacleItems[cont_obstacle]->pos();

            qreal x1 = pos.x(); // Coordenada y


            if(sprite_prota->getx()>x1){
                marco->moveRihgt();

            }else{
                sprite_prota->setSprite();
                marco->moveLeft();


            }

        }

        break;


    case Qt::Key_W:



        verify_coli=false;

        cont_obstacle=0;

        while(cont_obstacle<num_obstacle){

            if(sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])){

                verify_coli=true;
                break;
            }
            cont_obstacle++;
        }



        if(!verify_coli){

            marco->moveUp();

        }else{
            QPointF pos=obstacleItems[cont_obstacle]->pos();

            qreal y1 = pos.y(); // Coordenada y



            if(sprite_prota->gety()<y1+50){
                marco->moveUp();

            }else{
                sprite_prota->setSprite();
                marco->moveDown();


            }

        }



        break;

    case Qt::Key_S:



        verify_coli=false;

        cont_obstacle=0;

        while(cont_obstacle<num_obstacle){

            if(sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])){

                verify_coli=true;
                break;
            }
            cont_obstacle++;
        }



        if(!verify_coli){

            marco->moveDown();

        }else{
            QPointF pos=obstacleItems[cont_obstacle]->pos();

            qreal y1 = pos.y(); // Coordenada y


            if(sprite_prota->gety()>y1){
                marco->moveDown();

            }else{
                sprite_prota->setSprite();
                marco->moveUp();


            }

        }




       break;

    case Qt::Key_R:

        rechargeProta();

        break;

    case Qt::Key_Return:

       // shootProta(marco);

        bullet();

        break;

    default:

        QMainWindow::keyPressEvent(event);
    }

}


void MainWindow::bullet(){


    sprite_bullet=new sprite(":bala_1.png", 0, 0, 100, 50, 400, 400);

    sprite_bullet->setPos(sprite_prota->pos());

    scene->addItem(sprite_bullet);

    bullet_timer = new QTimer(this);

    connect(bullet_timer, &QTimer::timeout, [=]() {

        sprite_bullet->moveImage(10,0);
    });

    bullet_timer ->start(50);
}


