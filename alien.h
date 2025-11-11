#ifndef ALIEN_H
#define ALIEN_H
#include "colisionable.h"
#include "movil.h"
#include "proyectil.h"

#include "dibujable_abstracto.h"

class Alien : public colisionable,public Dibujable_abstracto,public movil
{
private:


public:
    Alien(int vida_,float x_, float y_,float ancho_, float alto_);

     proyectil* Disparar();
    //✅métodos de movil:
    virtual void movimiento() override;
};

#endif // ALIEN_H
