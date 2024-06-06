# include "characters.h"
#include <QTimer>


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H


class prota : public charac {

private:


    sprite *sprite_prota;
    QGraphicsScene *scene;

    int cont_bullets=0;
    double t=0;

public:

    prota(qreal _x,qreal _y,int _life,int _bullets,int _speed,sprite *s_prota, QGraphicsScene *_scene);

    void moveUp();
    void moveDown();
    void moveRihgt();
    void moveLeft();

    void throwGrenade(QTimer *timer_grenade,double y_inicial,double x_inical,sprite *grenade);


    void shoot(QTimer *t_prota_shoot);

    void dead();
    void recharge(QTimer* t_prota_recharge);

    void setCont_bullets();


    int getCont_bullets();

    int getY();
    int getX();



};


#endif // CHARAC_PROTA_H
