# include "charac_enemy.h"

enemy::enemy(qreal _x,qreal _y,int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y), scene(_scene){

    sprite_enemy_rifle = new sprite(":/soldado_rifle.png", 0, 110, 85, 110,_x,_y);
    scene->addItem(sprite_enemy_rifle);  // Agregar el sprite a la escena
    sprite_enemy_rifle->setPos(_x,_y);
}


enemy::enemy(){

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

      methodCharacter( sprite_enemy_rifle);

}

void enemy::deadEnemy(){

    // methodCharacter(sprite_prota);


}

void enemy::setMovRan(){

    mov_ran++;

}

void enemy::setN_ran(int _n_ran){

    n_ran=_n_ran;

}

int enemy::getN_ran()
{
    return n_ran;
}

int enemy::getMov_ran()
{
    return mov_ran;
}
