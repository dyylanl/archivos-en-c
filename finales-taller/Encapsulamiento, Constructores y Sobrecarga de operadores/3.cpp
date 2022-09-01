/* Declare la clase Email para encapsular una cadena correspondiente a una dirección de email.
 * Incluya al menos: Constructor default y Constructor de Copia; Operador <<, ==, =, int y >>.
 * Implemente el operador >>. 
 */

#include <iostream>
class Email {
private:
    std::string email;
public:
    Email(const std::string = "");
    Email(const Email& e);
    Email& operator=(const Email& e);
    bool operator==(const Email& e) const;
    operator int() const;
    friend std::ostream& operator<<(std::ostream& os, const Email& e);
    friend std::istream& operator>>(std::istream& is, Email& e);
};
 
//Suponemos que es para operaciones de entrada salida
std::istream& operator>>(std::istream& is, Email& e) {
    is >> e.email;
    return is;
}