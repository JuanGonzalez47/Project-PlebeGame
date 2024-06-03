#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sprite.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
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




    juan=new prota(400,400,10,10,10,scene);

    ene1 = new enemy*[4];
    for(int i = 0; i < 4; ++i) {
        ene1[i] = new enemy();
    }

    for(int i=0;i<4;i++){
        ene1[i]->moveAndShoot();

    }

}

MainWindow::~MainWindow() {
    delete ui;
}


/*void MainWindow::fondo(){

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

}*/

void MainWindow::keyPressEvent(QKeyEvent *event){



    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:

        juan->moveLeftProta();

        break;
    case Qt::Key_D:

        juan->moveRihgtProta();

        break;
    case Qt::Key_W:

        juan->moveUpProta();

        break;

    case Qt::Key_S:

        juan->moveDownProta();

        break;

    case Qt::Key_R:

          juan->rechargeProta();

        break;

    case Qt::Key_Return:

        juan->shootProta();

        break;

    default:

        QMainWindow::keyPressEvent(event);
    }

}


