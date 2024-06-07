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



void prota::throwGrenade(QTimer *timer_grenade, QTimer *timer_burst,double y_inicial, double x_inicial, sprite *grenade) {


    grenade->moveParabolic(x_inicial,y_inicial);

  if (grenade->gety() > y_inicial) {

        // Detener el temporizador y eliminar la granada
        qDebug()<<grenade->getx();
        qDebug()<<grenade->gety();
        grenade->setCont(0);
        timer_grenade->stop();
        scene->removeItem(grenade);
        delete grenade;
        delete timer_grenade;

        timer_burst->start(50);
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




