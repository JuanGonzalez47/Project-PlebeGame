# include "characters.h"
#include <QTimer>


#ifndef CHARAC_ENEMY_H
#define CHARAC_ENEMY_H

class enemy : public charac{

private:

    QGraphicsScene *scene;
    sprite *sprite_enemy_rifle;
    QTimer *timer;
    QTimer *timer2;
    int n_ran=5;
    int mov_ran=-1;
public:

    enemy(qreal _x,qreal _y,int _life,int _bullets,int _speed,QGraphicsScene *_scene);
    enemy();

    void moveUpEnemy();
    void moveDownEnemy();
    void moveRihgtEnemy();
    void moveLeftEnemy();


    void moveAndShoot();
    void shootEnemy();
    void deadEnemy();

};


#endif // CHARAC_ENEMY_H
