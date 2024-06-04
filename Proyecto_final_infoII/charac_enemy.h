#ifndef CHARAC_ENEMY_H
#define CHARAC_ENEMY_H
# include "characters.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <QVector2D>

#define size_screen_w 1600
#define size_screen_h 920
//condiciones iniciales del pendulo
#define g 9.8
#define periodo 6
#define longitud 25
//condiciones iniciales del movimiento circular
#define frecuencia 0.2
#define radio 80

#define velocidad_misil 15

    class enemy: protected charac
{
private:

    QPixmap *movimiento_enemigo, *movimiento_misil;
    QGraphicsPixmapItem *mov_enemigo, *mov_misil;
    unsigned int animation_counter_1 = 0, animation_counter_2 = 0, animation_counter = 6, animation_counter_3 = 0, counter = 0;
    double t, angulo, omega, x_inicial_, y_inicial_, omega_c, periodo_circular, x_ini, y_ini, tiempo = 0;
    bool valid_move_left = false, valid_move_right = true;

public:

    enemy();
    enemy(int _life);

    QPixmap *get_movimiento_enemigo();
    QGraphicsPixmapItem *get_mov_enemigo();
    QPixmap *get_movimiento_misil();
    QGraphicsPixmapItem *get_mov_misil();

    void pendulo_simple(double x_inicial, double y_inicial,QTimer *timerPendulo, QTimer *timerMovimientoRecto, QTimer *timerIniciarPendulo, QTimer *timerMisil);
    void Movimiento_recto();
    void seguimiento_mov(QVector2D pos_personaje, QTimer *timerSeguimiento);
    void animacion_preparo_disparo(QTimer *timerPendulo, QTimer *timerDisparo);
    void movimiento_cirular(QTimer *timerMisil_circular,double x_inicial, double y_inicial, QTimer *timerSeguimiento);
    double aceleracion_angular(double theta);
    double distancia(QVector2D vector1, QVector2D vector2);

};

#endif // CHARAC_ENEMY_H
