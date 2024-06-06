# include "charac_Prota.h"

#include <iostream>

prota::prota(int _life, int _bullets, int _speed,QGraphicsScene *_scene) : charac (_life,_bullets,_speed), scene(_scene){

    sprite_prota = new sprite(":/Sprite_prota.png", 0, 0, 110, 99,400,400);
    scene->addItem(sprite_prota);  // Agregar el sprite a la escena
    sprite_prota->setPos(400,400);

}

prota::prota(int _life)
{
    set_life(_life);
    sprite sprite_to_cut;
    //constructor para el sprite del protagonista del nivel_2
    //for para las animaciones de movimiento y muerte
    movimiento_prota = new QPixmap[39];
    unsigned int cont = 0;
    for (unsigned int x = 0; x < 39; x++){
        if (x < 7) movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(x,0,0,132,162);
        else if (x >= 7 && x < 14){
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,1,132,162);
            cont++;
            if (cont == 7) cont = 0;
        }
        else if (x >= 14 && x < 20){
            if (x == 19) {
                movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(0,0,2,130,192);
                cont = 0;
            }
            else{
                movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,2,130,192);
                cont++;
            }
        }
        else if (x >= 20 && x < 26){
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,3,130,192);
            cont++;
            if (x == 25) cont = 0;
        }
        else if (x >= 26 && x < 33){
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,6,120,186);
            cont++;
            if(x == 32) cont = 0;
        }
        else if(x >= 33 && x < 36){
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,10,177,172);
            cont++;
            if(x == 35) cont = 0;
        }
        else{
            movimiento_prota[x] = sprite_to_cut.set_sprite_for_animation(cont,0,11,179,172);
            cont++;
        }
    }
    //for para obtener las animaciones del avion
    movimiento_avion = new QPixmap [18];
    cont = 0;
    for (unsigned int x = 0; x < 18; x++){
        if (x >= 0 && x < 9 ){
            movimiento_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,12,95,60);
            if(x == 8) cont = 0;
        }
        else movimiento_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,12,95,60);
    }

    //for para obtener los misiles de ese avion

    mov_prota = new QGraphicsPixmapItem(movimiento_prota[32]);
}

prota::prota()
{
    //constructor por defecto de la clase prota
}

void prota::moveUpProta() {

    sprite_prota->setAttributes(0,110,9);
    moveUpCharacter(sprite_prota);
}

void prota::moveDownProta(){

    sprite_prota->setAttributes(0,110,9);
    moveDownCharacter(sprite_prota);

}

void prota::moveRihgtProta(){

    sprite_prota->setAttributes(0,110,9);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeftProta(){

    sprite_prota->setAttributes(0,110,9);
    moveLeftCharacter(sprite_prota);
}

void prota::shootProta(){

    sprite_prota->setAttributes(100,120,4);
    methodCharacter(sprite_prota);

}

void prota::rechargeProta(){

    sprite_prota->setAttributes(200,115,9);
    methodCharacter(sprite_prota);

}

void prota::mover_derecha()
{
    animation_counter_1++;
    if (animation_counter_1 == 6) animation_counter_1 = 0;
    mov_prota->setPixmap(movimiento_prota[animation_counter_1]);
    mov_prota->setX(mov_prota->x()+velocidad_personaje);
}

void prota::mover_izquierda()
{
    animation_counter_2++;
    if (animation_counter_2 == 13) animation_counter_2 = 7;
    mov_prota->setPixmap(movimiento_prota[animation_counter_2]);
    mov_prota->setX(mov_prota->x()-velocidad_personaje);
}

void prota::movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, QTimer *timerSpace, bool direccion, double potenciador, QTimer *timerRebotar)
{
    if (!direccion){
        animation_counter_3++;
        //realizar primero las animaciones de tomar impulso
        if (animation_counter_3 == 14 || animation_counter_3 == 15) mov_prota->setPixmap(movimiento_prota[animation_counter_3]);

        //ahora si realizar el movimiento parabolico

        if(animation_counter_3 >= 16){
            //componente Vx es constante, la componente Vy no, y esta es afectada por la gravedad.
            //los cosenos y los senos en las formulas salen de la descomposicion vectorial
            //ecuaciones para regir el movimiento: Vx = Vox = Vo*cos(angulo), Vy = Voy - g*t, siendo Voy = Vo*sen(angulo)
            //ecuaciones para regir la posicion en x y y, x = xo + vox*t (ecuacion MRU) no hay aceleracion, en Y (MRUA) y = yo + voy*t - 1/2*g*t^2.

            //sumarle al tiempo para actualizar posicion y al contador de la animacion
            t+=0.01;

            if (t == 0.01 ){
                y_inicial_ = y_inicial;
                x_inicial_ = x_inicial;
            }

            //definir Voy, Vox

            double Voy = (velocidad_inicial*potenciador)*sin((angulo1*M_PI) / 180.0);
            double Vox = (velocidad_inicial*potenciador)*cos((angulo1*M_PI) / 180.0);

            //definir la posicion en x y en y, se trucan lo signos de new_y ya que en el plano la y crece para abajo y decrece para arriba
            double new_y = y_inicial_ - Voy*t + (0.5*g*t*t);
            double new_x = x_inicial_ + Vox*t;

            if(t == 0.01){
                double a = 0.5*g;
                double b = -Voy;
                double c = y_inicial_ - 600;
                double discriminante = b * b - 4 * a * c;
                double raiz = sqrt(abs(discriminante));

                double x1 = (-b + raiz) / (2 * a);
                double x2 = (-b - raiz) / (2 * a);
                if (x1 > x2) t_final = x1;
                else t_final = x2;
            }

            mov_prota->setPixmap(movimiento_prota[16]);
            mov_prota->setX(new_x);
            mov_prota->setY(new_y);

            if (t >= t_final){
                mov_prota->setPixmap(movimiento_prota[0]);
                animation_counter_3 = 13;
                t = 0;
                timerSpace->stop();
                if (potenciador == 3) timerRebotar->stop();
            }
        }
    }
    else{
        if (animation_counter_3 == 13 && t == 0) set_animation_counter_3();
        animation_counter_3--;
        //realizar primero las animaciones de tomar impulso
        if (animation_counter_3 == 24 || animation_counter_3 == 23) mov_prota->setPixmap(movimiento_prota[animation_counter_3]);

        //ahora si realizar el movimiento parabolico

        if(animation_counter_3 <= 22){
            //componente Vx es constante, la componente Vy no, y esta es afectada por la gravedad.
            //los cosenos y los senos en las formulas salen de la descomposicion vectorial
            //ecuaciones para regir el movimiento: Vx = Vox = Vo*cos(angulo), Vy = Voy - g*t, siendo Voy = Vo*sen(angulo)
            //ecuaciones para regir la posicion en x y y, x = xo + vox*t (ecuacion MRU) no hay aceleracion, en Y (MRUA) y = yo + voy*t - 1/2*g*t^2.

            //sumarle al tiempo para actualizar posicion y al contador de la animacion
            t+=0.01;

            if (t == 0.01 ){
                y_inicial_ = y_inicial;
                x_inicial_ = x_inicial;
            }

            //definir Voy, Vox

            double Voy = (velocidad_inicial*potenciador)*sin((angulo1*M_PI) / 180.0);
            double Vox = (velocidad_inicial*potenciador)*cos((angulo1*M_PI) / 180.0);

            //definir la posicion en x y en y, se trucan lo signos de new_y ya que en el plano la y crece para abajo y decrece para arriba
            double new_y = y_inicial_ - Voy*t + (0.5*g*t*t);
            double new_x = x_inicial_ - Vox*t;

            if(t == 0.01){
                double a = 0.5*g;
                double b = -Voy;
                double c = y_inicial_ - 600;
                double discriminante = b * b - 4 * a * c;
                double raiz = sqrt(abs(discriminante));

                double x1 = (-b + raiz) / (2 * a);
                double x2 = (-b - raiz) / (2 * a);
                if (x1 > x2) t_final = x1;
                else t_final = x2;
            }

            mov_prota->setPixmap(movimiento_prota[22]);
            mov_prota->setX(new_x);
            mov_prota->setY(new_y);

            if (t >= t_final){
                //parar animacion ya que volvimos a nuestra y de partida y por ende ya estamos en el suelo
                //agregar animacion de aterrizaje y evaluar sui su posicion fianal es el de la llanta
                mov_prota->setPixmap(movimiento_prota[13]);
                animation_counter_3 = 13;
                t = 0;
                timerSpace->stop();
                if (potenciador == 3) timerRebotar->stop();
            }
        }
    }



}

void prota::movimiento_parabolico(double velocidad_inicial, double y_inicial, double x_inicial, bool direccion, QTimer *timerMuerte, QTimer *gameOver)
{
    if (!direccion){
        animation_counter_5++;
        //realizar primero las animaciones de tomar impulso
        if (animation_counter_5 == 14) mov_prota->setPixmap(movimiento_prota[38]);

        //ahora si realizar el movimiento parabolico

        if(animation_counter_5 >= 16){

            tiempo+=0.01;

            if (tiempo == 0.01 ){
                y_inicial_ = y_inicial;
                x_inicial_ = x_inicial;
            }

            //definir Voy, Vox

            double Voy = (velocidad_inicial*2)*sin((angulo1*M_PI) / 180.0);
            double Vox = (velocidad_inicial*2)*cos((angulo1*M_PI) / 180.0);

            //definir la posicion en x y en y, se trucan lo signos de new_y ya que en el plano la y crece para abajo y decrece para arriba
            double new_y = y_inicial_ - Voy*tiempo + (0.5*g*tiempo*tiempo);
            double new_x = x_inicial_ + Vox*tiempo;

            //calcular el tiempo final

            if(tiempo == 0.01){
                double a = 0.5*g;
                double b = -Voy;
                double c = y_inicial_ - 600;
                double discriminante = b * b - 4 * a * c;
                double raiz = sqrt(abs(discriminante));

                double x1 = (-b + raiz) / (2 * a);
                double x2 = (-b - raiz) / (2 * a);
                if (x1 > x2) t_final = x1;
                else t_final = x2;
            }


            mov_prota->setPixmap(movimiento_prota[37]);
            mov_prota->setX(new_x);
            mov_prota->setY(new_y);


            if (tiempo >= t_final){
                mov_prota->setPixmap(movimiento_prota[36]);
                timerMuerte->stop();
                gameOver->start();
                tiempo = 0;
                t_final = 0;
            }
        }
    }
    else{
        if (animation_counter_5 == 13 && tiempo == 0) set_animation_counter_3();
        animation_counter_5--;
        //realizar primero las animaciones de tomar impulso
        if (animation_counter_5 == 24) mov_prota->setPixmap(movimiento_prota[33]);

        //ahora si realizar el movimiento parabolico

        if(animation_counter_5 <= 22){
            //componente Vx es constante, la componente Vy no, y esta es afectada por la gravedad.
            //los cosenos y los senos en las formulas salen de la descomposicion vectorial
            //ecuaciones para regir el movimiento: Vx = Vox = Vo*cos(angulo), Vy = Voy - g*t, siendo Voy = Vo*sen(angulo)
            //ecuaciones para regir la posicion en x y y, x = xo + vox*t (ecuacion MRU) no hay aceleracion, en Y (MRUA) y = yo + voy*t - 1/2*g*t^2.

            //sumarle al tiempo para actualizar posicion y al contador de la animacion
            tiempo+=0.01;

            if (tiempo == 0.01 ){
                y_inicial_ = y_inicial;
                x_inicial_ = x_inicial;
            }

            //definir Voy, Vox

            double Voy = (velocidad_inicial*2)*sin((angulo1*M_PI) / 180.0);
            double Vox = (velocidad_inicial*2)*cos((angulo1*M_PI) / 180.0);

            //calcular el tiempo final

            if(tiempo == 0.01){
                double a = 0.5*g;
                double b = -Voy;
                double c = y_inicial_ - 600;
                double discriminante = b * b - 4 * a * c;
                double raiz = sqrt(abs(discriminante));

                double x1 = (-b + raiz) / (2 * a);
                double x2 = (-b - raiz) / (2 * a);
                if (x1 > x2) t_final = x1;
                else t_final = x2;
            }

            //definir la posicion en x y en y, se trucan lo signos de new_y ya que en el plano la y crece para abajo y decrece para arriba
            double new_y = y_inicial_ - Voy*tiempo + (0.5*g*tiempo*tiempo);
            double new_x = x_inicial_ - Vox*tiempo;


            mov_prota->setPixmap(movimiento_prota[34]);
            mov_prota->setX(new_x);
            mov_prota->setY(new_y);

            if (tiempo >= t_final){
                mov_prota->setPixmap(movimiento_prota[35]);
                timerMuerte->stop();
                gameOver->start();
                tiempo = 0;
                t_final = 0;
            }
        }
    }

}


void prota::firme(QTimer *timerFirme)
{
    animation_counter_4++;
    if (animation_counter_4 >= 25 && animation_counter_4 <= 32)
    mov_prota->setPixmap(movimiento_prota[animation_counter_4]);
    if (animation_counter_4 == 55) {
        timerFirme->stop();
    }
}

QPixmap *prota::get_movimiento_prota()
{
    return movimiento_prota;
}


QGraphicsPixmapItem *prota::get_mov_prota()
{
    return mov_prota;
}

QPixmap *prota::get_movimiento_avion()
{
    return movimiento_avion;
}

QGraphicsPixmapItem *prota::get_mov_avion()
{
    return mov_avion;
}

QPixmap *prota::get_movimiento_misiles_avion()
{
    return movimiento_misiles_avion;
}

QGraphicsPixmapItem *prota::get_mov_misiles_avion()
{
    return mov_misiles_avion;
}

void prota::set_animation_counter_3()
{
    animation_counter_3 = 25;
}

void prota::set_animation_counter_5()
{
    animation_counter_5 = 25;

}



void prota::deadProta(){

    sprite_prota->setAttributes(300,80,14);
    methodCharacter(sprite_prota);

}




