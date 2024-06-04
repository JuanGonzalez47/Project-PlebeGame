#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include "characters.h"
# include "charac_Prota.h"
#include "charac_enemy.h"
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene *escena_nivel_2, *pantalla_carga, *game_over;
    QPixmap *numeros;
    sprite sprite_aux;
    QGraphicsPixmapItem *fondo, *llanta_1, *llanta_2, *telefono, *helicoptero_enemigo, *mensaje, *pantalla_carga_, *time, *puntos, **numero_n;
    prota walter;
    enemy nazi;
    QTimer *timerD, *timerA, *timerSpace, *timerPendulo, *timerMovimientoRecto, *timerIniciarPendulo, *timerDisparo, *timerMisil, *timerMisil_circular, *timerSeguimiento, *timerFirme, *timerRebotar, *timerPantalla, *timerTemporizador;
    bool isDKeyPressed = false, isAKeyPressed = false, spacePressed = true, validKey = true, validKey_move  = true,  TeclaPressedA = true, TeclaPressedD = false, telefonoExist = true, validKey_move_ = true, valid = false, reproducir_animacion = false, reproducir_animacion_ = false, valid_rebotar = false;
    int tiempo_restante = 120;

public:

    void paint(unsigned int pos_x_to_paint,unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter, QGraphicsScene *escena);

    void setMapaNivel_2();
    void set_personaje_principal();
    void set_helicoptero_enemigo();
    void set_mensaje();
    void set_timers();
    void set_pantalla_carga();
    void set_window();
    void set_nivel_2();
    void set_temporizador();
    void set_arreglo_numeros();
    void temporizador();

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
    void iniciar_firme();
    void rebotar();

private:

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *juan;

};
#endif // MAINWINDOW_H
