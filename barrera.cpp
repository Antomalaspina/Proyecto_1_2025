#include "barrera.h"
#include <QPainter>

Barrera::Barrera(float Separacion_barrera, int vida_, float x_, float y_, float ancho_, float alto_){
    x=x_;
    y=y_;
    ancho=ancho_;
    alto=alto_;
    vida=vida_;
    Separacion_barrera=Separacion_barrera;
}


void Barrera::Dibujar(QPainter &P)

{
    // Solo dibujar si tiene vida
    if (vida <= 0) return;


    // Configurar colores según la vida restante (degradado de verde a rojo)
    QColor color_barrera;
    if (vida >= 8) {
        color_barrera = Qt::green;  // Verde brillante (10-8 vidas)
    } else if (vida >= 6) {
        color_barrera = QColor(150, 200, 50);  // Verde amarillento (7-6 vidas)
    } else if (vida >= 4) {
        color_barrera = QColor(200, 200, 0);  // Amarillo (5-4 vidas)
    } else if (vida >= 2) {
        color_barrera = QColor(255, 150, 0);  // Naranja (3-2 vidas)
    } else {
        color_barrera = QColor(255, 50, 0);  // Rojo (1 vida)
    }

    P.setPen(color_barrera);
    P.setBrush(color_barrera);

    // Dimensiones de la U invertida
    int grosor = ancho / 4;  // grosor de las paredes

    // Pilar izquierdo
    QRect pilarIzq(x - ancho/2, y - alto, grosor, alto);
    P.drawRect(pilarIzq);

    // Pilar derecho
    QRect pilarDer(x + ancho/2 - grosor, y - alto, grosor, alto);
    P.drawRect(pilarDer);

    // Techo superior (conecta los pilares)
    QRect techo(x - ancho/2, y - alto, ancho, grosor);
    P.drawRect(techo);
}
QRectF Barrera::get_area() const
{
    return QRectF(x - ancho/2, y - alto, ancho, alto);
}

void Barrera::recibir_danio(int danio)
{
    vida -= danio;
    if (vida <= 0) {
        set_colision(true);  // Marcar para eliminación
    }
}
