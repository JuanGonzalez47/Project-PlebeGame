# include "characters.h"


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H

#define life_prota_level_2 = 5

class prota : protected charac {

private:

    QGraphicsScene *scene;
    sprite *sprite_prota;
    QPixmap *movimiento_derecha, *movimiento_izquierda;
    QGraphicsPixmapItem *mov_derecha, *mov_izquierda;
    int animation_counter_1 = 0;


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

    QPixmap *get_movimiento_derecha();
    QPixmap *get_movimiento_izquierda();
    QGraphicsPixmapItem *get_mov_derecha();
    QGraphicsPixmapItem *get_mov_izquierda();

};


#endif // CHARAC_PROTA_H
