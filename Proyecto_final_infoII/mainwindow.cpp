#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    walter(5),
    avion(value),
    avion_1(value),
    nazi(5),
    nazi_1(5)

{
    ui->setupUi(this);


    if (true){ //agregar una condicion que se cumpla solo cuando pase el primer nivel
        //bloquear teclas de movimiento, w s (desactivar las otras)
        validKey = false;
        set_pantalla_carga();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::paint(unsigned int pos_x_to_paint, unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter, QGraphicsScene *escena)
{
    painter->setPos(pos_x_to_paint,pos_y_to_paint);
    painter->setZValue(z_value);
    escena->addItem(painter);
    ui->graphicsView->setScene(escena);
}

void MainWindow::setMapaNivel_2()
{
    //setear fondo
    fondo = new QGraphicsPixmapItem(sprite_aux.SetSprite(0).scaled(ui->graphicsView->width(),ui->graphicsView->height()));
    paint(0,0,0,fondo,escena_nivel_2);
    //seteo de objetos en el fondo (llantas y el telefono)
    llanta_1 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,150));
    paint(0,685,0,llanta_1,escena_nivel_2);
    llanta_2 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,150));
    paint(1300,685,0,llanta_2,escena_nivel_2);
    telefono = new QGraphicsPixmapItem(sprite_aux.SetSprite(15).scaled(75,70));
    paint(1250,685,0,telefono,escena_nivel_2);
}

void MainWindow::set_personaje_principal()
{
    paint(600,600,1,walter.get_mov_prota(),escena_nivel_2);
}

void MainWindow::set_helicoptero_enemigo()
{
    paint(600,0,0,nazi.get_mov_enemigo(),escena_nivel_2);
    paint(600,0,0,nazi_1.get_mov_enemigo(),escena_nivel_2);

}

void MainWindow::set_avion()
{
    paint(0,100,1,avion.get_mov_avion(),escena_nivel_2);
}

void MainWindow::set_mensaje()
{
    mensaje = new QGraphicsPixmapItem(sprite_aux.SetSprite(16).scaled(440,440));
    paint(1100,0,0,mensaje,escena_nivel_2);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
    if (event->key() == Qt::Key_D) {
        isDKeyPressed = false;
        timerD->stop();
    }
    if (event->key() == Qt::Key_A) {
        isAKeyPressed = false;
        timerA->stop();
    }
}


void MainWindow::handleDKey()
{
    if (isDKeyPressed) {
        walter.mover_derecha(llanta_2);
    }
}

void MainWindow::handleAKey()
{
    if (isAKeyPressed) {
        walter.mover_izquierda(llanta_1);
    }
}

void MainWindow::SpaceKey()
{
    reproducir_animacion = false;
    reproducir_animacion_ = false;
    valid = false;
    timerRebotar->start();
    if (TeclaPressedA) walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,true,2,timerRebotar);
    else walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,false,2,timerRebotar);

}

void MainWindow::pendulo()
{
    nazi.pendulo_simple(nazi.get_mov_enemigo()->x(),nazi.get_mov_enemigo()->y(),timerPendulo,timerMovimientoRecto,timerIniciarPendulo,timerMisil_circular);
    nazi_1.pendulo_simple(nazi_1.get_mov_enemigo()->x(),nazi_1.get_mov_enemigo()->y(),timerPendulo,timerMovimientoRecto,timerIniciarPendulo,timerMisil_circular);
}

void MainWindow::MovimientoRecto()
{
    if (move_helicoptero && helicoptero_1 && helicoptero_2){
        nazi.Movimiento_recto(timerMisil_recto,true,false);
        nazi_1.Movimiento_recto(timerMisil_recto,false,false);
    }
    else if (helicoptero_2 && helicoptero_1){
        nazi.Movimiento_recto(timerMisil_recto,true,true);
        nazi_1.Movimiento_recto(timerMisil_recto,false,true);
    }

}

void MainWindow::iniciar_secuencia()
{
    int tiempo_aleatorio = 10 + (rand() % 11);
    timerIniciarPendulo->start(tiempo_aleatorio*1000);
}

void MainWindow::iniciar_pendulo()
{
    timerMovimientoRecto->stop();
    timerIniciarPendulo->stop();
    preparo_disparo();
    timerDisparo->start();
}

void MainWindow::preparo_disparo()
{
    nazi.animacion_preparo_disparo(timerPendulo,timerDisparo,timerMisil_recto);
    nazi_1.animacion_preparo_disparo(timerPendulo,timerDisparo,timerMisil_recto);
}

void MainWindow::misil()
{
    valid_delete = false;
    if (valid_put_on_escene_misil){
        nazi.set_mov_misil();
        nazi_1.set_mov_misil();
        unsigned int pos_x = nazi.get_mov_enemigo()->x() + 40;
        unsigned int pos_y = nazi.get_mov_enemigo()->y() + 120;
        unsigned int pos_x_ = nazi_1.get_mov_enemigo()->x() + 40;
        unsigned int pos_y_ = nazi_1.get_mov_enemigo()->y() + 120;
        paint(pos_x_,pos_y_,1,nazi_1.get_mov_misil(),escena_nivel_2);
        paint(pos_x,pos_y,1,nazi.get_mov_misil(),escena_nivel_2);
    }
}

void MainWindow::misil_recto()
{
    misil();
    timerStartMisil_recto->start();
    valid_put_on_escene_misil = false;

}

void MainWindow::circular()
{
    misil();
    nazi.movimiento_cirular(timerMisil_circular,nazi.get_mov_enemigo()->x(),nazi.get_mov_enemigo()->y(),timerSeguimiento);
    nazi_1.movimiento_cirular(timerMisil_circular,nazi_1.get_mov_enemigo()->x(),nazi_1.get_mov_enemigo()->y(),timerSeguimiento);
    valid_put_on_escene_misil = false;

}

void MainWindow::seguimiento()
{
    if (llanta_derecha){
        QVector2D pos_objeto(llanta_1->x(), llanta_1->y());
        nazi.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,false,walter,false);
        nazi_1.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,false,walter,false);
    }
    else if (llanta_izquierda){
        QVector2D pos_objeto(llanta_2->x(), llanta_2->y());
        nazi.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,false,walter,false);
        nazi_1.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,false,walter,false);
    }
    else{
        QVector2D pos_objeto(walter.get_mov_prota()->x(), walter.get_mov_prota()->y());
        nazi.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,true,walter,true);
        nazi_1.seguimiento_mov(pos_objeto,timerSeguimiento,timerExplosion,timerMuerte,true,walter,true);
    }
}

void MainWindow::firme()
{
    walter.firme(timerFirme);
}

void MainWindow::iniciar_firme()
{
    if (telefonoExist){
        if ((walter.get_mov_prota()->x() + 100) >= telefono->x()){
            set_mensaje();
            escena_nivel_2->removeItem(telefono);
            timerFirme->start();
            validKey_move = false;
            telefonoExist = false;
            valid = true;
            set_temporizador();
        }
    }
}

void MainWindow::rebotar()
{

    // agregar una condicion que evalue esto si y solo si esta saltando
    if (walter.get_mov_prota()->collidesWithItem(llanta_1) || reproducir_animacion){
        walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,false,3,timerRebotar);
        reproducir_animacion = true;
        reproducir_animacion_ = false;
        if (timerSeguimiento->isActive()) llanta_derecha = true;
    }
    else if (walter.get_mov_prota()->collidesWithItem(llanta_2) || reproducir_animacion_){
        walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,true,3,timerRebotar);
        reproducir_animacion_ = true;
        reproducir_animacion = false;
        if (timerSeguimiento->isActive()) llanta_izquierda = true;
    }
    else if (walter.get_mov_prota()->y() >= 600) timerRebotar->stop();

}

void MainWindow::IniciarMovMisil()
{
    QVector2D pos_objeto(walter.get_mov_prota()->x(), walter.get_mov_prota()->y());
    nazi.misil_recto(timerExplosion,pos_objeto,timerMuerte,true);
    nazi_1.misil_recto(timerExplosion,pos_objeto,timerMuerte,true);

}

void MainWindow::delete_()
{
   escena_nivel_2->removeItem(nazi.get_mov_misil());
   escena_nivel_2->removeItem(nazi_1.get_mov_misil());
   valid_put_on_escene_misil = true;
   timerEliminacion->stop();
}


void MainWindow::set_temporizador()
{
    time = new QGraphicsPixmapItem(sprite_aux.SetSprite(6).scaled(90,50));
    paint(10,10,0,time,escena_nivel_2);
    puntos = new QGraphicsPixmapItem(sprite_aux.SetSprite(17).scaled(70,40));
    paint(153,15,0,puntos,escena_nivel_2);
    set_arreglo_numeros();
    timerTemporizador->start();

}

void MainWindow::set_arreglo_numeros()
{
    put_corazones = true;
    numeros = new QPixmap [10];
    corazon = sprite_aux.SetSprite(18);
    numero_n = new QGraphicsPixmapItem*[4];
    corazon_n = new QGraphicsPixmapItem*[5];
    for (unsigned int x = 0; x < 10; x++) {
        numeros[x] = sprite_aux.set_sprite_for_animation(x,0,7,47,72);
    }
    numero_n[0] = new QGraphicsPixmapItem(numeros[0].scaled(35,40));
    numero_n[1] = new QGraphicsPixmapItem(numeros[0].scaled(35,40));
    numero_n[2] = new QGraphicsPixmapItem(numeros[0].scaled(35,40));
    numero_n[3] = new QGraphicsPixmapItem(numeros[0].scaled(35,40));

    paint(117,18,0,numero_n[0],escena_nivel_2);
    paint(146,18,0,numero_n[1],escena_nivel_2);
    paint(192,18,0,numero_n[2],escena_nivel_2);
    paint(220,18,0,numero_n[3],escena_nivel_2);

    corazon_n[0] = new QGraphicsPixmapItem(corazon.scaled(35,35));
    corazon_n[1] = new QGraphicsPixmapItem(corazon.scaled(35,35));
    corazon_n[2] = new QGraphicsPixmapItem(corazon.scaled(35,35));
    corazon_n[3] = new QGraphicsPixmapItem(corazon.scaled(35,35));
    corazon_n[4] = new QGraphicsPixmapItem(corazon.scaled(35,35));

    paint(10,60,0,corazon_n[0],escena_nivel_2);
    paint(50,60,0,corazon_n[1],escena_nivel_2);
    paint(90,60,0,corazon_n[2],escena_nivel_2);
    paint(130,60,0,corazon_n[3],escena_nivel_2);
    paint(170,60,0,corazon_n[4],escena_nivel_2);

}

void MainWindow::set_corazones()
{
    switch (life) {
    case 4: escena_nivel_2->removeItem(corazon_n[4]);
        break;
    case 3: escena_nivel_2->removeItem(corazon_n[3]);
        break;
    case 2: escena_nivel_2->removeItem(corazon_n[2]);
        break;
    case 1: escena_nivel_2->removeItem(corazon_n[1]);
        break;
    }
}

void MainWindow::set_mensaje_final()
{
    move_helicoptero = false;
    timerTemporizador->stop();
    timerMovimientoRecto->stop();
    timerMovimientoRecto->start();
    timerMisil_recto->stop();
    timerIniciarPendulo->stop();

    mensaje_2 = new QGraphicsPixmapItem(sprite_aux.SetSprite(19).scaled(440,440));
    paint(1100,0,0,mensaje_2,escena_nivel_2);
}

void MainWindow::temporizador()
{
    if (tiempo_restante > 0){

        int minutos = tiempo_restante / 60;
        int segundos = tiempo_restante % 60;

        numero_n[0]->setPixmap(numeros[minutos / 10].scaled(35, 40));
        numero_n[1]->setPixmap(numeros[minutos % 10].scaled(35, 40));
        numero_n[2]->setPixmap(numeros[segundos / 10].scaled(35, 40));
        numero_n[3]->setPixmap(numeros[segundos % 10].scaled(35, 40));

        --tiempo_restante;
    }
    else {

        set_mensaje_final();
        set_avion();
        timerAvion->start();

        //activar timer para realizar la animacion de la muerte de los otros dos helicopteros (activar  un timer que haga la animacion de los helicopteros pero no se mueva)

    }
}

void MainWindow::explosion()
{
    valid_delete = true;
    nazi.explosion(timerExplosion, timerStartMisil_recto, timerEliminacion);
    nazi_1.explosion(timerExplosion, timerStartMisil_recto, timerEliminacion);
}

void MainWindow::muerte()
{
    if (walter.get_life() == 1 || telefonoExist){
        game_run = false;
        timerStop->start();
        timerSpace->stop();
        timerRebotar->stop();
        if (TeclaPressedA) walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,false,timerMuerte,timerGameOver);
        else walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,true,timerMuerte,timerGameOver);
    }
    else {
        life = walter.get_life();
        walter.set_life(--life);
        set_corazones();
        timerMuerte->stop();
    }

}

void MainWindow::stop()
{
    if (put_corazones){
        escena_nivel_2->removeItem(corazon_n[0]);
        escena_nivel_2->removeItem(corazon_n[1]);
        escena_nivel_2->removeItem(corazon_n[2]);
        escena_nivel_2->removeItem(corazon_n[3]);
        escena_nivel_2->removeItem(corazon_n[4]);
        timerTemporizador->stop();
        timerStop->stop();
    }
}



void MainWindow::keyPressEvent(QKeyEvent *event){

    if (game_run){
        if (event->isAutoRepeat())return;

        if (!timerMisil_circular->isActive() && !timerStartMisil_recto->isActive()) valid_put_on_escene_misil = true;

        if (!timerSeguimiento){
            llanta_derecha = false;
            llanta_derecha = false;
        }

        if (!timerExplosion->isActive() && valid_delete){
            llanta_izquierda = false;
            llanta_derecha = false;
        }

        if (!timerSpace->isActive() && !timerRebotar->isActive() && !timerFirme->isActive()){
            spacePressed = true;
            validKey_move  = true;
        }
        if (!timerFirme->isActive() && valid){
            validKey_move = true;
            escena_nivel_2->removeItem(mensaje);
        }

        //Manejo del evento de tecla
        switch(event->key()) {
        case Qt::Key_A:
            if (!isAKeyPressed && validKey_move && validKey) {
                isAKeyPressed = true;
                TeclaPressedA = true;
                handleAKey();
                timerA->start();
            }
            break;
        case Qt::Key_D:
            if (!isDKeyPressed && validKey_move && validKey) {
                isDKeyPressed = true;
                TeclaPressedA = false;
                handleDKey();
                timerD->start();
                iniciar_firme();
            }
            break;
        case Qt::Key_W:
            if (validKey){
            }

            break;

        case Qt::Key_S:
            if (validKey){
            }
            break;
        case Qt::Key_Space:
            if (spacePressed && validKey_move && validKey){
                SpaceKey();
                timerSpace->start();
                spacePressed = false;
                validKey_move  = false;
            }
            break;
        }
    }

}

void MainWindow::set_pantalla_carga()
{
    pantalla_carga = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(size_screen_w, size_screen_h);
    pantalla_carga->setSceneRect(0, 0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(pantalla_carga);
    pantalla_carga_ = new QGraphicsPixmapItem(sprite_aux.SetSprite(1).scaled(ui->graphicsView->width(),ui->graphicsView->height()));
    paint(0,0,0,pantalla_carga_,pantalla_carga);
    set_timers();
    timerPantalla->start();
}

void MainWindow::gameOver()
{
    timerMisil_recto->stop();
    timerIniciarPendulo->stop();
    game_over = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(size_screen_w, size_screen_h);
    game_over->setSceneRect(0, 0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(game_over);
    game_over_ = new QGraphicsPixmapItem(sprite_aux.SetSprite(5).scaled(ui->graphicsView->width(),ui->graphicsView->height()));
    paint(0,0,0,game_over_,game_over);
    timerFinalizar->start();
}

void MainWindow::finalizarJuego()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::IniciarAvion()
{
    avion.avion(100,timerMisilesAvion);
}

void MainWindow::misiles_avion_()
{
    paint(avion.get_mov_avion()->x(), avion.get_mov_avion()->y(), 1, avion.get_mov_misiles_avion(), escena_nivel_2);
    paint(avion.get_mov_avion()->x(), avion.get_mov_avion()->y(), 1, avion_1.get_mov_misiles_avion(), escena_nivel_2);

    timerMisilesAvion->stop();
    timerMovMisil->start();
    timerMovMisil_1->start();
}

void MainWindow::MovMisil()
{
    QVector2D pos_objeto(nazi.get_mov_enemigo()->x(), nazi.get_mov_enemigo()->y());
    avion.seguimiento_mov(pos_objeto,timerMovMisil,timerExplosion_misilAvion);

}

void MainWindow::MovMisil_1()
{
    QVector2D pos_objeto_(nazi_1.get_mov_enemigo()->x(), nazi_1.get_mov_enemigo()->y());
    avion_1.seguimiento_mov(pos_objeto_,timerMovMisil_1,timerExplosion_misilAvion_1);

}


void MainWindow::explosionMisilAvion()
{
    avion.explosion(timerExplosion_misilAvion,timerEliminar_helicoptero);
}

void MainWindow::explosionMisilAvion_1()
{
    avion_1.explosion(timerExplosion_misilAvion_1,timerEliminar_helicoptero_1);
    game_run = false;
    timerFirme->start();

}


void MainWindow::Eliminar_helicoptero()
{
    helicoptero_1 = false;
    escena_nivel_2->removeItem(nazi.get_mov_enemigo());
    timerEliminar_helicoptero->stop();
}

void MainWindow::Eliminar_helicoptero_1()
{
    timerMisil_circular->stop();
    timerEliminar_helicoptero_1->stop();
    timerMovimientoRecto->stop();
    helicoptero_2 = false;
    escena_nivel_2->removeItem(nazi_1.get_mov_enemigo());
    timerPantallaFinal->start();

}

void MainWindow::PantallaFinal()
{
    pantalla_final = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(size_screen_w, size_screen_h);
    pantalla_final->setSceneRect(0, 0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(pantalla_final);
    pantalla_final_ = new QGraphicsPixmapItem(sprite_aux.SetSprite(20).scaled(ui->graphicsView->width(),ui->graphicsView->height()));
    paint(0,0,0,pantalla_final_,pantalla_final);
    timerFinalizar->start();
}

void MainWindow::set_window()
{
    escena_nivel_2 = new QGraphicsScene(this);
    escena_nivel_2->setSceneRect(0, 0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(escena_nivel_2);
    timerPantalla->stop();
    set_nivel_2();

}

void MainWindow::set_nivel_2()
{
    //habilitar teclas
    validKey = true;
    //seteo del mapa del segundo nivel
    setMapaNivel_2();
    //seteo del eprsonaje en la escena
    set_personaje_principal();
    //seteo del helicoptero enemigo
    set_helicoptero_enemigo();
    MovimientoRecto();
    timerMovimientoRecto->start();
    iniciar_secuencia();

}


void MainWindow::set_timers()
{
    timerD = new QTimer(this);
    timerA = new QTimer(this);
    timerPendulo = new QTimer(this);
    timerMovimientoRecto = new QTimer(this);
    timerSpace = new QTimer(this);
    timerIniciarPendulo = new QTimer(this);
    timerDisparo = new QTimer(this);
    timerMisil_circular = new QTimer(this);
    timerSeguimiento = new QTimer (this);
    timerFirme = new QTimer (this);
    timerRebotar = new QTimer(this);
    timerPantalla = new QTimer(this);
    timerTemporizador = new QTimer(this);
    timerExplosion = new QTimer(this);
    timerMuerte = new QTimer(this);
    timerGameOver = new QTimer(this);
    timerStop = new QTimer(this);
    timerFinalizar = new QTimer(this);
    timerMisil_recto = new QTimer(this);
    timerStartMisil_recto = new QTimer (this);
    timerEliminacion = new QTimer(this);
    timerAvion = new QTimer(this);
    timerMisilesAvion = new QTimer(this);
    timerMovMisil = new QTimer(this);
    timerExplosion_misilAvion = new QTimer(this);
    timerEliminar_helicoptero = new QTimer(this);
    timerMovMisil_1 = new QTimer(this);
    timerExplosion_misilAvion_1 = new QTimer(this);
    timerEliminar_helicoptero_1 = new QTimer(this);
    timerPantallaFinal = new QTimer(this);


    timerPantallaFinal->setInterval(3000);
    timerExplosion_misilAvion_1->setInterval(16);
    timerEliminar_helicoptero_1->setInterval(1);
    timerMovMisil_1->setInterval(20);
    timerExplosion_misilAvion->setInterval(16);
    timerEliminar_helicoptero->setInterval(1);
    timerMovMisil->setInterval(20);
    timerMisilesAvion->setInterval(1);
    timerAvion->setInterval(30);
    timerEliminacion->setInterval(1);
    timerStartMisil_recto->setInterval(20);
    timerMisil_recto->setInterval(1000);
    timerFinalizar->setInterval(1000);
    timerGameOver->setInterval(1000);
    timerStop->setInterval(1);
    timerMuerte->setInterval(1);
    timerExplosion->setInterval(16);
    timerTemporizador->setInterval(1000);
    timerPantalla->setInterval(5000);
    timerPantalla->setInterval(5000);
    timerRebotar->setInterval(1);
    timerFirme->setInterval(100);
    timerSeguimiento->setInterval(25);
    timerDisparo->setInterval(100);
    timerMovimientoRecto->setInterval(60);
    timerPendulo->setInterval(1);
    timerSpace->setInterval(1);
    timerA->setInterval(100);
    timerD->setInterval(100);
    timerMisil_circular->setInterval(1);


    connect(timerPantallaFinal, &QTimer::timeout, this, &MainWindow::PantallaFinal);
    connect(timerExplosion_misilAvion_1, &QTimer::timeout, this, &MainWindow::explosionMisilAvion_1);
    connect(timerEliminar_helicoptero_1, &QTimer::timeout, this, &MainWindow::Eliminar_helicoptero_1);
    connect(timerMovMisil_1, &QTimer::timeout, this, &MainWindow::MovMisil_1);
    connect(timerExplosion_misilAvion, &QTimer::timeout, this, &MainWindow::explosionMisilAvion);
    connect(timerEliminar_helicoptero, &QTimer::timeout, this, &MainWindow::Eliminar_helicoptero);
    connect(timerMovMisil, &QTimer::timeout, this, &MainWindow::MovMisil);
    connect(timerMisilesAvion, &QTimer::timeout, this, &MainWindow::misiles_avion_);
    connect(timerAvion, &QTimer::timeout, this, &MainWindow::IniciarAvion);
    connect(timerEliminacion, &QTimer::timeout, this, &MainWindow::delete_);
    connect(timerStartMisil_recto, &QTimer::timeout, this, &MainWindow::IniciarMovMisil);
    connect(timerMisil_recto, &QTimer::timeout, this, &MainWindow::misil_recto);
    connect(timerFinalizar, &QTimer::timeout, this, &MainWindow::finalizarJuego);
    connect(timerStop, &QTimer::timeout, this, &MainWindow::stop);
    connect(timerGameOver, &QTimer::timeout, this, &MainWindow::gameOver);
    connect(timerMuerte, &QTimer::timeout, this, &MainWindow::muerte);
    connect(timerExplosion, &QTimer::timeout, this, &MainWindow::explosion);
    connect(timerTemporizador, &QTimer::timeout, this, &MainWindow::temporizador);
    connect(timerPantalla, &QTimer::timeout, this, &MainWindow::set_window);
    connect(timerRebotar, &QTimer::timeout, this, &MainWindow::rebotar);
    connect(timerFirme, &QTimer::timeout, this, &MainWindow::firme);
    connect(timerSeguimiento, &QTimer::timeout, this, &MainWindow::seguimiento);
    connect(timerMisil_circular, &QTimer::timeout, this, &MainWindow::circular);
    connect(timerDisparo, &QTimer::timeout, this, &MainWindow::preparo_disparo);
    connect(timerIniciarPendulo, &QTimer::timeout, this, &MainWindow::iniciar_pendulo);
    connect(timerPendulo, &QTimer::timeout, this, &MainWindow::pendulo);
    connect(timerSpace, &QTimer::timeout, this, &MainWindow::SpaceKey);
    connect(timerA, &QTimer::timeout, this, &MainWindow::handleAKey);
    connect(timerD, &QTimer::timeout, this, &MainWindow::handleDKey);
    connect(timerMovimientoRecto, &QTimer::timeout, this, &MainWindow::MovimientoRecto);
}

