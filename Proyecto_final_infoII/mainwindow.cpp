#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sprite.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    walter(5),
    nazi(5)

{
    ui->setupUi(this);

    /*QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1500, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1500+2* ui->graphicsView->frameWidth(),800+2* ui->graphicsView->frameWidth());

    QPixmap backgroundImage(":/escena_final2.png");
    //scene->addPixmap(backgroundImage);

    // Escalar la imagen de fondo (por ejemplo, 3x en X y 2x en Y)
    QPixmap scaledBackgroundImage = backgroundImage.scaled(
        backgroundImage.width() * 1.45,
        backgroundImage.height() * 2,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    // Crear un QGraphicsPixmapItem con la imagen escalada
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(scaledBackgroundImage);

    // Agregar el QGraphicsPixmapItem a la escena
    scene->addItem(background);
    background->setPos(0, 170);

    juan=new prota(2,2,5,scene);

    // scene->addItem(move);  // Agregar el sprite a la escena
    // move->setPos(200,200);*/

    //QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    //se define la escena en la cual se cargara el nivel 2
    escena_nivel_2 = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    //scene->setSceneRect(0,0, 800, 800);

    //ui->graphicsView->setScene(scene);
    //ui->graphicsView->setFixedSize(1000+2  * ui->graphicsView->frameWidth(), 800+2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

    //relaxion de aspecto del nivel 2
    ui->graphicsView->setFixedSize(size_screen_w ,size_screen_h);
    escena_nivel_2->setSceneRect(0,0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(escena_nivel_2);
    //creacion del personaje principal del nivel 2
    //timers para que el movimiento del eprsonaje se vea fluido
    timerD = new QTimer(this);
    timerA = new QTimer(this);
    timerPendulo = new QTimer(this);
    timerMovimientoRecto = new QTimer(this);
    timerSpace = new QTimer(this);
    timerIniciarPendulo = new QTimer(this);
    timerDisparo = new QTimer(this);
    timerDisparo->setInterval(100);
    timerMovimientoRecto->setInterval(60);
    timerPendulo->setInterval(1);
    timerSpace->setInterval(1);
    timerA->setInterval(100);
    timerD->setInterval(100);
    connect(timerDisparo, &QTimer::timeout, this, &MainWindow::preparo_disparo);
    connect(timerIniciarPendulo, &QTimer::timeout, this, &MainWindow::iniciar_pendulo);
    connect(timerPendulo, &QTimer::timeout, this, &MainWindow::pendulo);
    connect(timerSpace, &QTimer::timeout, this, &MainWindow::SpaceKey);
    connect(timerA, &QTimer::timeout, this, &MainWindow::handleAKey);
    connect(timerD, &QTimer::timeout, this, &MainWindow::handleDKey);
    connect(timerMovimientoRecto, &QTimer::timeout, this, &MainWindow::MovimientoRecto);

    if (true){ //agregar una condicion que se cumpla solo cuando pase el primer nivel
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
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::paint(unsigned int pos_x_to_paint, unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter)
{
    painter->setPos(pos_x_to_paint,pos_y_to_paint);
    painter->setZValue(z_value);
    escena_nivel_2->addItem(painter);
    ui->graphicsView->setScene(escena_nivel_2);
}

void MainWindow::setMapaNivel_2()
{
    //setear fondo
    fondo = new QGraphicsPixmapItem(sprite_aux.SetSprite(0).scaled(ui->graphicsView->width(),ui->graphicsView->height()));
    paint(0,0,0,fondo);
    //seteo de objetos en el fondo (llantas y el telefono)
    llanta_1 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,150));
    paint(0,685,0,llanta_1);
    llanta_2 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,150));
    paint(1300,685,0,llanta_2);
    telefono = new QGraphicsPixmapItem(sprite_aux.SetSprite(15).scaled(75,70));
    paint(1250,685,0,telefono);
}

void MainWindow::set_personaje_principal()
{
    paint(600,600,0,walter.get_mov_prota());
}

void MainWindow::set_helicoptero_enemigo()
{
    paint(600,0,0,nazi.get_mov_enemigo());
}

//recordar bloquear los keys W Y S para el segundo nivel

void MainWindow::keyPressEvent(QKeyEvent *event){

    if (event->isAutoRepeat())return;

    //reiniciar el estado de la variable para activar el space

    if (!timerSpace->isActive()) spacePressed = true;

    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:
        //juan->moveLeftProta();
        if (!isAKeyPressed) {
            isAKeyPressed = true;
            handleAKey();
            timerA->start();
        }
        break;
    case Qt::Key_D:
        //juan->moveRihgtProta();
        if (!isDKeyPressed) {
            isDKeyPressed = true;
            handleDKey();
            timerD->start();
        }
        break;
    case Qt::Key_W:

        juan->moveUpProta();

        break;

    case Qt::Key_S:

        juan->moveDownProta();

        break;
    case Qt::Key_Space:
        if (spacePressed){
            SpaceKey();
            timerSpace->start();
            spacePressed = false;
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
    walter.movimiento_parabolico(velocidad_personaje,walter.get_mov_prota()->y() + 10,walter.get_mov_prota()->x() + 10,timerSpace);
}

void MainWindow::pendulo()
{
    nazi.pendulo_simple(nazi.get_mov_enemigo()->x(),nazi.get_mov_enemigo()->y(),timerPendulo,timerMovimientoRecto,timerIniciarPendulo);
}

void MainWindow::MovimientoRecto()
{
    nazi.Movimiento_recto();
}

void MainWindow::iniciar_secuencia()
{
    int tiempo_aleatorio = 20 + (rand() % 6);
    timerIniciarPendulo->start(tiempo_aleatorio * 1000);
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



