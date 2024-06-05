
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

    move->moveImage(-speed,0);
    move->setSprite();

}

void charac::moveRightCharacter(sprite *move){

    move->moveImage(speed,0);
    move->setSprite();
}


void charac::setSpeed(){
    speed*=-1;
}

void charac::setLife(int n){

    life-=n;

}

qreal charac::getY(){

    return y;

}

int charac::getLife()
{
    return life;
}

int charac::getSpeed(){

    return speed;

}



