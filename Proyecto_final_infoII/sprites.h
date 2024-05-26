#ifndef SPRITES_H
#define SPRITES_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QString>

using namespace std;


class sprites : public QObject, public QGraphicsPixmapItem
{
private:

    QPixmap sprite;
    QPixmap spriteSheet;
    qreal x;
    qreal y;
    int sprite_x;
    int sprite_y;
    int sprite_width;
    int sprite_height;

public:

    sprites(QString name_image, int spriteX_,int spriteY_,int spriteWidth_,  int spriteHeight_,qreal x_,qreal y_);

    void moveImage(int dx, int dy);
    void setSprite(int pixelx);

};


#endif // SPRITES_H
