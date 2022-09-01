// Declare la clase COMPLEJO, incluyendo operadores aritméticos, lógicos y de entrada/salida.
/*
 * Declare una clase Complejo para encapsular un nro. complejo. Incluya al menos:
 * Constructor default, Constructor con valores de inicialización y Constructor de Copia;
 * Operador <, ==, =, int (que devuelva la parte real del nro. encapsulado) y << (impresión).
 * Implemente el operator<<.
 */
// Compilar con: g++ -std=c++11 1.cpp -o 1
// Ejecutar con: ./1
// Escribir por ejemplo: 10 -20    (10 para la parte real y -20 para la parte imaginaria)

#include <iostream>

class Complejo {
private:
    float real;
    float imaginario;
public:
    //Constructores y operadores de asignacion
    Complejo(const float real = 0, const float imaginario = 0); //Constructor default de Clase (y con valores de inicializacion)
    //Complejo(const Complejo& copiable); //Constructor de copia
    //Complejo& operator=(const Complejo& copiable); //Sobrecarga de Operador Asignacion=
    //Sobrecarga de Operadores
    Complejo operator+(const Complejo& c2) const;
    Complejo operator-(const Complejo& c2) const;
    bool operator==(const Complejo& c2) const;
    bool operator!=(const Complejo& c2) const;
    bool operator<(const Complejo& c2) const;
    Complejo& operator++();                                //prefix ++, ej ++a
    Complejo operator++(int);                              //postfix ++, ej a++
    operator bool() const;
    operator int() const;
    //Operadores globales con acceso privado a ésta.
    friend std::ostream& operator<<(std::ostream& output, const Complejo& c);
    friend std::istream& operator>>(std::istream& input, Complejo& c);
};

//Prototipos de sobrecarga de operadores globales
std::ostream& operator<<(std::ostream& output, const Complejo& c);
std::istream& operator>>(std::istream& input, Complejo& c);

//Definiciones de métodos y funciones
Complejo::Complejo(const float real, const float imaginario) {
    this->real = real;
    this->imaginario = imaginario;
}

Complejo Complejo::operator+(const Complejo& c2) const {
    float parteReal = this->real + c2.real;
    float parteImaginaria = this->imaginario + c2.imaginario;
    return Complejo(parteReal, parteImaginaria);
}

Complejo Complejo::operator-(const Complejo& c2) const { 
    float parteReal = this->real - c2.real;
    float parteImaginaria = this->imaginario - c2.imaginario;
    return Complejo(parteReal, parteImaginaria);
}

bool Complejo::operator==(const Complejo& c2) const {
    if ((this->real == c2.real) and (this->imaginario == c2.imaginario))
        return true;
    return false;
}

bool Complejo::operator!=(const Complejo& c2) const {
    if ((this->real != c2.real) or (this->imaginario != c2.imaginario))
        return true;
    return false;
}

Complejo& Complejo::operator++() {
    this->real++;
    this->imaginario++;
    return *this;
}

Complejo Complejo::operator++(int) {
    Complejo temp = *this;
    this->real++;
    this->imaginario++;
    return temp;
}

Complejo::operator bool() const {
    //No se indica el tipo de retorno porque queda claro que debe ser bool
    if ((this->real!=0) or (this->imaginario!=0))
        return true; //Cualquier otro caso
    return false; //Si es 0+0i
}

Complejo::operator int() const {
    //No se indica el tipo de retorno porque queda claro que debe ser int
    return (int)this->real;
}

//Sobrecarga de operadores globales << y >> con acceso privado a la clase Complejo
//friend va sólo en la declaracion en la clase Complejo
std::ostream& operator<<(std::ostream& output, const Complejo& c) { 
    char signo = '+';
    float r = c.real;
    float i = c.imaginario;
    if (i<0) { //Signo - e invierno i para que quede positivo
        signo = '-'; 
        i = -i;
    }
    output << std::to_string(r) << signo << std::to_string(i) << "i" ;
    return output;            
}

//friend va sólo en la declaracion en la clase Complejo
std::istream& operator>>(std::istream& input, Complejo& c) {
    input >> c.real >> c.imaginario;
    return input;            
}

int main(){
    Complejo c1(4, 4); //c1= 2+2i
    Complejo c2(1, 1); //c2= 1+1i
    Complejo c3; //c3= 0+0i
    std::cin >> c3; //c3 << cin (standart input)
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c1+c2: " << c1+c2 << std::endl;
    std::cout << "c1-c2: " << c1-c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    if (c1 == c1)
        std::cout << c1 << " = " << c1 << std::endl;
    if (c1 != c2)
        std::cout << c1 << " != " << c2 << std::endl;
       
    std::cout << "(bool)Complejo(0,0): " << (bool)Complejo(0,0) << std::endl;
    std::cout << "(bool)Complejo(0,1): " << (bool)Complejo(0,1) << std::endl;
    
    Complejo c4(4, 4); //c1= 2+2i
    Complejo c6(4, 4); //c2= 1+1i
    
    Complejo c5 = ++c4;
    std::cout << "c4: " << c4 << std::endl;
    std::cout << "c5: " << c5 << std::endl;
    
    Complejo c7 = c6++;
    std::cout << "c6: " << c6 << std::endl;
    std::cout << "c7: " << c7 << std::endl;
    
    std::cout << "(int)c1: " << (int)c1 << std::endl;
    std::cout << "++(++(c1+c2)): " << ++(++(c1+c2)) << std::endl; //Funciona por sacar los retornos const
    return 0;
}