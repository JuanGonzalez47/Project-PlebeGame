#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include "characters.h"
# include "charac_Prota.h"
#include "charac_enemy.h"
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene *escena_nivel_2;
    sprite sprite_aux;
    QGraphicsPixmapItem *fondo, *llanta_1, *llanta_2, *telefono, *helicoptero_enemigo, *mensaje;
    prota walter;
    enemy nazi;
    QTimer *timerD, *timerA, *timerSpace, *timerPendulo, *timerMovimientoRecto, *timerIniciarPendulo, *timerDisparo, *timerMisil, *timerMisil_circular, *timerSeguimiento, *timerFirme;
    bool isDKeyPressed = false, isAKeyPressed = false, spacePressed = true, validKey = true, validKey_move  = true,  TeclaPressedA = true, TeclaPressedD = false, telefonoExist = true;

public:

    void paint(unsigned int pos_x_to_paint,unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter);

    void setMapaNivel_2();
    void set_personaje_principal();
    void set_helicoptero_enemigo();
    void set_mensaje();
    void set_timers();
    void set_window();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleDKey();
    void handleAKey();
    void SpaceKey();
    void pendulo();
    void MovimientoRecto();
    void iniciar_secuencia();
    void iniciar_pendulo();
    void preparo_disparo();
    void misil();
    void circular();
    void seguimiento();
    void firme();

private:

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *juan;

};
#endif // MAINWINDOW_H
