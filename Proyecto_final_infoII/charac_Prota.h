# include "characters.h"


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H


class prota : public charac {

private:

    QGraphicsScene *scene;
    sprite *sprite_prota;


public:

    prota(int _life,int _bullets,int _speed,QGraphicsScene *_scene);

    void moveUpProta();
    void moveDownProta();
    void moveRihgtProta();
    void moveLeftProta();

    void shootProta();
    void deadProta();
    void rechargeProta();


};


#endif // CHARAC_PROTA_H
