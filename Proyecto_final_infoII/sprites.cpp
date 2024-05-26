#include "sprites.h"

sprite::sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _x,qreal _y){


    spriteSheet.load(name_image);

    //posicion inicial en la que se vera la imagen en la escena
    x=_x;
    y=_y;

    //posicion inicial en el sprite
    sprite_x=_sprite_x;
    sprite_y=_sprite_y;
    //dimensiones de cada imagen
    sprite_width=_sprite_width;
    sprite_height=_sprite_height;

    sprit = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprit);

}

sprite::sprite(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im){

}

void sprite::moveImage(int dx, int dy){

    //move imagen por la escena
    x += dx;
    y += dy;
    setPos(x, y);
}

void sprite::setSprite(int n_image,int dir){

    sprite_x = sprite_width * cont;//rotar por cada imagen
    sprite_y = dir;
    QPixmap sprite = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprite);
    cont++;
    if (cont == n_image) {
        cont = 0;
    }

}


