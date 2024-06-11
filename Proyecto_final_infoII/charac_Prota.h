# include "characters.h"

#include <cmath>
#include <QVector2D>

#include <QTimer>


#ifndef CHARAC_PROTA_H
#define CHARAC_PROTA_H

#define velocidad_misil_avion 15
#define life_prota_level_2 5
#define angulo1 75
#define g 9.8

//parametros funcion senoidal

#define amplitud 76
#define frecuencia_ 0.9

class prota : public charac {

private:


    sprite *sprite_prota;
    QPixmap *movimiento_prota, *movimiento_avion, *movimiento_misiles_avion;
    QGraphicsPixmapItem *mov_prota, *mov_avion, *mov_misiles_avion;
    int animation_counter_1 = 0, animation_counter_2 = 6, animation_counter_3 = 13, animation_counter_4 = 25, animation_counter_5 = 13, animation_counter_6 = 0, animation_counter_7 = 15, animation_counter_8 = 0;
    double y_inicial_ = 0, x_inicial_ = 0, t = 0, t_final = 0, tiempo = 0, t_seno = 0, y_inicial_1 = 0;
    bool valid_put_misil = true;
    QGraphicsScene *scene;
    int cont_bullets=0;

public:

    prota(int _life);
    prota (unsigned int life_);
    prota();
    prota(qreal _x,qreal _y,int _life,int _bullets,int _speed,sprite *s_prota, QGraphicsScene *_scene);

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void throwGrenade(QTimer *timer_grenade, QTimer *timer_burst,double y_inicial,double x_inical,sprite *grenade);
    void launch(QTimer* t_prota_lauch,bool *block);
    void shoot(QTimer *t_prota_shoot);
    void dead(QTimer *timer_dead);
    void recharge(QTimer* t_prota_recharge, bool *block);

    void setCont_bullets();
    int getCont_bullets();

    int getY();
    int getX();


    void mover_derecha(QGraphicsPixmapItem *llanta_2);
    void mover_izquierda(QGraphicsPixmapItem *llanta_1);
    void movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, QTimer *timerSpace, bool direccion, double potenciador, QTimer *timerRebotar);
    void movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, bool direccion, QTimer *timerMuerte, QTimer *gameOver);
    void seguimiento_mov(QVector2D pos_objeto, QTimer *timerMovMisil, QTimer *timerExplosion);
    double distancia(QVector2D vector1, QVector2D vector2);
    void explosion(QTimer *timerExplosion, QTimer *timerEliminacionHelicopteros);

    void firme(QTimer *timerFirme);
    void avion(unsigned int pos_y, QTimer *timerMisilesAvion);

    QPixmap *get_movimiento_prota();
    QGraphicsPixmapItem *get_mov_prota();
    QPixmap *get_movimiento_avion();
    QGraphicsPixmapItem *get_mov_avion();
    QPixmap *get_movimiento_misiles_avion();
    QGraphicsPixmapItem *get_mov_misiles_avion();
    void set_animation_counter_3();
    void set_animation_counter_5();
};


#endif // CHARAC_PROTA_H
