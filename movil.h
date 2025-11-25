#ifndef MOVIL_H
#define MOVIL_H

// Clase abstracta que define objetos con velocidad y movimiento
class movil
{
protected:
    float Vy = 0;   // Velocidad vertical
    float Vx = 0;   // Velocidad horizontal

public:
    // Método virtual puro: las clases hijas deben implementar el movimiento
    virtual void movimiento() = 0;// aca declaro que es abstracta ya que cada forma de moverse depende de cada objeto

    // Setters de velocidad: permiten modificarla en tiempo real
    void set_Vx(float Vx_) { Vx = Vx_; }//recibe Vx_ que se lo asigna a Vx
    void set_Vy(float Vy_) { Vy = Vy_; }
};

#endif // MOVIL_H

