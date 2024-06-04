# include "charac_Prota.h"
#include <QTimer>

prota::prota(qreal _x,qreal _y,int _life, int _bullets, int _speed,sprite *s_prota) : charac (_life,_bullets,_speed, _x,_y){
    sprite_prota=s_prota;
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

void prota::setCont_bullets(){

    cont_bullets++;

}

int prota::getCont_bullets(){

    return cont_bullets;

}

void prota::dead(){

    methodCharacter(sprite_prota);

}




