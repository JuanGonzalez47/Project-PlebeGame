# include "characters.h"
#include <QTimer>


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H


class prota : public charac {

private:

    sprite *sprite_prota;
    sprite **sprite_bullet;
    int cont_bullets=0;

public:

    prota(qreal _x,qreal _y,int _life,int _bullets,int _speed,sprite *s_prota);

    void moveUp();
    void moveDown();
    void moveRihgt();
    void moveLeft();


    void shoot();
    void dead();
    void recharge();

    void setCont_bullets();
    int getCont_bullets();


};


#endif // CHARAC_PROTA_H
