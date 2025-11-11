#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>       // Clase base para interfaces gráficas
#include <QPaintEvent>   // Eventos de dibujo
#include <QKeyEvent>     // Eventos de teclado
#include <QTimer>        // Timer para actualizar el juego
#include "gamelogic.h"   // Lógica general del juego

// Widget principal donde se muestra y corre el juego
class GameWidget: public QWidget
{
    Q_OBJECT

private:
    QTimer *Tiempo_principal;  // Timer que controla los updates (frames)
    Gamelogic *logic;          // Objeto que contiene la lógica del juego

public:
    explicit GameWidget(QWidget *parent = nullptr); // Constructor

protected:
    void paintEvent(QPaintEvent *event) override;   // Redibuja la pantalla
    void keyPressEvent(QKeyEvent *event) override;  // Captura tecla presionada
    void keyReleaseEvent(QKeyEvent*) override;      // Captura tecla soltada

private slots:
    void actualizarJuego();  // Slot ejecutado por el timer
};

#endif // GAMEWIDGET_H
