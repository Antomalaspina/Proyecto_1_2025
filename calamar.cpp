#include "calamar.h"
#include <QPainter>

calamar::calamar(int vida_, float x_, float y_, float ancho_, float alto_)
    : Alien(vida_, x_, y_, ancho_, alto_)
{
    vida= vida_;
    x=x_;
    y=y_;
    ancho=ancho_;
    alto=alto_;

}

void calamar::Dibujar(QPainter &P)
{
    // === CUERPO PRINCIPAL ===
    QPolygon cuerpo;
    cuerpo << QPoint(x, y - 2*alto)                     // Punta superior
           << QPoint(x + ancho/2, y - alto)             // Lado superior derecho
           << QPoint(x + ancho/3, y)                    // Tentáculo derecho superior
           << QPoint(x + ancho/6, y + alto/3)           // Tentáculo derecho inferior
           << QPoint(x - ancho/6, y + alto/3)           // Tentáculo izquierdo inferior
           << QPoint(x - ancho/3, y)                    // Tentáculo izquierdo superior
           << QPoint(x - ancho/2, y - alto);            // Lado superior izquierdo

    P.setPen(Qt::white);
    P.setBrush(Qt::blue);
    P.drawPolygon(cuerpo);

    // === TENTÁCULOS INFERIORES ===
    QPolygon tentaculos;
    tentaculos << QPoint(x - ancho/3, y + alto/3)
               << QPoint(x - ancho/4, y + alto/1.2)
               << QPoint(x - ancho/8, y + alto/3)
               << QPoint(x, y + alto/1.2)
               << QPoint(x + ancho/8, y + alto/3)
               << QPoint(x + ancho/4, y + alto/1.2)
               << QPoint(x + ancho/3, y + alto/3);

    P.drawPolygon(tentaculos);

    // === OJOS (con rectángulos explícitos para evitar ambigüedad) ===
    // Ojos blancos
    P.setBrush(Qt::white);
    P.drawEllipse(QRectF(x - ancho/4 - ancho/20, y - 2*alto - alto/16, ancho/10, alto/8)); // ojo izq
    P.drawEllipse(QRectF(x + ancho/4 - ancho/20, y - 2*alto - alto/16, ancho/10, alto/8)); // ojo der

    // Pupilas negras
    P.setBrush(Qt::black);
    P.drawEllipse(QRectF(x - ancho/4 - ancho/50, y - 2*alto - alto/30, ancho/25, alto/15)); // pupila izq
    P.drawEllipse(QRectF(x + ancho/4 - ancho/50, y - 2*alto - alto/30, ancho/25, alto/15)); // pupila der


}
QRectF calamar::get_area() const {

    // Calamar: desde y-2*alto (punta) hasta y+alto/1.2 (tentáculos)
    float altura_total = 2*alto + alto/1.2;
    return QRectF(x - ancho/2, y - 2*alto, ancho, altura_total);
}
