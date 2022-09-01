#include <iostream>
class Oracion {
private:
    char* a; //Almacena string terminado en null
public:
    Oracion(char* ptrA); //Constructor default
    Oracion(Oracion& o);    //Constructor por copia
    //Sobrecarga operatodes aritmeticos
    Oracion operator+(const Oracion& o);
    Oracion operator-(const Oracion& o);
    //Sobrecarga operadores << >>, Hipotesis, se utilizan para entrada y salida STDIN/OUT
    friend std::ostream& operator<<(std::ostream& os, const Oracion& o);
    friend std::istream& operator>>(std::istream& is, Oracion& o);
};

Oracion::Oracion(char* ptrA): a(ptrA){}

/*Oracion Oracion::operator-(const Oracion& o) {
   
}*/

int main() {
    char t1[] = "Hola";
    char t2[] = "Chau";
    Oracion unaOracion(t1);
    Oracion otraOracion(t2);
    unaOracion-otraOracion;
    return 0;
}