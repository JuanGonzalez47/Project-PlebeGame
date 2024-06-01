
#include "characters.h"


charac::charac(int _life,int _bullets,int _speed){

    life=_life;
    bullets=_bullets;
    speed=_speed;
}

charac::charac()
{
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

void charac::set_life(int _life)
{
    life = _life;
}

void charac::set_bullets(int _bullets)
{
    bullets = _bullets;
}



