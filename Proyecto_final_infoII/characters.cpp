
#include "characters.h"


charac::charac(int _life,int _bullets,int _speed,qreal _x,qreal _y){



    x=_x;
    y=_y;
    life=_life;
    bullets=_bullets;
    speed=_speed;

}

charac::charac(){
    //inicializar constructor por defecto

}


void charac::methodCharacter(sprite *method){

    method->setSprite();

}

void charac::moveUpCharacter(sprite *move){

    move->moveImage(0,-speed);
    move->setSprite();


}

void charac::moveDownCharacter(sprite *move){

    move->moveImage(0,speed);
    move->setSprite();
}

void charac::moveLeftCharacter(sprite *move){

    move->moveImage(-(speed-3),0);
    move->setSprite();

}

void charac::moveRightCharacter(sprite *move){

    move->moveImage(speed,0);
    move->setSprite();

}

void charac::deadCharacter(sprite *dead_sprite, int y_image, int width_image, int n_image,QTimer *timer_dead){

    dead_sprite->setAttributes(y_image,width_image,n_image);
    methodCharacter(dead_sprite);

    if(dead_sprite->getCont() == n_image-1) {
        dead_sprite->setCont(0);
        timer_dead->stop();
    }
}

void charac::setSpeed(){
    speed*=-1;
}

void charac::setLife(int n){

    life-=n;

}

int charac::getLife()
{
    return life;
}

int charac::getSpeed(){

    return speed;

}



