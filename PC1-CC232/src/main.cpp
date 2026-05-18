#include <iostream>
#include <vector>
#include <string>
#include "solution.hpp"

int main() {
    std::vector<std::string> tokens = {"2","1","+","3","*"}; // resultado esperado: 9
    std::cout << evalRPN(tokens) << std::endl;
    return 0;
}