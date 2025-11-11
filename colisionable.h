#ifndef COLISIONABLE_H
#define COLISIONABLE_H

#include "QRectF"   // Clase de Qt que representa un rectángulo flotante (para colisiones)

// Clase base para cualquier objeto que pueda colisionar
class colisionable
{
public:

    virtual ~colisionable() {}   // Destructor virtual para permitir herencia limpia

    // Método virtual puro: cada clase derivada debe devolver su área de colisión
    virtual QRectF get_area() const = 0;

    // Método que verifica si este objeto colisiona con otro
    bool CheckCollision(const colisionable* otroObjeto) const
    {
        QRectF miArea = get_area();              // Obtiene mi área
        QRectF otroArea = otroObjeto->get_area(); // Obtiene el área del otro objeto

        return miArea.intersects(otroArea);      // Usa la función de Qt para ver si se superponen
    }

    // Get: devuelve si el objeto ya está marcado como colisionado
    bool get_colision() const { return colisionado; }

    // Set: marca o desmarca el estado de colisión
    void set_colision(bool estado) { colisionado = estado; }

protected:
    bool colisionado = false;  // Flag para indicar si hubo colisión
};

#endif // COLISIONABLE_H

