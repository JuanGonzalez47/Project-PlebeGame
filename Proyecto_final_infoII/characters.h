#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "sprite.h"
#define vida_personaje 100
#define balas_personaje 100
#define velocidad_personaje 15


class charac{

private:


    int life;
    int bullets;
    int speed;

public:

    charac(int _life,int _bullets,int _speed);
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

};


#endif // CHARACTERS_H
