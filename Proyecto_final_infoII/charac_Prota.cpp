# include "charac_Prota.h"
#include <QTimer>
prota::prota(qreal _x,qreal _y,int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y), scene(_scene){

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 98,_x,_y);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(_x,_y);
}

void prota::moveUp() {

    sprite_prota->setAttributes(0,110,10);
    moveUpCharacter(sprite_prota);
}

void prota::moveDown(){

    sprite_prota->setAttributes(0,110,10);
    moveDownCharacter(sprite_prota);

}

void prota::moveRihgt(){

    sprite_prota->setAttributes(0,110,10);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeft(){

    sprite_prota->setAttributes(0,110,10);
    moveLeftCharacter(sprite_prota);
}

void prota::shoot(){

    methodCharacter(sprite_prota);
}

void prota::recharge(){

    methodCharacter(sprite_prota);

}

void prota::dead(){

    methodCharacter(sprite_prota);

}




