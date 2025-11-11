#include "pulpo.h"
#include <QPainter>

Pulpo::Pulpo(int vida_, float x_, float y_, float ancho_, float alto_)
    : Alien(vida_, x_, y_, ancho_, alto_)

{

}

void Pulpo::Dibujar(QPainter &P)
{
    P.setPen(Qt::white);
    P.setBrush(Qt::yellow);

    // Dimensiones base
    float mitad_ancho = ancho / 2.0f;
    float mitad_alto = alto / 2.0f;

    // ---- Cuerpo principal ----
    QRect cuerpo(QPoint(x - mitad_ancho, y - alto), QPoint(x + mitad_ancho, y));
    P.drawRect(cuerpo);

    // ---- Cabeza superior ----
    QRect cabeza(QPoint(x - mitad_ancho / 2, y - 1.5 * alto), QPoint(x + mitad_ancho / 2, y - alto));
    P.drawRect(cabeza);

    // ---- Tentáculos inferiores ----
    // Se dibujan como pequeñas columnas separadas
    int num_tentaculos = 4;
    float separacion = ancho / (num_tentaculos + 1);
    float ancho_tentaculo = separacion / 2;

    for (int i = 0; i < num_tentaculos; i++) {
        float x_tent = x - mitad_ancho + (i + 1) * separacion - ancho_tentaculo / 2;
        QRect tentaculo(QPoint(x_tent, y), QPoint(x_tent + ancho_tentaculo, y + alto / 1.5));
        P.drawRect(tentaculo);
    }

    // ---- Ojos ----
    P.setBrush(Qt::black);
    float ojo_ancho = ancho / 8;
    float ojo_y = y - 0.7 * alto;
    P.drawRect(QRectF(x - 0.3 * ancho, ojo_y, ojo_ancho, ojo_ancho));  // ojo izq
    P.drawRect(QRectF(x + 0.15 * ancho, ojo_y, ojo_ancho, ojo_ancho)); // ojo der

}
QRectF Pulpo::get_area() const
{
    // Desde y-1.5*alto (cabeza) hasta y+alto/1.5 (tentáculos)
    float altura_total = 1.5*alto + alto/1.5;
    return QRectF(x - ancho/2, y - 1.5*alto, ancho, altura_total);
}
