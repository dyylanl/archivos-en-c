/*
 * Declare una clase LEGAJO para encapsular un nro de legajo de un empleado.
 * Incluya al menos: Constructor default, Constructor con string de inicialización
 * y Constructor de Copia; Operador <, ==, = y << (impresión). Implemente el operator>.
 */

#include <iostream>
class Legajo {
private:
    int legajo;
public:
    //Constructores
    Legajo(const std::string legajo);       //Constructor default de clase
    Legajo(const Legajo& l);                //Constructor por copia
    //Sobrecarga operador asignacion
    Legajo& operator=(const Legajo& l);     //Operador asignacion=
    //Sobrecarga operadores de comparacion
    bool operator<(const Legajo& l) const;
    bool operator==(const Legajo& l) const;
    //Sobrecarga operadores << >> de cout y cin
    friend std::ostream& operator<<(std::ostream& os, const Legajo& l);
    friend std::istream& operator>>(std::istream& is, Legajo& l);
};
 
bool Legajo::operator<(const Legajo& l) const {
    if (this->legajo < l.legajo)
        return true;
    return false;
}