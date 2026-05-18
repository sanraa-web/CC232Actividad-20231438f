#include "solution.hpp"
#include <vector>
#include <string>
#include <stdexcept>

int evalRPN(const std::vector<std::string>& tokens) {
    Stack<int> st;

    for (const std::string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (st.size() < 2)
                throw std::invalid_argument("Expresion RPN invalida");

            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            if      (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else {
                if (b == 0)
                    throw std::invalid_argument("Division por cero");
                st.push(a / b);
            }
        } else {
            int num = std::stoi(token);
            if (num < -200 || num > 200)
                throw std::out_of_range("Numero fuera del rango [-200, 200]");
            st.push(num);
        }
    }

    return st.top();
}