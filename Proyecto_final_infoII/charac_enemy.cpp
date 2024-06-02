# include "charac_enemy.h"

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


enemy::enemy(qreal _x,qreal _y,int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y), scene(_scene){



    sprite_enemy_rifle = new sprite(":/soldado_rifle.png", 0, 110, 85, 110,_x,_y);
    scene->addItem(sprite_enemy_rifle);  // Agregar el sprite a la escena
    sprite_enemy_rifle->setPos(_x,_y);
    timer = new QTimer(this);

}

void enemy::moveUpEnemy() {


    sprite_enemy_rifle->setAttributes(110,85,4);
    moveUpCharacter(sprite_enemy_rifle);

}

void enemy::moveDownEnemy(){

    sprite_enemy_rifle->setAttributes(110,85,4);
    moveDownCharacter(sprite_enemy_rifle);

}

void enemy::moveRihgtEnemy(){

    sprite_enemy_rifle->setAttributes(110,85,4);
    moveRightCharacter(sprite_enemy_rifle);

}

void enemy::moveLeftEnemy(){

    sprite_enemy_rifle->setAttributes(110,85,4);
    moveLeftCharacter(sprite_enemy_rifle);

}

void enemy::shootEnemy(){

    timer2->stop();

    timer = new QTimer(this);
    sprite_enemy_rifle->setAttributes(0,140,6);
    sprite_enemy_rifle->setCont(0);
    connect(timer, &QTimer::timeout, [=]() {

        methodCharacter( sprite_enemy_rifle);

        if( sprite_enemy_rifle->getCont()==5){
            sprite_enemy_rifle->setCont(0);
            timer->stop();
            timer2->start();
        }
    });

    timer->start(100);

}


void enemy::moveAndShoot() {
    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, [=]() {



        mov_ran++;
        moveUpEnemy();


        if (mov_ran == n_ran) {

            qDebug() << " n_ran :";
            qDebug() << n_ran;

            if(getY()<480){
                n_ran = (numRandom(0, (sprite_enemy_rifle->gety()-280)))/(abs(getSpeed()));

                qDebug() << " lim1 :";
                qDebug() << (sprite_enemy_rifle->gety()-280);
                qDebug() << " y :";
                qDebug() <<sprite_enemy_rifle->gety();
            }
            else{
                n_ran = (numRandom(0, (670-sprite_enemy_rifle->gety())))/(abs(getSpeed()));
                qDebug() << " lim2 :";
                qDebug() << (670-sprite_enemy_rifle->gety());
                qDebug() << " y :";
                qDebug() <<sprite_enemy_rifle->gety();
            }


            if(sprite_enemy_rifle->gety()<=320 || sprite_enemy_rifle->gety()>=640){
                setSpeed();
                n_ran=10;
            }else if(numRandom(1,2)==1){
                setSpeed();
            }
            shootEnemy();
            mov_ran=-1;
        }

    });

    timer2->start(100);
}

void enemy::deadEnemy(){

   /* timer = new QTimer(this);
     sprite_enemy_rifle->setAttributes(300,80,15);
    sprite_prota->setCont(0);
    connect(timer, &QTimer::timeout, [=]() {

        methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==14) timer->stop();
    });

    timer->start(60);*/


}
