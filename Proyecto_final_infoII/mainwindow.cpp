#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    walter(5),
    nazi(5)

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
}

void MainWindow::set_mensaje()
{
    mensaje = new QGraphicsPixmapItem(sprite_aux.SetSprite(16).scaled(440,440));
    paint(1100,0,0,mensaje,escena_nivel_2);
}

//recordar bloquear los keys W Y S para el segundo nivel

void MainWindow::keyPressEvent(QKeyEvent *event){

    if (event->isAutoRepeat())return;

    //reiniciar el estado de la variable para activar el space

    if (!timerSpace->isActive() && !timerRebotar->isActive()){
        spacePressed = true;
        validKey_move  = true;
    }
    if (!timerFirme->isActive() && valid){
        validKey_move_ = true;
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
        walter.mover_derecha();
    }
}

void MainWindow::handleAKey()
{
    if (isAKeyPressed) {
        walter.mover_izquierda();
    }
}

void MainWindow::SpaceKey()
{
    reproducir_animacion = false;
    reproducir_animacion_ = false;
    timerRebotar->start();
    if (TeclaPressedA) walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,true,2,timerRebotar);
    else walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,false,2,timerRebotar);

}

void MainWindow::pendulo()
{
    nazi.pendulo_simple(nazi.get_mov_enemigo()->x(),nazi.get_mov_enemigo()->y(),timerPendulo,timerMovimientoRecto,timerIniciarPendulo,timerMisil);
}

void MainWindow::MovimientoRecto()
{
    nazi.Movimiento_recto();
}

void MainWindow::iniciar_secuencia()
{
    int tiempo_aleatorio = 20 + (rand() % 6);
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
    nazi.animacion_preparo_disparo(timerPendulo,timerDisparo);
}

void MainWindow::misil()
{
    unsigned int pos_x = nazi.get_mov_enemigo()->x() + 40;
    unsigned int pos_y = nazi.get_mov_enemigo()->y() + 120;
    paint(pos_x,pos_y,0,nazi.get_mov_misil(),escena_nivel_2);
    timerMisil->stop();
    timerMisil_circular->start();
}

void MainWindow::circular()
{
    nazi.movimiento_cirular(timerMisil_circular,nazi.get_mov_enemigo()->x(),nazi.get_mov_enemigo()->y(),timerSeguimiento);
}

void MainWindow::seguimiento()
{
    QVector2D pos_personaje(walter.get_mov_prota()->x(), walter.get_mov_prota()->y());
    nazi.seguimiento_mov(pos_personaje,timerSeguimiento);
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
            validKey_move_ = false;
            telefonoExist = false;
            valid = true;
            //agregar a la escena el conteo (disparo del timer y setar en las posiciones los dos puntos y el time)
            set_temporizador();
        }
    }
}

void MainWindow::rebotar()
{
    if (walter.get_mov_prota()->collidesWithItem(llanta_1) || reproducir_animacion){
        walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,false,3,timerRebotar);
        reproducir_animacion = true;
        reproducir_animacion_ = false;
    }
    else if (walter.get_mov_prota()->collidesWithItem(llanta_2) || reproducir_animacion_){
        walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace,true,3,timerRebotar);
        reproducir_animacion_ = true;
        reproducir_animacion = false;
    }
    else if (walter.get_mov_prota()->y() >= 600) timerRebotar->stop();
}


void MainWindow::set_temporizador()
{
    time = new QGraphicsPixmapItem(sprite_aux.SetSprite(6).scaled(90,50));
    paint(10,10,0,time,escena_nivel_2);
    puntos = new QGraphicsPixmapItem(sprite_aux.SetSprite(17).scaled(70,40));
    paint(153,15,0,puntos,escena_nivel_2);
    set_arreglo_numeros();
    timerTemporizador->start();
    //iniciar timer para llevar el conteo

}

void MainWindow::set_arreglo_numeros()
{
    numeros = new QPixmap [10];
    numero_n = new QGraphicsPixmapItem*[4];
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
        timerTemporizador->stop();
        //poner pantalla de game over
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
    //seteo de todos los timers
    set_timers();
    timerPantalla->start();
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
    timerMisil = new QTimer(this);
    timerIniciarPendulo = new QTimer(this);
    timerDisparo = new QTimer(this);
    timerMisil_circular = new QTimer(this);
    timerSeguimiento = new QTimer (this);
    timerFirme = new QTimer (this);
    timerRebotar = new QTimer(this);
    timerPantalla = new QTimer(this);
    timerTemporizador = new QTimer(this);
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
    timerMisil->setInterval(10);
    connect(timerTemporizador, &QTimer::timeout, this, &MainWindow::temporizador);
    connect(timerPantalla, &QTimer::timeout, this, &MainWindow::set_window);
    connect(timerRebotar, &QTimer::timeout, this, &MainWindow::rebotar);
    connect(timerFirme, &QTimer::timeout, this, &MainWindow::firme);
    connect(timerSeguimiento, &QTimer::timeout, this, &MainWindow::seguimiento);
    connect(timerMisil_circular, &QTimer::timeout, this, &MainWindow::circular);
    connect(timerMisil, &QTimer::timeout, this, &MainWindow::misil);
    connect(timerDisparo, &QTimer::timeout, this, &MainWindow::preparo_disparo);
    connect(timerIniciarPendulo, &QTimer::timeout, this, &MainWindow::iniciar_pendulo);
    connect(timerPendulo, &QTimer::timeout, this, &MainWindow::pendulo);
    connect(timerSpace, &QTimer::timeout, this, &MainWindow::SpaceKey);
    connect(timerA, &QTimer::timeout, this, &MainWindow::handleAKey);
    connect(timerD, &QTimer::timeout, this, &MainWindow::handleDKey);
    connect(timerMovimientoRecto, &QTimer::timeout, this, &MainWindow::MovimientoRecto);
}

