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
    QTimer *Tiempo_principal;  // Timer que actualiza el juego
    Gamelogic *logic;          // Lógica del juego (nave, aliens, colisiones, etc.)

public:
    explicit GameWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;   // Redibuja pantalla
    void keyPressEvent(QKeyEvent *event) override;  // Captura teclas
    void keyReleaseEvent(QKeyEvent*) override;
private slots:
    void actualizarJuego();  // Slot que mueve enemigos y actualiza pantalla
};

#endif // GAMEWIDGET_H
