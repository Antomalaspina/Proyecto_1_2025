#include "cangrejo.h"
#include <QPainter>

cangrejo::cangrejo(int vida_, float x_, float y_, float ancho_, float alto_, float separacion_alien)
    : Alien(separacion_alien, vida_, x_, y_, ancho_, alto_)
{
    vida=vida_;
    x=x_;
    y=y_;
    ancho=ancho_;
    alto=alto_;
    separacion_alien=separacion_alien;
}

void cangrejo::Dibujar(QPainter &P)
{
    P.setPen(Qt::white);
    P.setBrush(Qt::red);

    float mitad_ancho = ancho / 2.0f;
    float mitad_alto  = alto / 2.0f;

    // ---- Cuerpo principal ----
    QRect cuerpo(QPoint(x - mitad_ancho, y - alto), QPoint(x + mitad_ancho, y));
    P.drawRect(cuerpo);

    // ---- Cabeza o franja superior ----
    QRect franja(QPoint(x - mitad_ancho * 0.7, y - 1.5 * alto), QPoint(x + mitad_ancho * 0.7, y - alto));
    P.drawRect(franja);

    // ---- Pinzas laterales ----
    QRect pinza_izq(QPoint(x - mitad_ancho * 1.0, y - 0.6 * alto), QPoint(x - mitad_ancho * 0.7, y - 0.2 * alto));
    QRect pinza_der(QPoint(x + mitad_ancho * 0.7, y - 0.6 * alto), QPoint(x + mitad_ancho * 1.0, y - 0.2 * alto));
    P.drawRect(pinza_izq);
    P.drawRect(pinza_der);

    // ---- Patas inferiores ----
    int num_patas = 4;
    float separacion = ancho / (num_patas + 1);
    float ancho_pata = separacion / 3.0;

    for (int i = 0; i < num_patas; i++) {
        float x_pata = x - mitad_ancho + (i + 1) * separacion - ancho_pata / 2;
        QRect pata(QPoint(x_pata, y), QPoint(x_pata + ancho_pata, y + alto / 2.5));
        P.drawRect(pata);
    }

    // ---- Ojos (negros) ----
    P.setBrush(Qt::black);
    float ojo_ancho = ancho / 8;
    float ojo_y = y - 1.2 * alto;
    P.drawRect(QRectF(x - 0.25 * ancho, ojo_y, ojo_ancho, ojo_ancho));  // ojo izq
    P.drawRect(QRectF(x + 0.15 * ancho, ojo_y, ojo_ancho, ojo_ancho));  // ojo der

}
QRectF cangrejo::get_area() const
{
    // Desde y-1.5*alto (franja superior) hasta y+alto/2.5 (patas)
    float altura_total = 1.5*alto + alto/2.5;
    return QRectF(x - ancho/2, y - 1.5*alto, ancho, altura_total);
}
