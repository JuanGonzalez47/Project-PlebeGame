#ifndef SPRITES_H
#define SPRITES_H


#include <QObject>
#include <QString>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>

using namespace std;


class sprite : public QObject, public QGraphicsPixmapItem
{
private:

    QPixmap sprit;
    QPixmap spriteSheet;
    qreal x;
    qreal y;
    int sprite_x;
    int sprite_y;
    int sprite_width;
    int sprite_height;
    int cont;


public:

    sprite(QString name_image, int _sprite_x, int _sprite_y, int _sprite_width, int _sprite_height,qreal _x,qreal _y);
    sprite(QGraphicsView *view,QGraphicsItem* im = 0);

    void moveImage(int dx, int dy);
    void setSprite(int n_image,int dir);

};


#endif // SPRITES_H
