#include "sprites.h"

sprites::sprites(QString name_image, int sprite_x_, int sprite_y_, int sprite_width_, int sprite_height_,qreal x_,qreal y_){


    spriteSheet.load(name_image);

    //posicion inicial en la que se vera la imagen en la escena
    x=x_;
    y=y_;

    //posicion inicial en la imagen
    sprite_x=sprite_x_;
    sprite_y=sprite_y_;
    //dimensiones imagen
    sprite_width=sprite_width_;
    sprite_height=sprite_height_;

    sprite = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprite);

}

void sprites::moveImage(int dx, int dy){

    //move imagen por la escena
    x += dx;
    y += dy;
    setPos(x, y);
}


