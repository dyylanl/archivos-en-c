#include <iostream>
 
class A {
private:
    std::string nombre;
    std::string texto;
public:
    A(const std::string nombre);            //Constructor por defecto de Clase    
    A(const A& copiable);                   //Constructor por Copia
    A(A&& copiable);                        //Constructor por movimiento
    A& operator=(const A& copiable);  //Sobrecarga del Operador asignación =
    A& operator=(A&& copiable);       //Sobrecarga del Operador asignación = por movimiento
    void mostrar() const;
};

//Constructor por defecto de Clase
A::A(const std::string nombre) {
    this->nombre = nombre;
    this->texto = "me creé con el Constructor de Clase";
}

//Constructor por Copia
A::A(const A& copiable) { 
    this->nombre = copiable.nombre;
    this->texto = "me creé con el Constructor por Copia";
}

//Constructor por movimiento
A::A(A&& copiable) {
    //Copio la informacion del objeto a destruir al nuevo objeto
    this->nombre = copiable.nombre;
    this->texto = "me creé con el Constructor por Movimiento";
    //Libero los recursos del objeto que se va a destruir
    copiable.nombre = "";
    copiable.texto = "";
}

//Sobrecarga del Operador asignación =
A& A::operator=(const A& copiable) {
    if (this != &copiable) { //Ahorro procesamiento para copiarme a contra mi mismo
        this->nombre = copiable.nombre;
        this->texto = "me reasigné con el Operador Asignación =";
    }
    return *this;
}

//Sobrecarga del Operador asignación = por movimiento
A& A::operator=(A&& copiable) {
    if (this != &copiable) { //Ahorro procesamiento para copiarme a contra mi mismo
        //Copio la informacion del objeto a destruir al nuevo objeto
        this->nombre = copiable.nombre;
        this->texto = "me reasigné con el Operador Asignación = por movimiento";
        //Libero los recursos del objeto que se va a destruir
        copiable.nombre = "";
        copiable.texto = "";
    }
    return *this;
}

void A::mostrar() const {
    std::cout << "Mi nombre es " << this->nombre << " y " << this->texto <<std::endl;
}

A foo(std::string nombre) {
    A a(nombre);
    return std::move(a); //Invoco al constructor por movimiento
}

int main() {
    A a1("Juan");       //Aplica el Constructor de Clase
    a1.mostrar();       // >>> "Mi nombre es Juan y me creé con el Constructor de Clase"

    A a2 = a1;          //Aplica el Constructor por Copia
    a2.mostrar();       // >>> "Mi nombre es Juan y me creé con el Constructor por Copia"
    
    A a3("Tomas");      //Aplica el Constructor de Clase
    a3.mostrar();       // >>> "Mi nombre es Tomas y me creé con el Constructor de Clase"
    a3 = a1;            //Aplica el Operador Asignación =
    a3.mostrar();       // >>> "Mi nombre es Juan y me reasigné con el Operador Asignación ="
    
    A a4 = foo("Teo");  //Aplica el Constructor por Movimiento
    a4.mostrar();       // >>> "Mi nombre es Teo y me creé con el Constructor por Movimiento"
    
    A a5("Jeronimo");   //Aplica el Constructor de Clase
    a5.mostrar();       // >>> "Mi nombre es Jeronimo y me creé con el Constructor de Clase"
    a5 = foo("Teo");    //Aplica el Operador Asignación = por Movimiento
    a5.mostrar();       // >>> "Mi nombre es Teo y me reasigné con el Operador Asignación = por Movimiento"
    return 0;
}
