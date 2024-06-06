#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QLabel>
#include <QVector>
#include <QPixmap>
#include <cstdlib>
#include <cstdlib>


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

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1500, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1500+2* ui->graphicsView->frameWidth(),800+2* ui->graphicsView->frameWidth());


    backGround();


    t_prota_shoot = new QTimer(this);

    sprite_prota = new sprite(":/sprite_prota2.png", 0, 0, 43, 52,100,400);

    sprite_prota->setScale(2);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena    
    sprite_prota->setPos(100,400);


    marco=new prota(100,400,10,10,10,sprite_prota,scene);

    setEnemys();

    setObstacles();

    moveEnemyRandom();


}




void MainWindow::backGround(){



    QPixmap backgroundImage(":/escena_final2.png");
    //scene->addPixmap(backgroundImage);

    // Escalar la imagen de fondo (por ejemplo, 3x en X y 2x en Y)
    QPixmap scaledBackgroundImage = backgroundImage.scaled(
        backgroundImage.width() * 3,
        backgroundImage.height() * 2,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    // Crear un QGraphicsPixmapItem con la imagen escalada
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(scaledBackgroundImage);

    // Agregar el QGraphicsPixmapItem a la escena
    scene->addItem(background);
    background->setPos(0,0);


}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setEnemys(){

    for(unsigned int i=0;i<num_enemys;i++){

        enemy *ene=new enemy(numRandom(800,1400),numRandom(200,660),4,10,10,scene);
        enemys.push_back(ene);

    }

}

void MainWindow::moveEnemyRandom(){

    for(unsigned int i=0;i<num_enemys;i++){
        moveAndShootEnemy(enemys[i]);
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
        obstacleItem->setScale(2.5);
        obstacleItem->setPos(700,300+180*i);  // Mover la posición para que no se superpongan
        scene->addItem(obstacleItem);
        obstacleItems.push_back(obstacleItem);
    }

}



// prota
void MainWindow::rechargeProta(){

    t_prota_recharge = new QTimer(this);
    connect(t_prota_recharge, &QTimer::timeout, [=]() {

        marco->recharge(t_prota_recharge);
    });

    t_prota_recharge->start(60);

}

void MainWindow::shootProta(prota *prot)
{

    // Temporizador para la animación del personaje disparando
    t_prota_shoot = new QTimer(this);

    connect(t_prota_shoot, &QTimer::timeout, [=]() {
        marco->shoot(t_prota_shoot);
    });

    t_prota_shoot->start(60);

    // Actualiza el contador de balas del personaje
    prot->setCont_bullets();

    // Crea un nuevo sprite y temporizador para la bala
    sprite *bullet = new sprite(":bala_1.png", 0, 0, 100, 50, 400, 400); // Crea un nuevo sprite para la bala
    QTimer *bullet_timer = new QTimer(this); // Crea un nuevo temporizador para la bala

    // Configura la posición y escala de la bala
    bullet->setScale(0.3);
    bullet->setPos(sprite_prota->getx()+70, sprite_prota->gety()+8);

    // Agrega la bala a la escena o al contenedor correspondiente
    scene->addItem(bullet);

    // Conecta el temporizador de la bala
    connect(bullet_timer, &QTimer::timeout, [=]() {


        // Movimiento de la bala
        bullet->moveBy(10, 0);


        bool colli_enemy=false;

        //verificar si choca con un enemigo
        for(unsigned int i=0;i<num_enemys;i++){
            if(bullet->collidesWithItem(enemys[i]->getSprite_rifle())){
                bullet_timer->stop();
                scene->removeItem(bullet);
                delete bullet;
                delete bullet_timer;
                colli_enemy=true;
                enemys[i]->setLife(1);

                if(enemys[i]->getLife()==0){

                    //quitar enemigo de la escena
                    scene->removeItem(enemys[i]->getSprite_rifle());
                    delete enemys[i];

                    //se utiliza para poder eliminar el enemigo del vecotr utilizando erase
                    size_t index_remove = static_cast<size_t>(i);
                    //eliminar el enemigo y que el resto queden contiguos en el vector
                    enemys.erase(enemys.begin() + index_remove);

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
                }else if (bullet->pos().x() > 1500 || bullet->pos().x()<-10) {

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
    t_enemy_shoot->start(130);

    // Crea un nuevo sprite y temporizador para la bala
    sprite *bullet_enemy = new sprite(":bala_1.png", 0, 0, 100, 50, 400, 400); // Crea un nuevo sprite para la bala
    QTimer *bullet_enemy_timer = new QTimer(this); // Crea un nuevo temporizador para la bala

    // Configura la posición y escala de la bala
    bullet_enemy->setScale(0.3);
    bullet_enemy->setPos(ene->getSprite_rifle()->getx(), (ene->getSprite_rifle()->gety()));

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

                exit(EXIT_SUCCESS);
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
                }else if (bullet_enemy->pos().x() > 1500 || bullet_enemy->pos().x() < -10) {

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




void MainWindow::moveAndShootEnemy(enemy *ene) {

    QTimer *t_enemy_move = new QTimer(this);

    connect(t_enemy_move, &QTimer::timeout, [=]() {

        ene->sumMovran();
        ene->moveUpEnemy();

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

           shootEnemy(ene,t_enemy_move);
            ene->setMovRan(-1);
        }

    });

    t_enemy_move->start(100);
}


void MainWindow::keyPressEvent(QKeyEvent *event){

    t_prota_shoot->stop();

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



            if(sprite_prota->getx()<x1+50){
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

       shootProta(marco);

    default:

        QMainWindow::keyPressEvent(event);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Crear una nueva granada
    sprite *grenade = new sprite(":/granada.png", 0, 0, 26, 24, sprite_prota->getx() + 7, sprite_prota->gety() + 8);
    grenade->setScale(2);
    grenade->setPos(sprite_prota->getx() + 7, sprite_prota->gety() + 8);

    // Agregar la granada a la escena
    scene->addItem(grenade);

    int y = marco->getY();
    int x = marco->getX();

    // Crear un nuevo temporizador para esta granada
    QTimer *timer_grenade = new QTimer(this);
    connect(timer_grenade, &QTimer::timeout, [=]() {
            marco->throwGrenade(timer_grenade, y, x, grenade);
        });

    timer_grenade->start(50);
}

