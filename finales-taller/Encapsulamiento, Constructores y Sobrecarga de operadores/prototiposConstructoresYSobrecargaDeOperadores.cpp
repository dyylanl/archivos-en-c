class Complejo {
private:
    float real;
    float imaginario;
public: 
    //Constructores y operadores de asignacion
    Complejo(const float real=0, const float imaginario=0); //Constructor por defecto de Clase
    Complejo(const Complejo& copiable);                     //Constructor por Copia
    Complejo(Complejo&& copiable);                          //Constructor por movimiento
    Complejo& operator=(const Complejo& copiable);          //Sobrecarga del Operador asignación =
    Complejo& operator=(Complejo&& copiable);               //Sobrecarga del Operador asignación = por movimiento 
    
    //Sobrecarga de Operadores
    Complejo operator+(const Complejo& c2) const;           //Idem + - * /
    bool operator==(const Complejo& c2) const;              //Idem == != < > <= >=
    Complejo& operator++();                                 //prefix ++, ej ++a     Idem ++ --
    Complejo operator++(int);                               //postfix ++, ej a++    Idem ++ --
    operator bool() const;                                  //Operador de casteo, idem bool int float char double etc..
    
    //Prototipos de sobrecarga de operadores globales
    //Opcion 1: indicar con friend la declaracion para darle acceso privado a la clase Complejo y evitar getters y setters.
    friend std::ostream& operator<<(std::ostream& output, const Complejo& c);
    friend std::istream& operator>>(std::istream& input, Complejo& c);
};

//Prototipos de sobrecarga de operadores globales
//Opcion 2: no declaramos en clase Complejo y usamos getters y setters de Complejo para acceder a real e imaginario.
//cout es de la clase ostream y no podemos modificarla -> sobrecargamos el operador global
//cin es de la clase istream y no podemos modificarla -> sobrecargamos el operador global
//std::ostream& operator<<(std::ostream &output, const Complejo &c);
//std::istream& operator>>(std::istream &input, Complejo &c);

//Tanto para opcion 1 u opción 2 se define de esta manera.
std::ostream& operator<<(std::ostream &output, const Complejo &c) {/*..*/}
std::istream& operator>>(std::istream &input, Complejo &c) {/*..*/}