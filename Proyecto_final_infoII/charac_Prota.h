# include "characters.h"
#include <cmath>

#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H

#define life_prota_level_2 5
#define angulo1 75
#define g 9.8

class prota : protected charac {

private:

    QGraphicsScene *scene;
    sprite *sprite_prota;
    QPixmap *movimiento_prota;
    QGraphicsPixmapItem *mov_prota;
    int animation_counter_1 = 0, animation_counter_2 = 6, animation_counter_3 = 13, animation_counter_4 = 25;
    double y_inicial_ = 0, x_inicial_ = 0, t = 0;


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
    void movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, QTimer *timerSpace, bool direccion, double potenciador, QTimer *timerRebotar);
    void movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, bool direccion, QTimer *timerMuerte, QTimer *gameOver, QTimer *timerSpace);
    void firme(QTimer *timerFirme);

    QPixmap *get_movimiento_prota();
    QGraphicsPixmapItem *get_mov_prota();
    void set_animation_counter_3();
};


#endif // CHARAC_PROTA_H
