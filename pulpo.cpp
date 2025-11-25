#include "pulpo.h"
#include <QPainter>

// Constructor: llama directamente al constructor base Alien
Pulpo::Pulpo(int vida_, float x_, float y_, float ancho_, float alto_)
    : Alien(vida_, x_, y_, ancho_, alto_)
{
    // No hace falta más código: Alien inicializa todo
}

void Pulpo::Dibujar(QPainter &P)
{
    P.setPen(Qt::white);       // Contorno blanco
    P.setBrush(Qt::yellow);    // Color base del pulpo

    // Variables auxiliares para simplificar cálculos
    float mitad_ancho = ancho / 2.0f;
    float mitad_alto  = alto  / 2.0f;

    // ---- Cuerpo principal (rectángulo grande inferior) ----
    QRect cuerpo(QPoint(x - mitad_ancho, y - alto),
                 QPoint(x + mitad_ancho, y));
    P.drawRect(cuerpo);

    // ---- Cabeza (rectángulo más pequeño arriba del cuerpo) ----
    QRect cabeza(QPoint(x - mitad_ancho / 2, y - 1.5 * alto),
                 QPoint(x + mitad_ancho / 2, y - alto));
    P.drawRect(cabeza);

    // ---- Tentáculos inferiores ----
    // Se dibujan como columnas separadas debajo del cuerpo
    int num_tentaculos = 4;
    float separacion = ancho / (num_tentaculos + 1);
    float ancho_tentaculo = separacion / 2;

    for (int i = 0; i < num_tentaculos; i++) {

        // Posición x de cada tentáculo
        float x_tent = x - mitad_ancho + (i + 1) * separacion - ancho_tentaculo / 2;

        // Rectángulo del tentáculo
        QRect tentaculo(QPoint(x_tent, y),
                        QPoint(x_tent + ancho_tentaculo, y + alto / 1.5));
        P.drawRect(tentaculo);
    }

    // ---- Ojos del pulpo ----
    P.setBrush(Qt::black);

    float ojo_ancho = ancho / 8;
    float ojo_y = y - 0.7 * alto;   // Altura promedio para ojos

    // Ojo izquierdo
    P.drawRect(QRectF(x - 0.3 * ancho, ojo_y, ojo_ancho, ojo_ancho));

    // Ojo derecho
    P.drawRect(QRectF(x + 0.15 * ancho, ojo_y, ojo_ancho, ojo_ancho));
}

// Devuelve el área total del pulpo considerando cabeza y tentáculos
QRectF Pulpo::get_area() const
{
    // Altura total del pulpo: cabeza (1.5*alto) + tentáculos (alto/1.5)
    float altura_total = 1.5 * alto + alto / 1.5;

    // Devuelve área desde la cabeza hasta los tentáculos
    return QRectF(x - ancho/2, y - 1.5 * alto, ancho, altura_total);
}
