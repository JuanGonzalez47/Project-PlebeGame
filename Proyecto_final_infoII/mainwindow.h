#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include "characters.h"
# include "charac_Prota.h"
#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

#define size_screen_w 1920
#define size_screen_h 1080

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


public:

    void paint(unsigned int pos_x_to_paint,unsigned int pos_y_to_paint, unsigned int z_value, QGraphicsPixmapItem *painter);
    void setMapaNivel_2();
    void set_personaje_principal();
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *juan;

};
#endif // MAINWINDOW_H
