#include <iostream>

float dividir(const float dividendo, const float divisor) {
    if (divisor == 0)
        throw std::runtime_error("ERROR: No se puede dividir por 0.");
    else
        return dividendo/divisor;
}

int main () {
    try {
        std::cout << dividir(3, 4) << std::endl;
        std::cout << dividir(3, 0) << std::endl; //Lanza excepción
    }
    catch (const std::runtime_error &e) { //Capturo excepción
        std::cerr << e.what() << std::endl;
    } 
    return 0;
}