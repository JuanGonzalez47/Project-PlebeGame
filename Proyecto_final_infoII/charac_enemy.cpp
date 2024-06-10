# include "charac_enemy.h"


enemy::enemy(qreal _x,qreal _y,int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y){


    sprite_enemy_rifle=new sprite(":/sprite_enemy.png", 0, 135, 110, 140,_x,_y);
    sprite_enemy_rifle->setScale(0.6);
    scene=_scene;
    scene->addItem(sprite_enemy_rifle);  // Agregar el sprite a la escena
    sprite_enemy_rifle->setPos(_x,_y);

}


enemy::enemy(){

}

enemy::~enemy(){

    //scene->removeItem(sprite_enemy_rifle);  // Quitar el sprite de la escena
    delete sprite_enemy_rifle;  // Liberar la memoria del sprite

}

void enemy::moveUpEnemy() {


    sprite_enemy_rifle->setAttributes(135,115,4);
    moveUpCharacter(sprite_enemy_rifle);

}

void enemy::moveDownEnemy(){

    sprite_enemy_rifle->setAttributes(135,115,4);
    moveDownCharacter(sprite_enemy_rifle);

}

void enemy::moveRihgtEnemy(){

    sprite_enemy_rifle->setAttributes(135,115,4);
    moveRightCharacter(sprite_enemy_rifle);

}

void enemy::moveLeftEnemy(){

    sprite_enemy_rifle->setAttributes(135,115,4);
    moveLeftCharacter(sprite_enemy_rifle);

}

void enemy::shoot(QTimer *t_move, QTimer *t_enemy_shoot){



    sprite_enemy_rifle->setPos(this->getX()-40,this->getY());

    sprite_enemy_rifle->setAttributes(0,184,6);
    methodCharacter(sprite_enemy_rifle);

    if(sprite_enemy_rifle->getCont()==5){
        t_enemy_shoot->stop();
        sprite_enemy_rifle->setCont(0);


        t_move->start();
    }

}

void enemy::deadEnemy(QTimer *timer_dead){

    sprite_enemy_rifle->setAttributes(294,156,16);
        methodCharacter(sprite_enemy_rifle);

        if(sprite_enemy_rifle->getCont() ==15) {
            sprite_enemy_rifle->setCont(0);
            timer_dead->stop();
        }
}

void enemy::sumMovran(){

    mov_ran++;
}



void enemy::setMovRan(int n){

    mov_ran=n;

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

int enemy::getX(){

    return sprite_enemy_rifle->getx();

}

int enemy::getY(){

    return sprite_enemy_rifle->gety();

}


sprite* enemy::getSprite_rifle(){

    return sprite_enemy_rifle;
}
