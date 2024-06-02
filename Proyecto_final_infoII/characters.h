#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "sprite.h"



class charac : public QObject{

private:


    int life;
    int bullets;
    int speed;
    qreal x;
    qreal y;

public:

    charac(int _life,int _bullets,int _speed,qreal _x,qreal _y);
    void methodCharacter(sprite *method);
    void moveUpCharacter(sprite *move);
    void moveDownCharacter(sprite *move);
    void moveLeftCharacter(sprite *move);
    void moveRightCharacter(sprite *move);

    void setSpeed();

    qreal getY();
    int getSpeed();
};


#endif // CHARACTERS_H
