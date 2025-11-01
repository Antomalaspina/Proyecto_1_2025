#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>
#include "gamelogic.h"

class GameWidget: public QWidget
{
    Q_OBJECT
private:
    QTimer * Tiempo_principal;
     Gamelogic *logic;
public:
    GameWidget(QWidget *parent =nullptr);// mi constructor instancia un objeto que apunta a Qwidget
    void paintEvent(QPaintEvent * );
    void keyPressEvent(QKeyEvent *);
    void actualizarJuego();
};

#endif // GAMEWIDGET_H
