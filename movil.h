#ifndef MOVIL_H
#define MOVIL_H
class Movil
{
protected:
    float Vy=0;
    float Vx=0;
public:
    //el destructor también taba en colisionable así que lo copio
    // virtual ~Movil();

    virtual void movimiento()=0;
    //Las hago abstractas para después usar los get_pos del resto de clases
    // virtual void mod_posX(float add_x)=0;
    // virtual void mod_posY(float add_y)=0;

    //Con esto se puede modificar la velocidad en cualquier momento sin necesidad
    //de modificar el constructor de las clases hijas
    void set_Vx(float Vx_){Vx=Vx_;}
    void set_Vy(float Vy_){Vy=Vy_;}
};

#endif // MOVIL_H
