#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class sprite : public QGraphicsPixmapItem {
public:
    sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _pos_x,qreal _pos_y);
    sprite(QString name_image);
    sprite();
    QPixmap set_sprite_for_animation(unsigned int pos_x,unsigned int pos_y, unsigned int value,unsigned int width, unsigned int height);
    void moveImage(int dx, int dy);
    void setSprite();
    QPixmap SetSprite(unsigned int tipo_imagen);
    void setAttributes(int _sprite_y,int _width,int n_image);

private:
    qreal x;
    qreal y;
    QPixmap spriteSheet, fondo_nivel_2, pantalla_carga_nivel_2, personaje_principal_mov_r, personaje_principal_mov_l, helicoptero_enemigo, helicoptero_amigo, telefono, llantas, sangre, misiles, numeros, time, explosion_1, explosion_2, game_over, mensaje, salto_D, salto_I, muerte, firme, punto;
    QPixmap sprit,copy;
    int sprite_x;
    int sprite_y;
    int sprite_width;
    int sprite_height;
    int n_image=9;
    int cont = 0;  // Inicializar la variable cont
    QGraphicsScene *scene;
};

#endif // SPRITE_H
