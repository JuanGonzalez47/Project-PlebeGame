#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QLabel>
#include <QVector>
#include <QPixmap>
#include <cstdlib>
#include <random>


int numRandom(int limiteInferior, int limiteSuperior) {
    // Asegurarse de que el límite inferior sea menor o igual al límite superior
    if (limiteInferior > limiteSuperior) {
        std::swap(limiteInferior, limiteSuperior);
    }

    // Crear un generador de números aleatorios con una semilla basada en el tiempo actual
    static std::mt19937 generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(limiteInferior, limiteSuperior);

    // Generar el número aleatorio dentro del rango especificado
    return distribution(generator);
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

    // Ajusta el tamaño de la escena
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 7200, 800);  // Cambia el ancho a 10000 unidades
    ui->graphicsView->setScene(scene);

    // Ajusta el tamaño del graphicsView para que sea grande en x
    ui->graphicsView->setFixedSize(1500 + 2 * ui->graphicsView->frameWidth(), 800+ 2 * ui->graphicsView->frameWidth());

    backGround();

    t_prota_shoot = new QTimer(this);
    t_prota_recharge= new QTimer(this);
    t_prota_throw=new QTimer(this);

    //arreglo para parar el timer del movimiento de los enemigos
    stop_timer_enemy=new bool[num_enemys];

    block_move=new bool();

    *block_move=false;

    setObstacles();

    setEnemys();

    moveEnemyRandom();


    sprite_prota = new sprite(":/sprite_prota2.png", 0, 0, 43, 52, 100, 400);

    sprite_prota->setScale(1.7);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(100, 400);

    marco = new prota(100, 400, 1000, 10, 20, sprite_prota, scene);
    moveView();

}





void MainWindow::backGround(){

    //fodo
    QPixmap sceImage(":/escenario.jpg");
    QPixmap scaled_esceImage = sceImage.scaled(sceImage.width() * 1.8,sceImage.height() *2);
    QGraphicsPixmapItem *sce = new QGraphicsPixmapItem(scaled_esceImage);

    scene->addItem(sce);
    sce->setPos(0,0);

    //carretera

    QPixmap roadImage(":/carretera.jpg");
    QPixmap scaled_roadImage=roadImage.scaled(roadImage.width() * 1.8,roadImage.height() * 2);
    QGraphicsPixmapItem *road = new QGraphicsPixmapItem(scaled_roadImage);

    scene->addItem(road);
    road->setPos(0,380);
}

void MainWindow::moveView(){
    ui->graphicsView->centerOn(sprite_prota);
}


void MainWindow::setEnemys(){

    for(unsigned int i=0;i<num_enemys;i++){

        int posy=490;
        int posx=numRandom(600,5500);

        QTimer *tim_ene=new QTimer(this);
        enemy *ene=new enemy(posx,posy,1,10,10,scene);
        enemys.push_back(ene);

        timer_enemy_move.push_back(tim_ene);

        stop_timer_enemy[i]=false;

    }
}


void MainWindow::moveEnemyRandom(){

    for(unsigned int i=0;i<enemys.size();i++){
        moveAndShootEnemy(enemys[i],i);
    }

}

void MainWindow::setObstacles(){

    obstacle1.load(":/obstaculo1.png");
    // obstacle2.load(":/obstaculo2.png");


    // Crear una arreglo de 4 pixmaps
    obstacles = new QPixmap[num_obstacle];

    // Inicializar cada entrada de la matriz con obstacle1

    for (unsigned int i = 0; i < num_obstacle; ++i) {
        obstacles[i] = obstacle1;
        obstacleItem = new QGraphicsPixmapItem(obstacles[i]);
        // Configurar la posición y escala
        obstacleItem->setScale(2);

        int posx=numRandom(600,6500);
        int posy=numRandom(280,700);

        for(unsigned int i=0;i<pos_obstacles_enemys.size();i+=2){

            if(posx<(pos_obstacles_enemys[i]+150) && posx>(pos_obstacles_enemys[i]-150)){

                if(numRandom(1,2)==1){
                    posy=pos_obstacles_enemys[i+1]+150;

                    if(posy>700){
                        posy=270;
                    }
                }else{
                    posy=pos_obstacles_enemys[i+1]-150;
                    if(posy<280){
                        posy=690;
                    }
                }
            }

        }
        pos_obstacles_enemys.push_back(posx);
        pos_obstacles_enemys.push_back(posy);

        obstacleItem->setPos(posx,posy);
        scene->addItem(obstacleItem);
        obstacleItems.push_back(obstacleItem);
    }

}



// prota
void MainWindow::rechargeProta(){

    t_prota_recharge = new QTimer(this);
    connect(t_prota_recharge, &QTimer::timeout, [=]() {

        marco->recharge(t_prota_recharge,block_move);
    });

    t_prota_recharge->start(60);

}

void MainWindow::shootProta()
{

    // Temporizador para la animación del personaje disparando
    t_prota_shoot = new QTimer(this);

    connect(t_prota_shoot, &QTimer::timeout, [=]() {
        marco->shoot(t_prota_shoot);
    });

    t_prota_shoot->start(60);

    // Actualiza el contador de balas del personaje
    marco->setCont_bullets();

    // Crea un nuevo sprite y temporizador para la bala
    sprite *bullet = new sprite(":bala_1.png", 0, 0, 100, 50, 400, 400); // Crea un nuevo sprite para la bala
    QTimer *bullet_timer = new QTimer(this); // Crea un nuevo temporizador para la bala

    // Configura la posición y escala de la bala
    bullet->setScale(0.3);

    int x_inicial=sprite_prota->getx()+100;
    int y_inicial=sprite_prota->gety()+24;

    bullet->setPos(x_inicial,y_inicial) ;
    // Agrega la bala a la escena o al contenedor correspondiente
    scene->addItem(bullet);

    // Conecta el temporizador de la bala
    connect(bullet_timer, &QTimer::timeout, [=]() {

        // Movimiento de la bala
        bullet->moveBy(10, 0);


        bool colli_enemy=false;
        bool delete_enemy=false;

        //verificar si choca con un enemigo
        for(unsigned int i=0;i<enemys.size();i++){

            if(bullet->collidesWithItem(enemys[i]->getSprite_rifle())){


                bullet_timer->stop();
                scene->removeItem(bullet);
                delete bullet;
                delete bullet_timer;
                colli_enemy=true;
                enemys[i]->setLife(1);

                if(enemys[i]->getLife()==0){
                    delete_enemy=true;
                    stop_timer_enemy[i]=true;
                    num_enemys--;


                }

                break;

            }

        }

        if(!colli_enemy){

            //verificar si choca  con un obstaculo
            for(unsigned int i=0;i<num_obstacle;i++){
                if(bullet->collidesWithItem(obstacleItems[i])){
                    bullet_timer->stop();
                    scene->removeItem(bullet);
                    delete bullet;
                    delete bullet_timer;
                    break;

                    //verifiar si se pasa de los limites
                }else if (bullet->pos().x() >7500 || (bullet->pos().x()-x_inicial)==1600) {

                    bullet_timer->stop();
                    scene->removeItem(bullet);
                    delete bullet;
                    delete bullet_timer;
                    break;
                }

            }

        }
    });

    bullet_timer->start(40);
}


//enemy



void MainWindow::shootEnemy(enemy *ene,QTimer *t_move){

    t_move->stop();
    QTimer *t_enemy_shoot = new QTimer(this);
    connect(t_enemy_shoot, &QTimer::timeout, [=]() {

        ene->shoot(t_move,t_enemy_shoot);

    });
    t_enemy_shoot->start(50);

    // Crea un nuevo sprite y temporizador para la bala
    sprite *bullet_enemy = new sprite(":bala_2.png", 0, 0, 47, 63, 400, 400); // Crea un nuevo sprite para la bala
    QTimer *bullet_enemy_timer = new QTimer(this); // Crea un nuevo temporizador para la bala

    // Configura la posición y escala de la bala
    bullet_enemy->setScale(0.3);
    int x_inicial=ene->getSprite_rifle()->getx()-20;
    bullet_enemy->setPos(ene->getSprite_rifle()->getx()-20, (ene->getSprite_rifle()->gety()+28));

    // Agrega la bala a la escena o al contenedor correspondiente
    scene->addItem(bullet_enemy);

    connect(bullet_enemy_timer, &QTimer::timeout, [=]() {


        // Movimiento de la bala
        bullet_enemy->moveBy(-10, 0);

        bool colli_prota=false;

        //verificar si choca con el protagonista

        if(bullet_enemy->collidesWithItem(sprite_prota)){
            bullet_enemy_timer->stop();
            scene->removeItem(bullet_enemy);
            delete bullet_enemy;
            delete bullet_enemy_timer;
            colli_prota=true;
            marco->setLife(1);
            if(marco->getLife()==0){



                QTimer *dead_prota_timer = new QTimer(this);
                *block_move=true;

                connect(dead_prota_timer, &QTimer::timeout, [=]() {

                    marco->dead(dead_prota_timer,block_move);

                });

                dead_prota_timer->start(100);

                //exit(EXIT_SUCCESS);
                //mostrar muerte

                //perdiste el juego
            }
        }


        if(!colli_prota) {

            //verificar si choca  con un obstaculo
            for(unsigned int i=0;i<num_obstacle;i++){
                if(bullet_enemy->collidesWithItem(obstacleItems[i])){
                    bullet_enemy_timer->stop();
                    scene->removeItem(bullet_enemy);
                    delete bullet_enemy;
                    delete bullet_enemy_timer;
                    break;

                    //verifiar si se pasa de los limites
                }else if (bullet_enemy->pos().x() < -10 || -(bullet_enemy->pos().x()-x_inicial)==1600) {

                    bullet_enemy_timer->stop();
                    scene->removeItem(bullet_enemy);
                    delete bullet_enemy;
                    delete bullet_enemy_timer;
                    break;
                }

            }
        }



    });

    bullet_enemy_timer->start(40);



}




void MainWindow::moveAndShootEnemy(enemy *ene,int i) {

    QTimer *timer_move=new QTimer(this);


    connect(timer_move, &QTimer::timeout, [=]() {

        ene->sumMovran();


        ene->moveUpEnemy();

        for(unsigned int i=0;i<num_obstacle;i++){

            if(ene->getSprite_rifle()->collidesWithItem(obstacleItems[i])){
                ene->setSpeed();
                break;
            }
        }


        if (ene->getMov_ran() == ene->getN_ran()) {

            if(ene->getSprite_rifle()->gety()<480){

                ene->setN_ran(numRandom(0, (ene->getSprite_rifle()->gety() - 280)) / abs(ene->getSpeed())) ;
            }
            else{

                ene->setN_ran(numRandom(0, (670-ene->getSprite_rifle()->gety())) / abs(ene->getSpeed()));

            }
            if(ene->getSprite_rifle()->gety()<=320 || ene->getSprite_rifle()->gety()>=640){
                ene->setSpeed();
                ene->setN_ran(10);
            }else if(numRandom(1,2)==1){

                ene->setSpeed();
            }

            shootEnemy(ene,timer_move);
            ene->setMovRan(-1);
        }
        if(stop_timer_enemy[i]){

            timer_move->stop();
            //mostrar muerte del enemigo
            QTimer *dead_enemy_timer = new QTimer(this);

            connect(dead_enemy_timer, &QTimer::timeout, [=]() {

                ene->deadEnemy(dead_enemy_timer);

            });

            dead_enemy_timer->start(70);
        }
    });

    timer_move->start(100);



}


void MainWindow::keyPressEvent(QKeyEvent *event) {

    if(!*block_move){
        t_prota_shoot->stop();
        t_prota_recharge->stop();
        t_prota_throw->stop();

        // Manejo del evento de tecla
        if (event->key() == Qt::Key_A) {

            verify_coli = false;
            cont_obstacle = 0;

            while (cont_obstacle < num_obstacle) {
                if (sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])) {
                    verify_coli = true;
                    break;
                }
                cont_obstacle++;
            }

            if (!verify_coli) {
                marco->moveLeft();
            } else {
                QPointF pos = obstacleItems[cont_obstacle]->pos();
                qreal x1 = pos.x();

                if (sprite_prota->getx() < x1 + 50) {
                    marco->moveLeft();
                } else {
                    sprite_prota->setSprite();
                    marco->moveRight();
                }
            }

        } else if (event->key() == Qt::Key_D) {

            verify_coli = false;
            cont_obstacle = 0;

            while (cont_obstacle < num_obstacle) {
                if (sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])) {
                    verify_coli = true;
                    break;
                }
                cont_obstacle++;
            }

            if (!verify_coli) {
                marco->moveRight();
            } else {
                QPointF pos = obstacleItems[cont_obstacle]->pos();
                qreal x1 = pos.x();

                if (sprite_prota->getx() > x1) {
                    marco->moveRight();
                } else {
                    sprite_prota->setSprite();
                    marco->moveLeft();
                }
            }

        } else if (event->key() == Qt::Key_W) {

            verify_coli = false;
            cont_obstacle = 0;

            while (cont_obstacle < num_obstacle) {
                if (sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])) {
                    verify_coli = true;
                    break;
                }
                cont_obstacle++;
            }

            if (!verify_coli) {
                marco->moveUp();
            } else {
                QPointF pos = obstacleItems[cont_obstacle]->pos();
                qreal y1 = pos.y();

                if (sprite_prota->gety() < y1 + 50) {
                    marco->moveUp();
                } else {
                    sprite_prota->setSprite();
                    marco->moveDown();
                }
            }

        } else if (event->key() == Qt::Key_S) {

            verify_coli = false;
            cont_obstacle = 0;

            while (cont_obstacle < num_obstacle) {
                if (sprite_prota->collidesWithItem(obstacleItems[cont_obstacle])) {
                    verify_coli = true;
                    break;
                }
                cont_obstacle++;
            }

            if (!verify_coli) {
                marco->moveDown();
            } else {
                QPointF pos = obstacleItems[cont_obstacle]->pos();
                qreal y1 = pos.y();

                if (sprite_prota->gety() > y1) {
                    marco->moveDown();
                } else {
                    sprite_prota->setSprite();
                    marco->moveUp();
                }
            }

        } else if (event->key() == Qt::Key_R) {

            *block_move=true;
            rechargeProta();

        } else if (event->key() == Qt::Key_Space) {
            *block_move=true;
            greande();

        } else if (event->key() == Qt::Key_Return) {
            shootProta();

        } else {
            QMainWindow::keyPressEvent(event);
        }

    }


}


void MainWindow::greande() {



    t_prota_throw = new QTimer(this);
    connect(t_prota_throw, &QTimer::timeout, [=]() {

        marco->launch(t_prota_throw,block_move);

    });

    t_prota_throw->start(80);



    // Crear una nueva granada
    sprite *grenade = new sprite(":/granada.png", 0, 0, 26, 24, sprite_prota->getx() + 7, sprite_prota->gety() + 8);
    grenade->setScale(2);
    grenade->setPos(sprite_prota->getx() + 60, sprite_prota->gety() + 8);

    // Agregar la granada a la escena
    scene->addItem(grenade);

    int y = sprite_prota->gety();
    int x = sprite_prota->getx();

    // Crear un nuevo temporizador para esta granada
    QTimer *timer_grenade = new QTimer(this);
    QTimer *timer_burst = new QTimer(this);

    connect(timer_grenade, &QTimer::timeout, [=]() {

        marco->throwGrenade(timer_grenade,timer_burst, y, x, grenade);

    });
    timer_grenade->start(50);


    sprite *burst=new sprite(":/explosion.png", 0, 0, 55,105,x+660,y-200);

    burst->setScale(3);

    scene->addItem(burst);

    burst->setPos(sprite_prota->getx()+660,sprite_prota->gety()-200);

    burst->setN_image(11);

    connect(timer_burst, &QTimer::timeout, [=]() {

        burst->setSprite();

        if(burst->getCont()==10){
            burst->setCont(0);
            timer_burst->stop();

            //verificar si choco con un enemigo
            for(unsigned int i=0;i<enemys.size();i++){

                if(burst->collidesWithItem(enemys[i]->getSprite_rifle())){

                    //quitarle toda la vida al enmigo

                    enemys[i]->setLife(enemys[i]->getLife());
                    stop_timer_enemy[i]=true;
                    num_enemys--;
                    break;
                }
            }
            scene->removeItem(burst);
            delete burst;
            delete timer_burst;
        }
    });


}


MainWindow::~MainWindow() {
    // Eliminar los enemigos
    for (enemy* ene : enemys) {
        delete ene;
    }
    enemys.clear();

    // Eliminar los temporizadores de movimiento de enemigos
    for (QTimer* timer : timer_enemy_move) {
        delete timer;
    }
    timer_enemy_move.clear();

    // Eliminar los obstáculos
    for (QGraphicsPixmapItem* obstacle : obstacleItems) {
        scene->removeItem(obstacle);
        delete obstacle;
    }
    obstacleItems.clear();

    delete[] obstacles; // Liberar la memoria del arreglo de QPixmap

    delete block_move;

    delete ui;
}
