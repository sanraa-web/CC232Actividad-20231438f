#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include "solution.hpp"

// Version con std::stack (solucion ingenua/referencia)
int evalRPN_std(const std::vector<std::string>& tokens) {
    std::stack<int> st;

    for (const std::string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            if      (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else                   st.push(a / b);
        } else {
            st.push(std::stoi(token));
        }
    }

    return st.top();
}

// Utilidad de medicion
using Clock = std::chrono::high_resolution_clock;

double ms_between(Clock::time_point a, Clock::time_point b) {
    return std::chrono::duration<double, std::milli>(b - a).count();
}

// Main
int main() {
    // Input representativo: 13 tokens, todas las operaciones
    const std::vector<std::string> tokens = {
        "10","6","9","3","+","-11","*","/","*","17","+","5","+"
    };
    const int N = 1'000'000;

    std::cout << "Benchmark: Stack<int> propio vs std::stack<int>\n";
    std::cout << "Iteraciones: " << N << "\n";
    std::cout << "Input: [10,6,9,3,+,-11,*,/,*,17,+,5,+]  -> esperado: 22\n\n";

    // Warmup (evita ruido de cache fria)
    for (int i = 0; i < 1000; i++) evalRPN(tokens);
    for (int i = 0; i < 1000; i++) evalRPN_std(tokens);

    // Stack propio 
    auto t1 = Clock::now();
    for (int i = 0; i < N; i++) evalRPN(tokens);
    auto t2 = Clock::now();

    // std::stack 
    auto t3 = Clock::now();
    for (int i = 0; i < N; i++) evalRPN_std(tokens);
    auto t4 = Clock::now();

    double ms_propio = ms_between(t1, t2);
    double ms_std    = ms_between(t3, t4);

    std::cout << "Stack propio : " << ms_propio << " ms\n";
    std::cout << "std::stack   : " << ms_std    << " ms\n\n";

    double diff = ms_propio - ms_std;
    double pct  = (diff / ms_std) * 100.0;

    if (diff > 0)
        std::cout << "Stack propio es " << pct  << "% mas lento\n";
    else
        std::cout << "Stack propio es " << -pct << "% mas rapido\n";


    return 0;
}