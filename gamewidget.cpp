#include "gamewidget.h"
#include <QPainter>
#include <QKeyEvent>


GameWidget::GameWidget(QWidget *parent)
 : QWidget(parent) {
    setWindowTitle("Space Invaders");
    setFixedSize(800, 600); // Tamaño fijo de la ventana

    // Configurar el widget para recibir eventos de teclado
    setFocusPolicy(Qt::StrongFocus);

    // Inicializar timer (opcional, para futuras actualizaciones)
    Tiempo_principal = new QTimer(this);

    // Inicializar lógica del juego (opcional)
     logic = new Gamelogic();
}

void GameWidget::paintEvent(QPaintEvent * a){
    QPainter painter(this);

    // Dibujar fondo negro
    painter.fillRect(rect(), Qt::black);

    // Aquí puedes agregar más elementos de dibujo

    logic->Dibujar(painter);
}

void GameWidget:: KeyPressEvent(QKeyEvent* b){

}

