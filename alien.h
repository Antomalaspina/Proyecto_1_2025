#ifndef ALIEN_H
#define ALIEN_H
// Guardas de inclusión para evitar inclusiones múltiples
//verificando github

#include "colisionable.h"
#include "movil.h"
#include "proyectil.h"
#include "dibujable_abstracto.h"

// La clase Alien hereda de múltiples clases (herencia múltiple):
// - colisionable: permite detectar colisiones con otros objetos
// - Dibujable_abstracto: permite que el alien sea dibujado en pantalla
// - movil: permite que el alien se mueva
class Alien : public colisionable, public Dibujable_abstracto, public movil
{
private:
    // (No hay atributos privados adicionales definidos aquí,
    // los atributos vienen de las clases base)

public:
    // Constructor que inicializa vida, posición (x,y) y dimensiones (ancho, alto)
    Alien(int vida_, float x_, float y_, float ancho_, float alto_);

    // Método que crea un proyectil disparado por el alien
    proyectil* Disparar();

    // Implementación del método movimiento() heredado de la clase movil
    // El 'override' indica que sobrescribe el método virtual de la clase base
    virtual void movimiento() override;
};

#endif // ALIEN_H
