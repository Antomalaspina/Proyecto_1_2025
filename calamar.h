#ifndef CALAMAR_H
#define CALAMAR_H

#include "alien.h"     // Incluye la clase base Alien, de la cual Calamar hereda

// Clase Calamar: enemigo derivado de Alien con su propio dibujo
class calamar : public Alien
{
public:
    // Constructor: inicializa un calamar con vida, posición y tamaño
    calamar(int vida_,float x_, float y_,float ancho_, float alto_);

    // Método que dibuja gráficamente al calamar
    void Dibujar(QPainter &P) override ;

    // Retorna el rectángulo que ocupa el calamar (para colisiones)
    QRectF get_area() const override;
};

#endif // CALAMAR_H

