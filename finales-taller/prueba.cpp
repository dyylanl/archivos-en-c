/* Declare una clase Patente para encapsular una patente de vehículo de Argentina.
 * Incluya al menos: Constructor default, Constructor con valor de inicialización
 * y Constructor de Copia; Operador <, ==, =, int (que devuelva la parte entera de
 * la patente) y << (impresión). Implemente el operator>. */

/*#include <iostream>
class Patente {
private:
    std::string patente;
public:
    Patente(const std::string p="AAA000");
    Patente(const Patente& p);
    
    bool operator<(const Patente& p) const;
    bool operator>(const Patente& p) const;
    bool operator==(const Patente& p) const;
    operator int();
    friend std::ostream& operator<<(std::ostream& os, const Patente& p);
};

Patente::Patente(const std::string p): patente(p) {}

bool Patente::operator<(const Patente& p) const {
    if (this->patente<p.patente)
        return true;
    return false;
}

bool Patente::operator>(const Patente& p) const {
    if (this->patente>p.patente)
        return true;
    return false;
}

bool Patente::operator==(const Patente& p) const {
    if (this->patente==p.patente)
        return true;
    return false;
}

Patente::operator int() {
    std::string tmp = this->patente.substr(3,3);
    int value = atoi(tmp.c_str());
    return value;
}

std::ostream& operator<<(std::ostream& os, const Patente& p) {
    os << p.patente;
    return os;
}

int main() {
    Patente p1("AAA999");
    Patente p2("BBB000");
    if (p2>p1)
        std::cout << p2 << " > " << p1 << std::endl;
    else
        std::cout << p2 << " < " << p1 << std::endl;
    
    std::cout << (int)p1 << std::endl;
    std::cout << (int)p2 << std::endl;
    return 0;
}*/

/*class A {
protected :
    int x;
public :
    int y;
public :
    A();
    ~A();
};*/
 
/*class B {
public :
    //B();
    //~B();
};

//A::A() {};
//A::~A() {};
//B::B() {};
//B::~B() {};
 
int main() {
    B* b2 = new B();
    delete b2;
    return 0;
}*/

/*class A {
public :
    A(){}
    ~A(){}
};

#include <list>
int main() {
    std::list<A> a = {1};
}*/

#include <stdio.h>
#define ASSERT(cond, msg) ((!cond) ? printf("Mensaje: %s\nNroLinea %d\n",msg,__LINE__) : printf("Test exitoso"))
#define ASSERT2(cond, msg) ((cond) ?: printf("Mensaje: %s\nNroLinea %d\n",msg,__LINE__))

int main() {
    int v = 0;
    ASSERT(v==1, "Mensaje");
    return 0;
}