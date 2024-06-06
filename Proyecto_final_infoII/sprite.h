#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>

class sprite : public QGraphicsPixmapItem {
public:
    sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _pos_x,qreal _pos_y);
    sprite();

    void moveImage(int dx, int dy);


    void setSprite();
    void setAttributes(int _sprite_y,int _width,int n_image);
    void setCont(int _cont);

    int getCont();
    qreal gety();
    qreal getx();

private:
    qreal x;
    qreal y;
    QPixmap spriteSheet;
    QPixmap sprit;
    int sprite_x;
    int sprite_y;
    int sprite_width;
    int sprite_height;
    int n_image=7;
    int cont = 0;  // Inicializar la variable cont
};

#endif // SPRITE_H
