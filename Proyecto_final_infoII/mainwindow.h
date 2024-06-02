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

public:

    void fondo();
    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    prota *juan;
    enemy *ene;


};
#endif // MAINWINDOW_H
