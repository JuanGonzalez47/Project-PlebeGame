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

    QTimer *t_prota_recharge,*t_prota_dead,*t_prota_shoot;

    sprite *sprite_prota;
    sprite *sprite_enemy_rifle;

    std::vector<enemy*> enemys;

    std::vector<QGraphicsPixmapItem*> obstacleItems;

    std::vector<int> pos_obstacles_enemys;

    QPixmap *obstacles;
    QPixmap obstacle1;
    QPixmap obstacle2;

    QPixmap obstacleCopy;
    QGraphicsPixmapItem* obstacleItem;

    bool verify_coli;

    unsigned int cont_obstacle=0;
    unsigned int num_obstacle=15;
    unsigned int num_enemys=4;




public:

    // prota
    void rechargeProta();
    void shootProta(prota *prot);

    //enemy

    void shootEnemy(enemy *ene,QTimer *t_move);
    void moveAndShootEnemy(enemy *ene);
    void setEnemys();
    void moveEnemyRandom();

    void mousePressEvent(QMouseEvent *event);
    void bullet();

    void setObstacles();
    void keyPressEvent(QKeyEvent *event);
    explicit MainWindow(QWidget *parent = nullptr);


    ~MainWindow();
    void backGround();

private slots:
    void moveView();


private:

    QGraphicsScene *scene;
    QGraphicsView *view;
    Ui::MainWindow *ui;
    prota *marco;

};
#endif // MAINWINDOW_H
