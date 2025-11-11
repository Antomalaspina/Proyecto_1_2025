#include "calamar.h"
#include <QPainter>    // Necesario para dibujar figuras

// Constructor: inicializa el calamar usando el constructor de Alien
calamar::calamar(int vida_, float x_, float y_, float ancho_, float alto_)
    : Alien(vida_, x_, y_, ancho_, alto_)     // Llamada al constructor de la clase base
{
    // Se reasignan los valores (aunque ya lo hace Alien)
    vida = vida_;
    x = x_;
    y = y_;
    ancho = ancho_;
    alto = alto_;
}

// Método principal de dibujo del calamar
void calamar::Dibujar(QPainter &P)
{
    // === CUERPO PRINCIPAL ===
    QPolygon cuerpo;
    cuerpo << QPoint(x, y - 2*alto)                     // Punta superior del calamar
           << QPoint(x + ancho/2, y - alto)             // Lado superior derecho
           << QPoint(x + ancho/3, y)                    // Tentáculo derecho superior
           << QPoint(x + ancho/6, y + alto/3)           // Tentáculo derecho inferior
           << QPoint(x - ancho/6, y + alto/3)           // Tentáculo izquierdo inferior
           << QPoint(x - ancho/3, y)                    // Tentáculo izquierdo superior
           << QPoint(x - ancho/2, y - alto);            // Lado superior izquierdo

    P.setPen(Qt::white);      // Línea blanca alrededor de la figura
    P.setBrush(Qt::blue);     // Relleno azul
    P.drawPolygon(cuerpo);    // Dibuja el cuerpo del calamar

    // === TENTÁCULOS INFERIORES ===
    QPolygon tentaculos;
    tentaculos << QPoint(x - ancho/3, y + alto/3)
               << QPoint(x - ancho/4, y + alto/1.2)
               << QPoint(x - ancho/8, y + alto/3)
               << QPoint(x, y + alto/1.2)
               << QPoint(x + ancho/8, y + alto/3)
               << QPoint(x + ancho/4, y + alto/1.2)
               << QPoint(x + ancho/3, y + alto/3);

    P.drawPolygon(tentaculos);  // Dibuja tentáculos inferiores

    // === OJOS ===
    // Ojos blancos
    P.setBrush(Qt::white);
    P.drawEllipse(QRectF(x - ancho/4 - ancho/20,        // Posición ojo izquierdo
                         y - 2*alto - alto/16,
                         ancho/10, alto/8));

    P.drawEllipse(QRectF(x + ancho/4 - ancho/20,        // Posición ojo derecho
                         y - 2*alto - alto/16,
                         ancho/10, alto/8));

    // Pupilas negras
    P.setBrush(Qt::black);
    P.drawEllipse(QRectF(x - ancho/4 - ancho/50,        // Pupila izquierda
                         y - 2*alto - alto/30,
                         ancho/25, alto/15));

    P.drawEllipse(QRectF(x + ancho/4 - ancho/50,        // Pupila derecha
                         y - 2*alto - alto/30,
                         ancho/25, alto/15));
}

// Devuelve el área rectangular del calamar, utilizada para detectar colisiones
QRectF calamar::get_area() const {

    // El calamar ocupa desde la punta superior hasta los tentáculos inferiores
    float altura_total = 2*alto + alto/1.2;

    // x - ancho/2: esquina izquierda
    // y - 2*alto: parte superior del cuerpo
    return QRectF(x - ancho/2, y - 2*alto, ancho, altura_total);
}

