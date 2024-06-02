# include "characters.h"


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H

#define life_prota_level_2 = 5

class prota : protected charac {

private:

    QGraphicsScene *scene;
    sprite *sprite_prota;
    QPixmap *movimiento_prota;
    QGraphicsPixmapItem *mov_prota;
    int animation_counter_1 = 0, animation_counter_2 = 6;


public:

    prota(int _life,int _bullets,int _speed,QGraphicsScene *_scene);
    prota(int _life);
    prota();

    void moveUpProta();
    void moveDownProta();
    void moveRihgtProta();
    void moveLeftProta();

    void shootProta();
    void deadProta();
    void rechargeProta();

    void mover_derecha();
    void mover_izquierda();
    void salto();

    QPixmap *get_movimiento_prota();
    QGraphicsPixmapItem *get_mov_prota();

};


#endif // CHARAC_PROTA_H
