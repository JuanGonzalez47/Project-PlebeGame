# include "charac_Prota.h"

prota::prota(int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed), scene(_scene){

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 99,400,400);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(400,400);
}

void prota::moveUpProta() {

    sprite_prota->setAttributes(0,110,9);
    moveUpCharacter(sprite_prota);
}

void prota::moveDownProta(){

    sprite_prota->setAttributes(0,110,9);
    moveDownCharacter(sprite_prota);

}

void prota::moveRihgtProta(){

    sprite_prota->setAttributes(0,110,9);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeftProta(){

    sprite_prota->setAttributes(0,110,9);
    moveLeftCharacter(sprite_prota);
}

void prota::shootProta(){

    sprite_prota->setAttributes(100,120,4);
    methodCharacter(sprite_prota);

}

void prota::rechargeProta(){

    sprite_prota->setAttributes(200,115,9);
    methodCharacter(sprite_prota);

}

void prota::deadProta(){

    sprite_prota->setAttributes(300,80,14);
    methodCharacter(sprite_prota);

}




