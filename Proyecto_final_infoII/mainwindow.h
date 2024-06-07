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
    QPixmap *numeros, corazon;
    sprite sprite_aux;
    QGraphicsPixmapItem *fondo, *llanta_1, *llanta_2, *telefono, *helicoptero_enemigo, *mensaje, *pantalla_carga_, *time, *puntos, **numero_n, **corazon_n, *game_over_, *mensaje_2, **misiles_avion;
    prota walter, avion, avion_1;
    enemy nazi, nazi_1;
    QTimer *timerD, *timerA, *timerSpace, *timerPendulo, *timerMovimientoRecto, *timerIniciarPendulo, *timerDisparo, *timerMisil_circular, *timerSeguimiento, *timerFirme, *timerRebotar, *timerPantalla, *timerTemporizador, *timerExplosion, *timerMuerte, *timerStop, *timerGameOver, *timerFinalizar, *timerMisil_recto, *timerStartMisil_recto, *timerEliminacion, *timerAvion, *timerMisilesAvion, *timerMovMisil, *timerExplosion_misilAvion, *timerEliminar_helicoptero, *timerMovMisil_1, *timerExplosion_misilAvion_1, *timerEliminar_helicoptero_1;
    bool isDKeyPressed = false, helicoptero_1 = true, helicoptero_2 = true, isAKeyPressed = false, spacePressed = true, validKey = true, validKey_move  = true,  TeclaPressedA = true, TeclaPressedD = false, telefonoExist = true, validKey_move_ = true, valid = false, reproducir_animacion = false, reproducir_animacion_ = false, valid_rebotar = false, valid_delete = false, put_corazones, game_run = true, llanta_derecha = false, llanta_izquierda = false, valid_put_on_escene_misil = true, move_helicoptero = true;
    int tiempo_restante = 5, life;
    unsigned int value = 5;

public:

    void paint(unsigned int pos_x_to_paint,unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter, QGraphicsScene *escena);

    void setMapaNivel_2();
    void set_personaje_principal();
    void set_helicoptero_enemigo();
    void set_avion();
    void set_mensaje();
    void set_timers();
    void set_pantalla_carga();
    void set_window();
    void set_nivel_2();
    void set_temporizador();
    void set_arreglo_numeros();
    void set_corazones();
    void set_mensaje_final();


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
    void misil_recto();
    void circular();
    void seguimiento();
    void firme();
    void iniciar_firme();
    void rebotar();
    void IniciarMovMisil();
    void delete_();
    void temporizador();
    void explosion();
    void muerte();
    void stop();
    void gameOver();
    void finalizarJuego();
    void IniciarAvion();
    void misiles_avion_();
    void MovMisil();
    void explosionMisilAvion();
    void Eliminar_helicoptero();
    void MovMisil_1();
    void explosionMisilAvion_1();
    void Eliminar_helicoptero_1();

private:

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *juan;

};
#endif // MAINWINDOW_H
