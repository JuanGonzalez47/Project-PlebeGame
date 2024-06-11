# include "charac_Prota.h"
#include <QTimer>

 
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

    mov_prota = new QGraphicsPixmapItem(movimiento_prota[32]);
}

prota::prota(unsigned int life_)
{
    set_life(life_);
    sprite sprite_to_cut;
    //for para obtener las animaciones del avion
    movimiento_avion = new QPixmap [18];
    unsigned int cont = 0;
    for (unsigned int x = 0; x < 18; x++){
        if (x >= 0 && x < 9 ){
            movimiento_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,13,95,60).scaled(280,125);
            cont++;
            if(x == 8) cont = 0;
        }
        else {
            movimiento_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,12,95,60).scaled(280,125);
            cont++;
        }
    }

    //for para obtener los misiles de ese avion y las explosiones

    movimiento_misiles_avion = new QPixmap [39];
    cont = 0;
    for (unsigned int x = 0; x < 38; x++){
        if (x >= 0 && x < 8 ){
            movimiento_misiles_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,15,51,30).scaled(130,60);
            cont++;
            if(x == 7) cont = 0;
        }
        else if (x >= 8 && x < 16){
            movimiento_misiles_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,14,51,30).scaled(130,60);
            cont++;
            if (x == 15) cont = 0;
        }
        else if (x >= 16 && x < 28){
            movimiento_misiles_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,8,55,105).scaled(150,256);
            cont++;
            if (x == 27) cont = 0;
        }
        else{
            movimiento_misiles_avion[x] = sprite_to_cut.set_sprite_for_animation(cont,0,9,50,111).scaled(150,256);
            cont++;
        }
    }

    mov_misiles_avion = new QGraphicsPixmapItem (movimiento_misiles_avion[0]);
    mov_avion = new QGraphicsPixmapItem(movimiento_avion[0]);
}

prota::prota()
{
    //constructor por defecto de la clase prota
}

prota::prota(qreal _x,qreal _y,int _life, int _bullets, int _speed,sprite *s_prota,QGraphicsScene *_scene) : charac (_life,_bullets,_speed, _x,_y){

    scene=_scene;
    sprite_prota=s_prota;
}

void prota::moveUp() {

    sprite_prota->setAttributes(0,43,4);
    moveUpCharacter(sprite_prota);
}

void prota::moveDown(){


 sprite_prota->setAttributes(0,43,4);
    moveDownCharacter(sprite_prota);

}

void prota::moveRight(){

    sprite_prota->setAttributes(0,43,4);
    moveRightCharacter(sprite_prota);
}

void prota::moveLeft(){

   sprite_prota->setAttributes(0,43,4);
    moveLeftCharacter(sprite_prota);
}



void prota::throwGrenade(QTimer *timer_grenade, QTimer *timer_burst,double y_inicial, double x_inicial, sprite *grenade) {


    grenade->moveParabolic(x_inicial,y_inicial);

  if (grenade->gety()-50 > y_inicial) {

        // Detener el temporizador y eliminar la granada
        grenade->setCont(0);
        timer_grenade->stop();
        scene->removeItem(grenade);
        delete grenade;
        delete timer_grenade;

        timer_burst->start(40);
    }

}



void prota::shoot(QTimer *t_prota_shoot){
    sprite_prota->setAttributes(53,64,5);
    methodCharacter(sprite_prota);
    if(sprite_prota->getCont() == 4) {
        sprite_prota->setCont(0);
        t_prota_shoot->stop();
    }
}

void prota::recharge(QTimer* t_prota_recharge, bool *block){


    sprite_prota->setAttributes(100,47,10);
    methodCharacter(sprite_prota);
    if(sprite_prota->getCont()==9){
         sprite_prota->setCont(0);
        t_prota_recharge->stop();
        *block=false;
    }
}

void prota::launch(QTimer* t_prota_lauch,bool *block){

    sprite_prota->setAttributes(200,42,7);
    methodCharacter(sprite_prota);
    if(sprite_prota->getCont()==6){
        sprite_prota->setCont(0);
        t_prota_lauch->stop();
        *block=false;
    }
}

void prota::setCont_bullets(){

    cont_bullets++;

}

int prota::getCont_bullets(){

    return cont_bullets;

}

int prota::getY(){

    return sprite_prota->gety();

}

int prota::getX()
{
    return sprite_prota->getx();
}


void prota::mover_derecha(QGraphicsPixmapItem *llanta_2)
{
    animation_counter_1++;
    if (animation_counter_1 == 6) animation_counter_1 = 0;
    mov_prota->setPixmap(movimiento_prota[animation_counter_1]);
    if (!mov_prota->collidesWithItem(llanta_2)) mov_prota->setX(mov_prota->x()+velocidad_personaje);

}

void prota::mover_izquierda(QGraphicsPixmapItem *llanta_1)
{
    animation_counter_2++;
    if (animation_counter_2 == 13) animation_counter_2 = 7;
    mov_prota->setPixmap(movimiento_prota[animation_counter_2]);
    if (!mov_prota->collidesWithItem(llanta_1)) mov_prota->setX(mov_prota->x()-velocidad_personaje);

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

void prota::seguimiento_mov(QVector2D pos_objeto, QTimer *timerMovMisil, QTimer *timerExplosion_misilAvion)
{
    animation_counter_8++;
    QVector2D pos_misil(mov_misiles_avion->pos().x(), mov_misiles_avion->pos().y());
    QVector2D direccion = pos_objeto - pos_misil;
    direccion.normalize();
    pos_misil += direccion*velocidad_misil_avion;


    if (animation_counter_8 == 7) animation_counter_8 = 0;
    mov_misiles_avion->setPixmap(movimiento_misiles_avion[animation_counter_8]);
    mov_misiles_avion->setX(pos_misil.x());
    mov_misiles_avion->setY(pos_misil.y());

    if (distancia(pos_misil, pos_objeto) < 10) {
        animation_counter_8 = 0;
        mov_misiles_avion->setY(pos_objeto.y() - 100);
        timerExplosion_misilAvion->start();
        timerMovMisil->stop();
    }
}

double prota::distancia(QVector2D vector1, QVector2D vector2)
{
    return (vector1 - vector2).length();

}

void prota::explosion(QTimer *timerExplosion_misilAvion, QTimer *timerEliminacionHelicopteros)
{
    animation_counter_7++;
    mov_misiles_avion->setPixmap(movimiento_misiles_avion[animation_counter_7]);
    if (animation_counter_7 == 38){
        animation_counter_7 = 15;
        timerExplosion_misilAvion->stop();
        timerEliminacionHelicopteros->start();
    }
}


void prota::firme(QTimer *timerFirme)
{
    animation_counter_4++;
    if (animation_counter_4 >= 25 && animation_counter_4 <= 32)
    mov_prota->setPixmap(movimiento_prota[animation_counter_4]);
    if (animation_counter_4 == 55) {
        timerFirme->stop();
        animation_counter_4 = 25;
    }
}

void prota::avion(unsigned int pos_y, QTimer *timerMisilesAvion)
{
    animation_counter_6++;
    t_seno+=0.01;
    if (t_seno == 0.01){
        y_inicial_1 = pos_y;
    }
    if (animation_counter_6 == 8) animation_counter_6 = 0;
    mov_avion->setPixmap(movimiento_avion[animation_counter_6]);
    double new_y = y_inicial_1 + amplitud * sin(2 *M_PI * frecuencia_ *t_seno);
    mov_avion->setY(new_y);
    mov_avion->setX(mov_avion->x() + 10);
    if (mov_avion->x() >= 150 && valid_put_misil){
        timerMisilesAvion->start();
        valid_put_misil = false;
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


void prota::dead(QTimer *timer_dead){



    sprite_prota->setAttributes(150,53,10);
    methodCharacter(sprite_prota);

    if(sprite_prota->getCont() ==9) {
        sprite_prota->setCont(0);
        timer_dead->stop();
    }

}





