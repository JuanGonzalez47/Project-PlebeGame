#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class sprite : public QGraphicsPixmapItem {
public:
    sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height, int _n_image,qreal _pos_x,qreal _pos_y);
    void moveImage(int dx, int dy);
    void setSprite();

private:
    qreal x;
    qreal y;
    QPixmap spriteSheet;
    QPixmap sprit;
    int sprite_x;
    int sprite_y;
    int sprite_width;
    int sprite_height;
    int n_image;
    int cont = 0;  // Inicializar la variable cont
    QGraphicsScene *scene;
};

#endif // SPRITE_H
