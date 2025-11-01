#ifndef ALIEN_H
#define ALIEN_H
#include "dibujable_abstracto.h"

class Alien : public Dibujable_abstracto
{
private:
    float separacion_alien;

public:
    Alien(float separacion_alien,int vida_,float x_, float y_,float ancho_, float alto_);
    void set_x(float x_alien_movimiento);
    void set_y(float y_alien_movimiento);
};

#endif // ALIEN_H
