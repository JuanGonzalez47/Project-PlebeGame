#include "charac_enemy.h"
#include <iostream>

enemy::enemy()
{
    //constructor por defecto
}

enemy::enemy(int _life)
{
    set_life(_life);
    sprite sprite_to_cut;
    //constructor para el sprite del protagonista del nivel_2
    //for para las animaciones de movimiento y muerte
    movimiento_enemigo = new QPixmap[12];
    unsigned int cont = 0;
    unsigned int y = 0;
    for (unsigned int x = 0; x < 7; x++){
        movimiento_enemigo[cont] = sprite_to_cut.set_sprite_for_animation(x,y,4,71,82).scaled(300,200);
        cont++;
    }
    y = 1;
    for (unsigned int x = 0; x < 5; x++){
        movimiento_enemigo[cont] = sprite_to_cut.set_sprite_for_animation(x,y,4,72,91).scaled(300,200);
        cont++;
    }
    mov_enemigo = new QGraphicsPixmapItem(movimiento_enemigo[0]);

    //llenar un nuevo arreglo que contenga los misiles y las explosiones

    movimiento_misil = new QPixmap[34];
    unsigned int x = 0;
    for (y = 0; y < 8; y++){
        movimiento_misil[y] = sprite_to_cut.set_sprite_for_animation(x,y,5,30,51).scaled(60,130);
    }
    mov_misil = new QGraphicsPixmapItem(movimiento_misil[0]);

}

QPixmap *enemy::get_movimiento_enemigo()
{
    return movimiento_enemigo;
}

QGraphicsPixmapItem *enemy::get_mov_enemigo()
{
    return mov_enemigo;
}

QGraphicsPixmapItem *enemy::get_mov_misil()
{
    return mov_misil;
}

QPixmap *enemy::get_movimiento_misil()
{
    return movimiento_misil;
}

void enemy::pendulo_simple(double x_inicial, double y_inicial, QTimer *timerPendulo, QTimer *timerMovimientoRecto, QTimer *timerIniciarPendulo, QTimer *timerMisil)
{
    //el MAS movimiento armonico simple en especial del pendulo simple sabemos que viene dado por una ecacion diferencial, sin embargo tiene una aproximacion valida
    // la de angulos pequeños donde decimos que seno(theta) es aproxi theta, sin emabrgo esta no me funciona para mover el helicoptero, por ende optare por un metodo
    // numerico estudiado en metodos numericos, en este caso con el metodo de euler, recordemos que el movimiento armonico simple tiene parametros claves:

    // l = longitud del cable del cual va a ocilar la masa, sin embargo ne mi caso la masa no influira, esta solo aplica tension al cable, entonces no la tenndre en cuenta
    //para el metodo tenemos a g, el angulo del lanzamiento del pendulo, velocidad angular inicial, aceleracion angular (esta es necesario ya que recordemos
    //que trabajaremos con la ecuacion diferencial no lineal de segundo orden d2theta/dt^2 + g/l*sen(theta) = 0

    animation_counter_1++;
    if (animation_counter_1 == 1){
        t = 0.01;
        angulo = M_PI/2;
        omega = 0;
        x_inicial_ = x_inicial;
        y_inicial_ = y_inicial;
    }
    else{
        omega += aceleracion_angular(angulo) * t;

        angulo += omega * t;

        double new_x = x_inicial_ + longitud*sin(angulo);
        double new_y = longitud + (longitud*cos(angulo));

        mov_enemigo->setX(new_x);
        mov_enemigo->setY(new_y);
    }
    if(animation_counter_1 == (periodo*1000)/2){
        mov_enemigo->setPixmap(movimiento_enemigo[11]);
        timerMisil->start();
    }
    if(animation_counter_1 == periodo*1000){
        timerPendulo->stop();
        timerMovimientoRecto->start();
        timerIniciarPendulo->start();
        animation_counter_1 = 0;
    }


}

void enemy::Movimiento_recto()
{
    animation_counter_2++;
    if (animation_counter_2 == 6) animation_counter_2 = 0;
    mov_enemigo->setPixmap(movimiento_enemigo[animation_counter_2]);
    if(valid_move_left){
        mov_enemigo->setX(mov_enemigo->x()-velocidad_helicoptero);
        if (mov_enemigo->x() <= 100){
            valid_move_right = true;
            valid_move_left = false;
        }
    }
    else if (valid_move_right){
        mov_enemigo->setX(mov_enemigo->x() + velocidad_helicoptero);
        if (mov_enemigo->x() >= size_screen_w - 450) {
            valid_move_left = true;
            valid_move_right = false;
        }
    }
}

void enemy::seguimiento_mov(QVector2D pos_personaje,QTimer *timerSeguimiento)
{
    animation_counter_3++;
    QVector2D pos_misil(mov_misil->pos().x(), mov_misil->pos().y());
    QVector2D direccion = pos_personaje - pos_misil;
    direccion.normalize();
    pos_misil += direccion*velocidad_misil;

    if (animation_counter_3 == 7) animation_counter_3 = 0;
    mov_misil->setPixmap(movimiento_misil[animation_counter_3]);
    mov_misil->setX(pos_misil.x());
    mov_misil->setY(pos_misil.y());

    if (distancia(pos_misil, pos_personaje) < 5) {
        timerSeguimiento->stop();
        animation_counter_3 = 0;
        //activar timer de explosion y muerte del personaje (este misil matara de un solo tiro)

    }
}

void enemy::animacion_preparo_disparo(QTimer *timerPendulo, QTimer *timerDisparo)
{
    animation_counter++;
    mov_enemigo->setPixmap(movimiento_enemigo[animation_counter]);
    if (animation_counter == 10) {
        timerDisparo->stop();
        timerPendulo->start();
        animation_counter = 6;
    }
}

double enemy::distancia(QVector2D vector1, QVector2D vector2)
{
    return (vector1 - vector2).length();
}


void enemy::movimiento_cirular(QTimer *timerMisil_circular, double x_inicial, double y_inicial, QTimer *timerSeguimiento)
{
    counter++;
    tiempo+=0.01;
    //Recordemos que para el movimiento circular tenemos dos variantes: el Uniforme cuya velocidad angular es constante y el unfiormemente acelerado, por simplicidad
    //y ya que el movimiento uniforme puede generar un buen movimiento para el misil, usaremos este, aspectos a tener en cuenta: ya que rige una trayectoria circular
    //debemos saber que las coordenadas de dicho movimiento ya no seran cartesianas sino polares, pues estan nos ayudan a describir con detalle el cambio de la posicion
    //angular con respecto a un r (radio constante) asi que para nuestro caso sera necesario saber las relaciones de x y y en coordenadas polares (tema estudiado en
    //calculo vectorial y matematicas especiales)

    if (counter == 1) {
        omega_c = 2*M_PI*frecuencia;
        periodo_circular = (2*M_PI)/omega_c;
        x_ini = x_inicial;
        y_ini = y_inicial;
    }
    if (counter == 50) mov_enemigo->setPixmap(movimiento_enemigo[10]);


    double new_y = -y_ini + radio*sin(omega_c*tiempo) + 70;
    double new_x = x_ini + radio*cos(omega_c*tiempo) + 100;

    mov_misil->setX(new_x);
    mov_misil->setY(new_y);

    if (counter == (periodo_circular*1000)/2){
        timerSeguimiento->start();
        timerMisil_circular->stop();
        counter = 0;
    }


}

double enemy::aceleracion_angular(double theta)
{
    return -(g / longitud) * sin(theta); //se despeja basicamente de la ecuacion diferencial que coloque arriba
}
