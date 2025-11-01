#include "gamewidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Space Invaders");
    setFixedSize(800, 600);
    setFocusPolicy(Qt::StrongFocus);

    // SOLO UNA instancia del timer
    Tiempo_principal = new QTimer(this);
    Tiempo_principal->setInterval(30);  // 30ms

    // Conectar el timer
    connect(Tiempo_principal, &QTimer::timeout, this, &GameWidget::actualizarJuego);
    Tiempo_principal->start();

    // Inicializar lógica del juego
    logic = new Gamelogic();
}

void GameWidget::paintEvent(QPaintEvent * a){
    QPainter painter(this);

    // Dibujar fondo negro
    painter.fillRect(rect(), Qt::black);

    // Aquí puedes agregar más elementos de dibujo
    logic->Dibujar(painter);
}

void GameWidget::actualizarJuego() {
    update();  // Esto llama a paintEvent()
}

void GameWidget:: keyPressEvent(QKeyEvent* b){
    logic->Pressbutton(b);
}
