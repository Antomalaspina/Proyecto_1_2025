#include "nave_enemiga.h"

Nave_enemiga::Nave_enemiga(float x_, float y_, bool direccion_derecha)
{
    x = x_;
    y = y_;
    ancho = 40.0f;
    alto = 15.0f;
    vida = 1;  // Muere con un solo disparo
    mover_derecha = direccion_derecha;
}

void Nave_enemiga::Dibujar(QPainter &P)
{
    P.setPen(Qt::red);
    P.setBrush(Qt::red);

    // Cuerpo principal (elipse alargada)
    QRectF cuerpo(x - ancho/2, y - alto/2, ancho, alto);
    P.drawEllipse(cuerpo);

    // Cúpula o cabina (círculo pequeño en el centro)
    P.setBrush(Qt::yellow);
    float radio_cupula = alto / 3;
    QRectF cupula(x - radio_cupula, y - alto/2 - radio_cupula/2, radio_cupula * 2, radio_cupula * 2);
    P.drawEllipse(cupula);

    // Alas o extensiones laterales
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
    return QRectF(x - ancho/2 - 5, y - alto/2, ancho + 10, alto);
}

void Nave_enemiga::movimiento()
{
    if (mover_derecha) {
        x += Vx;  // Mover hacia la derecha
    } else {
        x -= Vx;  // Mover hacia la izquierda
    }
}

bool Nave_enemiga::fuera_de_pantalla() const
{
    // Considerar que está fuera si sale completamente de la pantalla (800 de ancho)
    if (mover_derecha) {
        return x - ancho/2 > 800;  // Salió por la derecha
    } else {
        return x + ancho/2 < 0;    // Salió por la izquierda
    }
}
