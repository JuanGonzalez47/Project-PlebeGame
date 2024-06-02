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
    movimiento_prota = new QPixmap[26];
    unsigned int cont = 0;
    for (unsigned int x = 0; x < 26; x++){
        if (x < 7) movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(x,0,0,132,162);
        else if (x >= 7 && x < 14){
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,1,132,162);
            cont++;
            if (cont == 7) cont = 0;
        }
        else if (x >= 14 && x < 20){
            if (x == 19) movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(0,0,2,130,192);
            else{
                movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,2,130,192);
                cont++;
            }
        }
    }
    mov_prota = new QGraphicsPixmapItem(movimiento_prota[19]);
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
    mov_prota->setPixmap(movimiento_prota[animation_counter_1]);
    mov_prota->setX(mov_prota->x()+velocidad_personaje);
}

void prota::mover_izquierda()
{
    animation_counter_2++;
    if (animation_counter_2 == 13) animation_counter_2 = 7;
    mov_prota->setPixmap(movimiento_prota[animation_counter_2]);
    mov_prota->setX(mov_prota->x()-velocidad_personaje);
}

void prota::salto()
{
    //agregar animacion del salto, tomarn en cuenta la ecuacion de movimiento parabolico
}

QPixmap *prota::get_movimiento_prota()
{
    return movimiento_prota;
}


QGraphicsPixmapItem *prota::get_mov_prota()
{
    return mov_prota;
}


void prota::deadProta(){

    sprite_prota->setAttributes(300,80,14);
    methodCharacter(sprite_prota);

}




