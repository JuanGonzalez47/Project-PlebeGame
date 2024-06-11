#ifndef CHARAC_ENEMY_H
#define CHARAC_ENEMY_H
#include "characters.h"
#include "charac_Prota.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <QVector2D>
#include <QTimer>
  
#define size_screen_w 1600
#define size_screen_h 920
//condiciones iniciales del pendulo
#define g 9.8
#define periodo 2
#define longitud 25
//condiciones iniciales del movimiento circular
#define frecuencia 0.4
#define radio 80

#define velocidad_misil 15

    class enemy: public charac
{
private:
    QGraphicsScene *scene;
    sprite *sprite_enemy_rifle;
    int n_ran=5;
    int mov_ran=0;
    
    
    QPixmap *movimiento_enemigo, *movimiento_misil;
    QGraphicsPixmapItem *mov_enemigo, *mov_misil;
    unsigned int animation_counter_1 = 0, animation_counter_2 = 0, animation_counter = 6, animation_counter_3 = 0, counter = 0, animation_counter_4 = 7, animation_counter_5 = 0, counter_1 = 0;
    double t, angulo, omega, x_inicial_, y_inicial_, omega_c, periodo_circular, x_ini, y_ini, tiempo = 0;
    bool valid_move_left = false, valid_move_right = true;

public:

    enemy(qreal _x,qreal _y,int _life,int _bullets,int _speed, QGraphicsScene *_scene);

    ~enemy();
    void moveUpEnemy();
    void moveDownEnemy();
    void moveRihgtEnemy();
    void moveLeftEnemy();
    void shoot(QTimer *t_move, QTimer *t_enemy_shoot);


    void deadEnemy(QTimer *timer_dead);

    void setMovRan(int n);
    void setN_ran(int _n_ran);
    void sumMovran();

    int getN_ran();
    int getMov_ran();

    int getX();
    int getY();
    sprite* getSprite_rifle();



    enemy();
    enemy(int _life);

    QPixmap *get_movimiento_enemigo();
    QGraphicsPixmapItem *get_mov_enemigo();
    QPixmap *get_movimiento_misil();
    QGraphicsPixmapItem *get_mov_misil();
    void set_mov_misil();

    void pendulo_simple(double x_inicial, double y_inicial,QTimer *timerPendulo, QTimer *timerMovimientoRecto, QTimer *timerIniciarPendulo, QTimer *timerMisil_circular);
    void Movimiento_recto(QTimer *timerMisil_recto, bool direccion, bool stop);
    void seguimiento_mov(QVector2D pos_objeto, QTimer *timerSeguimiento, QTimer *timerExplosion, QTimer *timerMuerte, bool muerte, prota &walter, bool morir);
    void animacion_preparo_disparo(QTimer *timerPendulo, QTimer *timerDisparo, QTimer *timerMisil_recto);
    void movimiento_cirular(QTimer *timerMisil_circular,double x_inicial, double y_inicial, QTimer *timerSeguimiento);
    void misil_recto(QTimer *timerExplosion, QVector2D pos_objeto, QTimer *timerMuerte, bool muerte);
    double aceleracion_angular(double theta);
    double distancia(QVector2D vector1, QVector2D vector2);
    void explosion(QTimer *timerExplosion, QTimer *timerStartMisil_recto, QTimer *timerEliminacion);

};
#endif // CHARAC_ENEMY_H
