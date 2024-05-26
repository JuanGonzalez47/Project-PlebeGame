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
    scene->setSceneRect(0, 0, 1300, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1300 + 2 * ui->graphicsView->frameWidth(), 800 + 2 * ui->graphicsView->frameWidth());
    scene->addItem(move);  // Agregar el sprite a la escena
    move->setPos(200,200);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event){

    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:

        juan->moveLeftCharacter(move);

        break;
    case Qt::Key_D:

        juan->moveRightCharacter(move);

        break;
    case Qt::Key_W:
        //qDebug() << "Tecla: " << event->key();

        juan->moveUpCharacter(move);

        break;
    case Qt::Key_S:

        juan->moveDownCharacter(move);

        break;
    default:
        keyPressEvent(event);
    }

}


