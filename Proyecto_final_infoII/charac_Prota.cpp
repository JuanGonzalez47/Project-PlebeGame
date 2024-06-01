# include "charac_Prota.h"

prota::prota(int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed), scene(_scene){

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 99,400,400);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(400,400);

}

prota::prota(int _life)
{
    set_life(_life);
    sprite sprite_to_cut;
    //constructor para el sprite del protagonista del nivel_2
    //for para las animaciones de movimiento y muerte
    movimiento_derecha = new QPixmap[7];
    movimiento_izquierda = new QPixmap[7];
    for (unsigned int x = 0; x < 7; x++){
        movimiento_derecha[x] = sprite_to_cut.set_sprite_for_animation(x,0,0,130,160);
        movimiento_izquierda[x] = sprite_to_cut.set_sprite_for_animation(x,0,0,130,160);
    }
    mov_derecha = new QGraphicsPixmapItem(movimiento_derecha[0]);
    mov_izquierda = new QGraphicsPixmapItem(movimiento_izquierda[0]);
}

prota::prota()
{
    //constructor por defecto de la clase prota
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

void prota::mover_derecha()
{
    animation_counter_1++;
    if (animation_counter_1 == 6) animation_counter_1 = 0;
    mov_derecha->setPixmap(movimiento_derecha[animation_counter_1]);
    mov_derecha->setX(mov_derecha->x()+velocidad_personaje);
}

QPixmap *prota::get_movimiento_derecha()
{
    return movimiento_derecha;
}

QPixmap *prota::get_movimiento_izquierda()
{
    return movimiento_izquierda;
}

QGraphicsPixmapItem *prota::get_mov_derecha()
{
    return mov_derecha;
}


QGraphicsPixmapItem *prota::get_mov_izquierda()
{
    return mov_izquierda;
}

void prota::deadProta(){

    sprite_prota->setAttributes(300,80,14);
    methodCharacter(sprite_prota);

}




