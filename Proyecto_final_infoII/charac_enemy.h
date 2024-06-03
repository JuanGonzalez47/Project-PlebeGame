# include "characters.h"
#include <QTimer>


#ifndef CHARAC_ENEMY_H
#define CHARAC_ENEMY_H

class enemy : public charac{

private:

    QGraphicsScene *scene;
    sprite *sprite_enemy_rifle;
    int n_ran=5;
    int mov_ran=0;
public:

    enemy(qreal _x,qreal _y,int _life,int _bullets,int _speed,sprite *s_enemy_rifle);
    enemy();

    void moveUpEnemy();
    void moveDownEnemy();
    void moveRihgtEnemy();
    void moveLeftEnemy();
    void shoot();
    void deadEnemy();

    void setMovRan(int n);
    void setN_ran(int _n_ran);
    void sumMovran();

    int getN_ran();
    int getMov_ran();


};


#endif // CHARAC_ENEMY_H
