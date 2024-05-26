#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sprites.h"
#include "characters.h"

#include <qdebug.h>
#include <QLabel>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0,0, 800, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1000+2  * ui->graphicsView->frameWidth(), 800+2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

    sprite *move = new sprite(ui->graphicsView);
    scene -> addItem(move);
    move->setPos(45,45);//PREGUNTAR
}




void MainWindow::keyPressEvent(QKeyEvent *event){


    sprite move(":/dispa-mov-personaje.png",0,0,110,100,300,300);

    //Manejo del evento de tecla
    switch(event->key()) {
        case Qt::Key_A:

            move.moveImage(-5,0);
            move.setSprite(9,0);

            break;
        case Qt::Key_D:

            move.moveImage(5,0);
            move.setSprite(9,0);

            break;
        case Qt::Key_W:

            move.moveImage(0,5);
            move.setSprite(9,0);
            break;
        case Qt::Key_S:

            move.moveImage(0,-5);
            move.setSprite(9,0);

            break;
    }
}




MainWindow::~MainWindow(){


    delete ui;
}
