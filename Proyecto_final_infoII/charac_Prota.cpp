# include "charac_Prota.h"
#include <QTimer>

prota::prota(qreal _x,qreal _y,int _life, int _bullets, int _speed,sprite *s_prota,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y){

    scene=_scene;
    sprite_prota=s_prota;
}

void prota::moveUp() {

    sprite_prota->setAttributes(0,43,4);
    moveUpCharacter(sprite_prota);
}

void prota::moveDown(){


 sprite_prota->setAttributes(0,43,4);
    moveDownCharacter(sprite_prota);

}

void prota::moveRihgt(){

    sprite_prota->setAttributes(0,43,4);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeft(){

   sprite_prota->setAttributes(0,43,4);
    moveLeftCharacter(sprite_prota);
}



void prota::throwGrenade(QTimer *timer_grenade, double y_inicial, double x_inicial, sprite *grenade) {

    float Voy = 50;
    float g = 9.8;
    float Vox = 60;

    t +=0.2;

    // Calcular nuevas posiciones
    double new_y = y_inicial - Voy * t + (0.5 * g * t * t);
    double new_x = x_inicial + Vox * t;

    grenade->setPos(new_x, new_y);

    int z=(40/t);

    if(z%2!=0){
        grenade->setSprite();
    }

    grenade->setSprite();

    if (new_y > y_inicial) {
        // Detener el temporizador y eliminar la granada
        timer_grenade->stop();
        scene->removeItem(grenade);
        delete grenade;
        delete timer_grenade;
    }
}



void prota::shoot(QTimer *t_prota_shoot){


    sprite_prota->setAttributes(53,64,5);
    methodCharacter(sprite_prota);
    if(sprite_prota->getCont() == 4) {
        sprite_prota->setCont(0);
        t_prota_shoot->stop();
    }
}






void prota::recharge(QTimer* t_prota_recharge){


    sprite_prota->setAttributes(106,47,10);
    methodCharacter(sprite_prota);
    if(sprite_prota->getCont()==9){
         sprite_prota->setCont(0);
        t_prota_recharge->stop();
    }
}

void prota::setCont_bullets(){

    cont_bullets++;

}

int prota::getCont_bullets(){

    return cont_bullets;

}

int prota::getY(){

    return sprite_prota->gety();

}

int prota::getX()
{
    return sprite_prota->getx();
}

void prota::dead(){

    methodCharacter(sprite_prota);

}




