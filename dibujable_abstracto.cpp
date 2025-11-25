#include "dibujable_abstracto.h"

// Devuelve la coordenada X del objeto
float Dibujable_abstracto::get_x()
{
    return x;
}

// Devuelve la coordenada Y del objeto
float Dibujable_abstracto::get_y()
{
    return y;
}

// Devuelve el ancho del objeto
float Dibujable_abstracto::get_ancho()
{
    return ancho;
}

// Devuelve el alto del objeto
float Dibujable_abstracto::get_alto()
{
    return alto;
}
