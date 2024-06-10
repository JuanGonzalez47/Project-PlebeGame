#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "sprite.h"
#include "characters.h"
# include "charac_Prota.h"
#include "charac_enemy.h"
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //general
    void backGround();
    void setObstacles();
    void varAux();
    void keyPressEvent(QKeyEvent *event);

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
    unsigned int num_obstacle=60;
    unsigned int num_enemys=2;
    unsigned int bullets_initial=10;

    bool verify_recharge=false;
    bool verify_coli;
    bool *block_move;
    bool *stop_timer_enemy;



};
#endif // MAINWINDOW_H
