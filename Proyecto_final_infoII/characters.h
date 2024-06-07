#ifndef CHARACTERS_H
#define CHARACTERS_H


#include "sprite.h"
#include "QTimer"



class charac{

private:
    int life;
    int bullets;
    int speed;
    qreal x;
    qreal y;

public:

    charac(int _life,int _bullets,int _speed,qreal _x,qreal _y);
    charac();
    void methodCharacter(sprite *method);
    void moveUpCharacter(sprite *move);
    void moveDownCharacter(sprite *move);
    void moveLeftCharacter(sprite *move);
    void moveRightCharacter(sprite *move);
    void deadCharacter(sprite *dead_sprite, int y_image,int width_image,int n_image,QTimer *timer_dead);

    void setSpeed();
    void setLife(int n);

    int getSpeed();
    int getLife();


};


#endif // CHARACTERS_H
