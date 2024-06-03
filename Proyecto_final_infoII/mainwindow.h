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

    QTimer *t_prota_recharge,*t_prota_dead,*t_prota_shoot;
    QTimer *t_enemy_shoot,*t_enemy_move;
    sprite *sprite_prota;
    sprite *sprite_enemy_rifle;



public:

    // prota
    void rechargeProta();
    void shootProta();

    //enemy

    void shootEnemy(enemy *ene);
    void moveAndShootEnemy(enemy *ene);

    void fondo();
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:



    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *marco;

};
#endif // MAINWINDOW_H
