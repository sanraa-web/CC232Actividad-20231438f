#include <cassert>
#include <vector>
#include <string>
#include <stdexcept>
#include "../src/solution.hpp"
using namespace std;

int main() {

    // Casos básicos
    assert(evalRPN(vector<string>{"2","1","+","3","*"}) == 9);
    assert(evalRPN(vector<string>{"4","13","5","/","+"}) == 6);

    // Todas las operaciones
    assert(evalRPN(vector<string>{"5","3","-"}) == 2);
    assert(evalRPN(vector<string>{"2","3","*"}) == 6);
    assert(evalRPN(vector<string>{"8","2","/"}) == 4);

    // Números negativos
    assert(evalRPN(vector<string>{"-3"}) == -3);
    assert(evalRPN(vector<string>{"-7","2","/"}) == -3);

    // Caso complejo
    assert(evalRPN(vector<string>{
        "10","6","9","3","+","-11","*","/","*","17","+","5","+"}) == 22);

    // Caso propio (diseñado)
    assert(evalRPN(vector<string>{"2","3","4","*","+"}) == 14);

    // División por cero
    try {
        evalRPN(vector<string>{"4","0","/"});
        assert(false); // debería fallar
    } catch (const invalid_argument&) {
        assert(true);
    }

    // Expresión RPN inválida
    try {
        evalRPN(vector<string>{"+"});
        assert(false); // debería fallar
    } catch (const invalid_argument&) {
        assert(true);
    }

    return 0;
}