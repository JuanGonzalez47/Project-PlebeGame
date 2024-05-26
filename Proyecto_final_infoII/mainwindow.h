#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include "characters.h"

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

    void keyPressEvent(QKeyEvent *event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    sprite *move = new sprite(":/mov_prin.png", 0, 0, 110, 100, 9,200,200);
    charac *juan=new charac(2,2,5);

};
#endif // MAINWINDOW_H
