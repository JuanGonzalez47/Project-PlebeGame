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

    // prota
    void rechargeProta();
    void shootProta();

    //enemy

    void shootEnemy(enemy *ene,QTimer *t_move);
    void setEnemys();
    void moveEnemyRandom();
    void bullet();

    void setObstacles();
    void keyPressEvent(QKeyEvent *event);
    explicit MainWindow(QWidget *parent = nullptr);
    void greande();


    ~MainWindow();
    void backGround();

private slots:

    void moveView();
    void moveAndShootEnemy(enemy *ene,int i);



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

    std::vector<int> pos_obstacles_enemys;
    int pos_enemy=0;

    bool *stop_timer_enemy;

    QPixmap *obstacles;
    QPixmap obstacle1;
    QPixmap obstacle2;

  // bool *stop_timer;

    QPixmap obstacleCopy;
    QGraphicsPixmapItem* obstacleItem;

    bool verify_coli;

    unsigned int cont_obstacle=0;
    unsigned int num_obstacle=20;
    unsigned int num_enemys=20;

    bool *block_move;

    int posx;

};
#endif // MAINWINDOW_H
