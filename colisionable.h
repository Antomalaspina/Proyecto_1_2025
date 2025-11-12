#ifndef COLISIONABLE_H
#define COLISIONABLE_H
#include "QRectF"

class colisionable
{
public:

    virtual ~colisionable() {}

    // Método virtual puro que cada clase debe implementar
    virtual QRectF get_area() const = 0;

    // Método de colisión que usa las áreas de ambos objetos
    bool CheckCollision(const colisionable* otroObjeto) const
    {
        QRectF miArea = get_area();
        QRectF otroArea = otroObjeto->get_area();

        return miArea.intersects(otroArea);
    }
    bool get_colision() const { return colisionado; }
     void set_colision(bool estado) { colisionado = estado; }
protected:
        bool colisionado = false;

};


#endif // COLISIONABLE_H
