#ifndef DIBUJABLE_ABSTRACTO_H
#define DIBUJABLE_ABSTRACTO_H

#include <QPainter>   // Para dibujar en pantalla usando Qt

// Clase abstracta para todos los objetos que se dibujan en pantalla
class Dibujable_abstracto
{
protected:
    int vida;        // Vida del objeto (si aplica)
    float x;         // Posición horizontal
    float y;         // Posición vertical
    float ancho;     // Ancho del sprite / figura
    float alto;      // Alto del sprite / figura

public:

    // Métodos getter para acceder a los atributos protegidos
    float get_x();
    float get_y();
    float get_ancho();
    float get_alto();

    // Método PURAMENTE virtual: toda clase derivada debe implementarlo
    virtual void Dibujar(QPainter &P)=0;
};

#endif // DIBUJABLE_ABSTRACTO_H
