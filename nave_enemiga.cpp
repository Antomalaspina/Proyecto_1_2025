#include "nave_enemiga.h"

// Constructor: inicializa posición, tamaño, vida y dirección de movimiento
Nave_enemiga::Nave_enemiga(float x_, float y_, bool direccion_derecha)
{

}

void Nave_enemiga::Dibujar(QPainter &P)
{
    P.setPen(Qt::red);
    P.setBrush(Qt::red);

    // Cuerpo principal: elipse horizontal
    QRectF cuerpo(x - ancho/2, y - alto/2, ancho, alto);
    P.drawEllipse(cuerpo);

    // Cabina superior amarilla
    P.setBrush(Qt::yellow);
    float radio_cupula = alto / 3;
    QRectF cupula(
        x - radio_cupula,
        y - alto/2 - radio_cupula/2,
        radio_cupula * 2,
        radio_cupula * 2
        );
    P.drawEllipse(cupula);

    // Alas laterales rojas oscuras
    P.setBrush(Qt::darkRed);

    // Ala izquierda
    QRect ala_izq(x - ancho/2 - 5, y - alto/4, 5, alto/2);
    P.drawRect(ala_izq);

    // Ala derecha
    QRect ala_der(x + ancho/2, y - alto/4, 5, alto/2);
    P.drawRect(ala_der);
}

QRectF Nave_enemiga::get_area() const
{
    // Área de colisión ampliada para incluir alas
    return QRectF(
        x - ancho/2 - 5,  // margen para ala izq
        y - alto/2,
        ancho + 10,       // suma de ambas alas
        alto
        );
}

void Nave_enemiga::movimiento()
{
    // Movimiento horizontal basado en la dirección y la velocidad Vx
    if (mover_derecha) {
        x += Vx;  // Se mueve hacia la derecha
    } else {
        x -= Vx;  // Se mueve hacia la izquierda
    }
}

bool Nave_enemiga::fuera_de_pantalla() const
{
    // Considera pantalla fija de 800 px de ancho
    if (mover_derecha) {
        // Si va a la derecha, se considera fuera cuando su borde izquierdo supera 800
        return x - ancho/2 > 800;
    } else {
        // Si va a la izquierda, se considera fuera cuando su borde derecho baja de 0
        return x + ancho/2 < 0;
    }
}
