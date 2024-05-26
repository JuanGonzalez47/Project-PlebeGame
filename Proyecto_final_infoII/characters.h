#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "sprite.h"



class charac{

private:


    int life;
    int bullets;
    int speed;

public:

    charac(int _life,int _bullets,int _speed);
    void methodCharacter(sprite *method);
    void moveUpCharacter(sprite *move);
    void moveDownCharacter(sprite *move);
    void moveLeftCharacter(sprite *move);
    void moveRightCharacter(sprite *move);
};


#endif // CHARACTERS_H
