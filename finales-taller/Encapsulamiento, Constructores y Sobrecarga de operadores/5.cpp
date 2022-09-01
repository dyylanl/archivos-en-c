/*
 * Declare una clase a elección que incluya los operatores +, >, >> y bool.
 */

#include <iostream>
class A {
public:
    A();
    A operator+(const A& a) const;
    bool operator>(const A& a) const;
    operator bool() const;
    friend std::istream& operator>>(stD::istream& is, A& a); //Hipotesis: suponemos que la necesitan para entrada cin
};