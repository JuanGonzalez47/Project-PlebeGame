#include "sprite.h"

sprite::sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height, int _n_image,qreal _x,qreal _y) {
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
    n_image = _n_image;

    sprit = spriteSheet.copy(sprite_x, sprite_y, sprite_width, sprite_height);
    setPixmap(sprit);
}

void sprite::moveImage(int dx, int dy) {
    // Mover imagen por la escena
    x += dx;
    y += dy;
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
