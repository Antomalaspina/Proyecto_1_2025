#include "gamewidget.h"    // Cabecera de GameWidget
#include <QPainter>        // Para dibujar gráficos
#include <QKeyEvent>       // Para manejar teclado
#include <QDebug>          // Para debug por consola

//----------------------------------------------------
// CONSTRUCTOR DEL WIDGET PRINCIPAL
//----------------------------------------------------
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Space Invaders");  // Texto en la barra de título
    resize(800, 600);                  // Tamaño inicial de la ventana
    setMinimumSize(400, 300);          // Tamaño mínimo permitido
    setFocusPolicy(Qt::StrongFocus);   // Permite recibir eventos de teclado

    // Crear lógica central del juego
    logic = new Gamelogic();           // Maneja colisiones, aliens, nave, etc.

    // Crear timer que ejecuta la actualización al ritmo del juego
    Tiempo_principal = new QTimer(this);
    Tiempo_principal->setInterval(30); // 30 ms → ~33 FPS

    // Conecta el QTimer con la función actualizarJuego()
    connect(Tiempo_principal, &QTimer::timeout,
            this, &GameWidget::actualizarJuego);

    Tiempo_principal->start();         // Comienza a generar señales de timeout
}

//----------------------------------------------------
// paintEvent: Se llama automáticamente para repintar la escena
//----------------------------------------------------
void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  // Objeto que dibuja en el widget

    painter.fillRect(rect(), Qt::black); // Fondo negro del juego
    painter.setRenderHint(QPainter::Antialiasing, true); // Suaviza bordes

    // Dimensiones lógicas del juego (escenario 800x600)
    float ancho_w = 800.0f;
    float alto_w  = 600.0f;

    // Relación de aspecto ideal del juego
    float ratio_window = ancho_w / alto_w;

    // Relación de aspecto real de la ventana actual
    float ratio_viewport = (float)this->width() / (float)this->height();

    float _width, _height;
    float ajuste_x, ajuste_y;

    // Mantener aspect ratio evitando deformación de gráficos
    if (ratio_window < ratio_viewport) {
        // Ventana más ancha que el juego → ajustar ancho
        _width  = this->height() * ratio_window;
        _height = this->height();
        ajuste_x = (this->width() - _width) / 2.0f;
        ajuste_y = 0;
    } else {
        // Ventana más alta que el juego → ajustar alto
        _width  = this->width();
        _height = this->width() / ratio_window;
        ajuste_x = 0;
        ajuste_y = (this->height() - _height) / 2.0f;
    }

    // Fijar área donde se dibuja el juego manteniendo escala correcta
    painter.setViewport(ajuste_x, ajuste_y, _width, _height);

    // Definir sistema de coordenadas lógico 800x600
    painter.setWindow(0, 0, ancho_w, alto_w);

    // Delegar el dibujado completo a la lógica del juego
    logic->Dibujar(painter);
}

//----------------------------------------------------
// Slot llamado por el QTimer cada 30ms
//----------------------------------------------------
void GameWidget::actualizarJuego()
{
    logic->actualizar();          // Actualiza posiciones, estados y mecánicas
    logic->Verificar_colisiones();// Revisa colisiones cada frame

    update();  // Solicita repintar (dispara paintEvent)
}

//----------------------------------------------------
// Evento: tecla presionada
//----------------------------------------------------
void GameWidget::keyPressEvent(QKeyEvent* b)
{
    logic->Pressbutton(b);   // Reenvía el evento a la lógica del juego
}

//----------------------------------------------------
// Evento: tecla liberada
//----------------------------------------------------
void GameWidget::keyReleaseEvent(QKeyEvent* b)
{
    logic->Releasebutton(b); // Reenvía el evento a la lógica del juego
}
