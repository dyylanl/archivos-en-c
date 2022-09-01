/* Declare la clase Número para almacenar un número de 100 cifras decimales.
 * Incluya: constructor default, constructor de copia, los operadores +,
 * ++ (posfijo),++ (prefijo), >, =, << (corrimiento de bits) y <<(impresión).
 * Implemente el operador <<(impresión). */

#include <iostream>
class Numero {
public:
    //Constructores: nunca retornan nada ni son metodos constantes
    Numero(double valor=0); //Constructor default
    Numero(const double& n); //Constructor por copia
    //Comparadores: const n para preservar el objeto original, retorna Numero& porque se modifica el 1er miembro.
    Numero& operator=(const Numero& n);  //Sobrecarga operador asignacion=
    bool operator>(const double& n) const;  //Sobrecarga operador >
    //Binarios aritmeticos, , ambos const es para preservar ambos miembros de la suma. Se retorna Numero porque se genera uno nuevo.
    Numero operator+(const double& n) const; //Sobrecarga operador +
    //Operadores de Incremento y decremento
    Numero& operator++(); //prefix, incrementamos *this y luego lo retornamos
    Numero operator++(int); //postfix, copiamos *this, incrementamos *this y luego retornamos la copia
    std::string getValor() const;
};
 
/*No se puede editar la clase std::cout ni std::cin entonces editamos
 * el operador global << y >> y pasamos de paràmetro ambos miembros.
 */
std::ostream& operator<<(std::ostream& os, const Numero& n); //n es const porque queremos preservar el dato.
std::istream& operator>>(std::istream& is, Numero& n); //n no es const porque se va a cargar informacion en él.
 
std::ostream& operator<<(std::ostream& os, const Numero& n) {
    os << n.getValor();
    return os;
}