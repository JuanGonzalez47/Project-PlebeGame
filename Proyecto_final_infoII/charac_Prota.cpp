# include "charac_Prota.h"
#include <QTimer>
prota::prota(qreal _x,qreal _y,int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y), scene(_scene){

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 98,_x,_y);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(_x,_y);
    timer = new QTimer(this);
}

void prota::moveUpProta() {

    sprite_prota->setAttributes(0,110,10);
    moveUpCharacter(sprite_prota);
}

void prota::moveDownProta(){

    sprite_prota->setAttributes(0,110,10);
    moveDownCharacter(sprite_prota);

}

void prota::moveRihgtProta(){

    sprite_prota->setAttributes(0,110,10);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeftProta(){

    sprite_prota->setAttributes(0,110,10);
    moveLeftCharacter(sprite_prota);
}

void prota::shootProta(){

    timer = new QTimer(this);
    sprite_prota->setAttributes(100,120,4);
    sprite_prota->setCont(0);
    connect(timer, &QTimer::timeout, [=]() {

        methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==3) timer->stop();
    });

    timer->start(60);

}

void prota::rechargeProta(){


    timer = new QTimer(this);
    sprite_prota->setAttributes(200,115,10);
    sprite_prota->setCont(0);
    connect(timer, &QTimer::timeout, [=]() {

        methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==9) timer->stop();
    });

    timer->start(60);

}

void prota::deadProta(){

    timer = new QTimer(this);
    sprite_prota->setAttributes(300,80,15);
    sprite_prota->setCont(0);
    connect(timer, &QTimer::timeout, [=]() {

        methodCharacter(sprite_prota);
        if(sprite_prota->getCont()==14) timer->stop();
    });

    timer->start(60);


}




