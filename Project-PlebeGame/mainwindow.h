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
#include <vector>
#include <QGraphicsProxyWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QGraphicsScene *scene;
    QGraphicsView *view;
    Ui::MainWindow *ui;
    prota *marco;

    QTimer *t_prota_recharge,*t_prota_dead,*t_prota_shoot,*t_prota_throw;

    sprite *sprite_prota;
    sprite *sprite_enemy_rifle;

    std::vector<enemy*> enemys;
    std::vector<QTimer*> timer_enemy_move;
    std::vector<QGraphicsPixmapItem*> obstacleItems;

    QPixmap obstacle1;
    QPixmap obstacle2;

    QGraphicsPixmapItem* obstacleItem;

    unsigned int cont_obstacle=0;


    unsigned int num_obstacle;
    unsigned int num_enemys;
    unsigned int bullets_initial;
    unsigned int life_prota;
    unsigned int speed_prota;
    unsigned int grenades_prota;

    unsigned int life_enemy;
    unsigned int speed_enemy;

    bool verify_recharge=false;
    bool verify_coli;
    bool *block_move;
    bool *stop_timer_enemy;

    
    QGraphicsScene *escena_nivel_2, *pantalla_carga, *game_over, *pantalla_final, *pantalla_inicio;
    QPixmap *numeros, corazon;
    sprite sprite_aux;
    QGraphicsPixmapItem *fondo, *llanta_1, *pantalla_inicio_, *llanta_2, *telefono, *helicoptero_enemigo, *mensaje, *pantalla_carga_, *pantalla_final_, *time, *puntos, **numero_n, **corazon_n, *game_over_, *mensaje_2, **misiles_avion;
    prota walter, avion, avion_1;
    enemy nazi, nazi_1;
    QTimer *timerD, *timerA, *timerSpace, *timerPendulo, *timerMovimientoRecto, *timerIniciarPendulo, *timerDisparo, *timerMisil_circular, *timerSeguimiento, *timerFirme, *timerRebotar, *timerPantalla, *timerTemporizador, *timerExplosion, *timerMuerte, *timerStop, *timerGameOver, *timerFinalizar, *timerMisil_recto, *timerStartMisil_recto, *timerEliminacion, *timerAvion, *timerMisilesAvion, *timerMovMisil, *timerExplosion_misilAvion, *timerEliminar_helicoptero, *timerMovMisil_1, *timerExplosion_misilAvion_1, *timerEliminar_helicoptero_1, *timerPantallaFinal, *timerNivel_2;
    bool isDKeyPressed = false, helicoptero_1 = true, helicoptero_2 = true, isAKeyPressed = false, spacePressed = true, validKey = true, validKey_move  = true,  TeclaPressedA = true, TeclaPressedD = false, telefonoExist = true, validKey_move_ = true, valid = false, reproducir_animacion = false, reproducir_animacion_ = false, valid_rebotar = false, valid_delete = false, put_corazones = false, game_run = true, llanta_derecha = false, llanta_izquierda = false, valid_put_on_escene_misil = true, move_helicoptero = true, nivel_2 = false;
    int tiempo_restante = 120, life;
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
    void stop_nivel_1();
    void set_nivel_1();
    void juego();


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
    void PantallaFinal();
    void nivel2();
    
    //general
    void backGround();
    void setObstacles();
    void varAux();
    void addCharacteristics();
    void stopTimers();

    // prota
    void setProta();
    void rechargeProta();
    void shootProta();
    void greande();

    //enemy
    void shootEnemy(enemy *ene,QTimer *t_move);
    void setEnemys();
    void moveEnemyRandom();
    void bullet();
    void moveAndShootEnemy(enemy *ene,int i);

private slots:

    void moveView();


};
#endif // MAINWINDOW_H
