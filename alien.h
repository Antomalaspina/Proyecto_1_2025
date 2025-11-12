#ifndef ALIEN_H
#define ALIEN_H
#include "colisionable.h"
#include "movil.h"
#include "proyectil.h"

#include "dibujable_abstracto.h"

class Alien : public colisionable,public Dibujable_abstracto, public Movil
{
private:
    float separacion_alien;

public:
    Alien(float separacion_alien,int vida_,float x_, float y_,float ancho_, float alto_);
    // void set_x(float x_alien_movimiento);
    // void set_y(float y_alien_movimiento);
    proyectil* Disparar();
    //✅métodos de movil:
    virtual void movimiento() override;
    //Las hago abstractas para después usar los get_pos del resto de clases
    // virtual void mod_posX(float add_x) override;
    // virtual void mod_posY(float add_y) override;
};

#endif // ALIEN_H
