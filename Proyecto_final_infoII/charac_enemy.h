#ifndef CHARAC_ENEMY_H
#define CHARAC_ENEMY_H
# include "characters.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#define size_screen_w 1600
#define size_screen_h 920
#define periodo 4
#define g 9.8
#define longitud 25

    class enemy: protected charac
{
private:

    QPixmap *movimiento_enemigo;
    QGraphicsPixmapItem *mov_enemigo;
    unsigned int animation_counter_1 = 0, animation_counter_2 = 0, animation_counter = 6;
    double t, angulo, omega, x_inicial_, y_inicial_;
    bool valid_move_left = false, valid_move_right = true;

public:

    enemy();
    enemy(int _life);

    QPixmap *get_movimiento_enemigo();
    QGraphicsPixmapItem *get_mov_enemigo();

    void pendulo_simple(double x_inicial, double y_inicial,QTimer *timerPendulo, QTimer *timerMovimientoRecto, QTimer *timerIniciarPendulo);
    void Movimiento_recto();
    void animacion_preparo_disparo(QTimer *timerPendulo, QTimer *timerDisparo);
    double aceleracion_angular(double theta);

};

#endif // CHARAC_ENEMY_H
