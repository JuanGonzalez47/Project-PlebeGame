# include "characters.h"
#include <QTimer>


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H


class prota : public charac {

private:

    QGraphicsScene *scene;
    sprite *sprite_prota;
    sprite **sprite_bullet;
    QTimer ** timer_bullets;
    QTimer *timer;

    int cont_bullets=0;

public:

    prota(qreal _x,qreal _y,int _life,int _bullets,int _speed,QGraphicsScene *_scene);

    void moveUpProta();
    void moveDownProta();
    void moveRihgtProta();
    void moveLeftProta();


    void shootProta();
    void deadProta();
    void rechargeProta();


};


#endif // CHARAC_PROTA_H
