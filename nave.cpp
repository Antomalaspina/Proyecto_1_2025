#include "nave.h"


#include "nave.h"

//------------------------------------------------------
// CONSTRUCTOR: inicializa la posición, tamaño y vida
//------------------------------------------------------
Nave::Nave(float pos_x, float pos_y) {
    x = pos_x;      // Coordenada X de la nave
    y = pos_y;      // Coordenada Y de la nave
    ancho = 30.0f;  // Ancho del sprite
    alto = 20.0f;   // Alto del sprite
    vida = 3;       // Vida inicial (3 golpes)
}

//------------------------------------------------------
// Movimiento horizontal basado en Vx
//------------------------------------------------------
void Nave::movimiento() {
    x += Vx;        // Desplaza la nave en el eje X
}

//------------------------------------------------------
// Dibujo completo de la nave usando rectángulos
//------------------------------------------------------
void Nave::Dibujar(QPainter &P) {
    // No dibujar si la nave ya está destruida
    if (vida <= 0) return;

    P.setPen(Qt::green);     // Contorno verde
    P.setBrush(Qt::green);   // Relleno verde

    // Base rectangular inferior
    QRect base(QPoint(x - 15, y - 8), QPoint(x + 15, y));
    P.drawRect(base);

    // parte superior más angosta
    QRect PartSup(QPoint(x - 8, y - 14), QPoint(x + 8, y - 8));
    P.drawRect(PartSup);

    // Cañón vertical
    QRect canon(QPoint(x - 2, y - 22), QPoint(x + 2, y - 14));
    P.drawRect(canon);
}

//------------------------------------------------------
// Área usada para colisiones (bounding box)
//------------------------------------------------------
QRectF Nave::get_area() const {
    return QRectF(x - 15, y - 22, 30, 22);
}

//------------------------------------------------------
// Creación de proyectiles del jugador
//------------------------------------------------------
proyectil* Nave::Disparar() {
    float x_proyectil = x;             // Centrado en la nave
    float y_proyectil = y - alto/2;    // Sale por arriba de la nave
    float ancho_proyectil = 3;
    float alto_proyectil = 10;
    float velocidad = -12;             // Negativa → se mueve hacia arriba

    // Se retorna un nuevo proyectil configurado
    return new proyectil(velocidad, 1,
                         x_proyectil,
                         y_proyectil,
                         ancho_proyectil,
                         alto_proyectil);
}

//------------------------------------------------------
// La nave recibe daño y reduce su cantidad de vida
//------------------------------------------------------
void Nave::recibir_danio(int danio) {
    vida -= danio;

    if (vida < 0) {
        vida = 0;   // Evita valores negativos
    }
}
