#include "cangrejo.h"
#include <QPainter>       // Necesario para dibujar

// Constructor: inicializa el cangrejo llamando al constructor de Alien
cangrejo::cangrejo(int vida_, float x_, float y_, float ancho_, float alto_)
    : Alien(vida_, x_, y_, ancho_, alto_)   // Inicialización usando la clase base
{

}

// Método que dibuja gráficamente al cangrejo
void cangrejo::Dibujar(QPainter &P)
{
    P.setPen(Qt::white);   // Borde blanco
    P.setBrush(Qt::red);   // Relleno rojo para el cuerpo del cangrejo

    float mitad_ancho = ancho / 2.0f;
    float mitad_alto  = alto / 2.0f;

    // ---- Cuerpo principal ----
    // Rectángulo central del cuerpo
    QRect cuerpo(QPoint(x - mitad_ancho, y - alto),
                 QPoint(x + mitad_ancho, y));
    P.drawRect(cuerpo);

    // ---- Cabeza o franja superior ----
    // Franja más angosta en la parte superior
    QRect franja(QPoint(x - mitad_ancho * 0.7, y - 1.5 * alto),
                 QPoint(x + mitad_ancho * 0.7, y - alto));
    P.drawRect(franja);

    // ---- Pinzas laterales ----
    // Rectángulos a izquierda y derecha simulando garras
    QRect pinza_izq(QPoint(x - mitad_ancho * 1.0, y - 0.6 * alto),
                    QPoint(x - mitad_ancho * 0.7, y - 0.2 * alto));

    QRect pinza_der(QPoint(x + mitad_ancho * 0.7, y - 0.6 * alto),
                    QPoint(x + mitad_ancho * 1.0, y - 0.2 * alto));

    P.drawRect(pinza_izq);
    P.drawRect(pinza_der);

    // ---- Patas inferiores ----
    int num_patas = 4;                     // Número de patas a dibujar
    float separacion = ancho / (num_patas + 1);   // Distancia entre patas
    float ancho_pata = separacion / 3.0;          // Ancho de cada pata

    for (int i = 0; i < num_patas; i++) {
        float x_pata = x - mitad_ancho + (i + 1) * separacion - ancho_pata / 2;
        QRect pata(QPoint(x_pata, y),
                   QPoint(x_pata + ancho_pata, y + alto / 2.5));   // Patas dirigidas hacia abajo
        P.drawRect(pata);
    }

    // ---- Ojos ----
    P.setBrush(Qt::black);                 // Pupilas negras
    float ojo_ancho = ancho / 8;           // Tamaño de los ojos
    float ojo_y = y - 1.2 * alto;          // Posición vertical de los ojos

    // Ojo izquierdo
    P.drawRect(QRectF(x - 0.25 * ancho, ojo_y, ojo_ancho, ojo_ancho));

    // Ojo derecho
    P.drawRect(QRectF(x + 0.15 * ancho, ojo_y, ojo_ancho, ojo_ancho));
}

// Devuelve el área ocupada por el cangrejo (para colisiones)
QRectF cangrejo::get_area() const
{
    // Altura: desde la franja superior hasta el fin de las patas
    float altura_total = 1.5 * alto + alto / 2.5;

    // x - ancho/2 → lado izquierdo
    // y - 1.5*alto → punto más alto del cangrejo
    return QRectF(x - ancho/2, y - 1.5*alto, ancho, altura_total);
}

