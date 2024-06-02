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
    walter(5)

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
    ui->graphicsView->setFixedSize(size_screen_w,size_screen_h);
    escena_nivel_2->setSceneRect(0,0, size_screen_w - 5, size_screen_h - 5);
    ui->graphicsView->setScene(escena_nivel_2);
    //creacion del personaje principal del nivel 2
    //timers para que el movimiento del eprsonaje se vea fluido
    timerD = new QTimer(this);
    timerD->setInterval(100); // Intervalo en milisegundos
    connect(timerD, &QTimer::timeout, this, &MainWindow::handleDKey);
    if (true){ //agregar una condicion que se cumpla solo cuando pase el primer nivel
        //seteo del mapa del segundo nivel
        setMapaNivel_2();
        set_personaje_principal();
        //seteo del eprsonaje en la escena
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
    llanta_1 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,92));
    paint(0,685,0,llanta_1);
    llanta_2 = new QGraphicsPixmapItem(sprite_aux.SetSprite(10).scaled(223,92));
    paint(1300,685,0,llanta_2);
    telefono = new QGraphicsPixmapItem(sprite_aux.SetSprite(15).scaled(75,70));
    paint(1250,685,0,telefono);

}

void MainWindow::set_personaje_principal()
{
    paint(600,600,0,walter.get_mov_derecha());
}


void MainWindow::keyPressEvent(QKeyEvent *event){

    if (event->isAutoRepeat())return;

    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:

        juan->moveLeftProta();

        break;
    case Qt::Key_D:
        //juan->moveRihgtProta();
        if (!isDKeyPressed) {
            isDKeyPressed = true;
            handleDKey();
            timerD->start();
        }
        break;
        walter.mover_derecha();

        break;
    case Qt::Key_W:

        juan->moveUpProta();

        break;

    case Qt::Key_S:

        juan->moveDownProta();

        break;
    default:
        keyPressEvent(event);
    }


}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
    if (event->key() == Qt::Key_D) {
        isDKeyPressed = false;
        timerD->stop();
    }
}


void MainWindow::handleDKey()
{
    if (isDKeyPressed) {
        walter.mover_derecha();
    }
}
