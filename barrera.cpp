#include "barrera.h"
#include <QPainter>

// Constructor: inicializa todos los atributos de la barrera
Barrera::Barrera(float Separacion_barrera, int vida_, float x_, float y_, float ancho_, float alto_)
{
    x = x_;
    y = y_;
    ancho = ancho_;
    alto = alto_;
    vida = vida_;
    Separacion_barrera = Separacion_barrera;
}


// Método que dibuja la barrera en forma de U invertida
void Barrera::Dibujar(QPainter &P)
{
    // No dibujar si la barrera está destruida (sin vida)
    if (vida <= 0) return;

    // Sistema de degradado de color según la vida restante

    QColor color_barrera;
    if (vida >= 8) {
        color_barrera = Qt::green;  // Verde brillante (10-8 vidas) - casi intacta
    } else if (vida >= 6) {
        color_barrera = QColor(150, 200, 50);  // Verde amarillento (7-6 vidas)
    } else if (vida >= 4) {
        color_barrera = QColor(200, 200, 0);  // Amarillo (5-4 vidas) - daño medio
    } else if (vida >= 2) {
        color_barrera = QColor(255, 150, 0);  // Naranja (3-2 vidas) - muy dañada
    } else {
        color_barrera = QColor(255, 50, 0);  // Rojo (1 vida) - a punto de destruirse
    }

    // Configurar el color del pincel y el borde
    P.setPen(color_barrera);
    P.setBrush(color_barrera);

    // Calcular el grosor de las paredes (1/4 del ancho total)
    int grosor = ancho / 4;

    // Dibujar pilar izquierdo de la U invertida
    // Posición: desde la mitad izquierda, hacia arriba
    QRect pilarIzq(x - ancho/2, y - alto, grosor, alto);
    P.drawRect(pilarIzq);

    // Dibujar pilar derecho de la U invertida
    // Posición: en la mitad derecha, hacia arriba
    QRect pilarDer(x + ancho/2 - grosor, y - alto, grosor, alto);
    P.drawRect(pilarDer);

    // Dibujar techo superior que conecta ambos pilares
    // Forma la parte horizontal superior de la U invertida
    QRect techo(x - ancho/2, y - alto, ancho, grosor);
    P.drawRect(techo);
}

// Devuelve el área rectangular completa que ocupa la barrera
// Usado por el sistema de colisiones para detectar impactos
QRectF Barrera::get_area() const
{
    // Crea un rectángulo desde la esquina superior izquierda
    // con las dimensiones completas de la barrera
    return QRectF(x - ancho/2, y - alto, ancho, alto);
}

// Método que procesa el daño recibido por la barrera
void Barrera::recibir_danio(int danio)
{
    // Reduce la vida según el daño recibido
    vida -= danio;

    // Si la vida llega a 0 o menos, marca la barrera para eliminación
    if (vida <= 0) {
        set_colision(true);  // Activa flag de colisión para que sea removida del juego
    }
}
