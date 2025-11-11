#include "gamewidget.h"// Incluye la declaración de la clase GameWidget y referencias a sus miembros.
#include <QPainter>// QPainter se usa para dibujar en el widget.
#include <QKeyEvent> // QKeyEvent proporciona información sobre eventos de teclado.
#include <QDebug> // QDebug para imprimir mensajes de depuración en la consola.

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) { // Constructor: crea el widget y llama al constructor de QWidget con el padre.
    setWindowTitle("Space Invaders"); // Establece el título de la ventana.
    resize(800, 600);// Tamaño inicial de la ventana (ancho x alto).
    setMinimumSize(400, 300);// Tamaño inicial de la ventana (ancho x alto).
    setFocusPolicy(Qt::StrongFocus); // Permite capturar teclas

    // Crear lógica del juego
    logic = new Gamelogic();// Instancia dinámica de la lógica principal del juego (responsable de la actualización del estado).

    // Configurar timer principal
    Tiempo_principal = new QTimer(this);  // Crea un QTimer; 'this' como padre asegura que se libere junto con el widget.
    Tiempo_principal->setInterval(30);  // 30 ms = ~33 FPS

    // Conectar el timer con el slot de actualización
    connect(Tiempo_principal, &QTimer::timeout, this, &GameWidget::actualizarJuego);
    Tiempo_principal->start();
}

void GameWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    // Dibujar fondo negro en toda la ventana
    painter.fillRect(rect(), Qt::black);
    painter.setRenderHint(QPainter::Antialiasing,true);
    // Configurar viewport para mantener aspect ratio 800x600
    float ancho_w = 800.0f;  // Ancho fijo del juego
    float alto_w = 600.0f;   // Alto fijo del juego

    float ratio_window = ancho_w / alto_w;
    float ratio_viewport = (float)this->width() / (float)this->height();

    float _width, _height;
    float ajuste_x, ajuste_y;

    if (ratio_window < ratio_viewport) {
        // La ventana es más ancha que el juego-> ajustar ancho
        _width = this->height() * ratio_window;
        _height = this->height();
        ajuste_x = (this->width() - _width) / 2.0f;
        ajuste_y = 0;
    } else {
        // La ventana es más alta que el juego-> ajustar alto
        _width = this->width();
        _height = this->width() / ratio_window;
        ajuste_x = 0;
        ajuste_y = (this->height() - _height) / 2.0f;
    }

    // area de dibujo
    painter.setViewport(ajuste_x, ajuste_y, _width, _height);

    painter.setWindow(0, 0, ancho_w, alto_w);

    logic->Dibujar(painter);
}

void GameWidget::actualizarJuego() {
     logic->actualizar();
     logic->Verificar_colisiones();
    update();  // Esto llama a paintEvent()
}

void GameWidget:: keyPressEvent(QKeyEvent* b){
    logic->Pressbutton(b);
}
void GameWidget:: keyReleaseEvent(QKeyEvent* b){
    logic->Releasebutton(b);
}
