#include "sprite.h"
# include <iostream>



sprite::sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _x,qreal _y) {
    spriteSheet.load(name_image);

    //posicion inicial en la escena
    x=_x;
    y=_y;

    // Posición inicial en el sprite
    sprite_x = _sprite_x;
    sprite_y = _sprite_y;
    // Dimensiones de cada imagen
    sprite_width = _sprite_width;
    sprite_height = _sprite_height;

    sprit = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprit);
}

sprite::sprite(){

}

sprite::~sprite(){

}

void sprite::moveImage(int dx, int dy) {
    // Mover imagen por la escena

    if(y>=280 && y<=700){
        y+= dy;
    }else if(y<300){
        y+=5;
    }else{
        y--;
    }

    if(x<=7000 && x>=-10){
        x+= dx;

    }else if(x<-10){
        x+=5;
    }else{
        x--;
    }


    setPos(x, y);

}

void sprite::setSprite() {

    sprite_x = sprite_width * cont; // Rotar por cada imagen
    QPixmap sprite = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprite);
    cont++;
    if (cont == n_image) {
        cont = 0;
    }

}

void sprite::setAttributes(int _sprite_y, int _width, int n){

    // por si se trabaja con un solo sprite poder moverse en el libremente cambiando el numero de imagenes cambiar
    //el ancho de la imagen y la posicion en y donde rotara en x en cada imagen
    sprite_y=_sprite_y;
    sprite_width=_width;
    n_image=n;

}

void sprite::setCont(int _cont){

    cont=_cont;

}

void sprite::setN_image(int n){

    n_image=n;

}

void sprite::moveParabolic(int x_inicial, int y_inicial){

    float Voy = 50;
    float g = 9.8;
    float Vox = 60;

    t +=0.2;

    // Calcular nuevas posiciones
    double new_y = y_inicial - Voy * t + (0.5 * g * t * t);
    double new_x = x_inicial + Vox * t;

    x=new_x;
    y=new_y;

    setPos(x,y);
    setSprite();

}


int sprite::getCont(){

    return cont;

}

qreal sprite::gety(){

    return y;

}

qreal sprite::getx(){

    return x;

}


