#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <QTimer>
#include "sprite.h"
#define vida_personaje 100
#define balas_personaje 100
#define velocidad_personaje 30
#define velocidad_helicoptero 10


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

    int get_life();
    int get_bullets();
    void set_life(int _life);
    void set_bullets(int _bullets);

    void setSpeed();
    void setLife(int n);
    void setBullets(int n);

    int getSpeed();
    int getLife();
    int getBullets();


};


#endif // CHARACTERS_H
