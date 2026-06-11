#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "../include/treap.h"

using Clock = std::chrono::high_resolution_clock;
using ms   = std::chrono::microseconds;

void run(int N) {
    ods::Treap<int> treap;
    std::mt19937 rng(44);

    std::vector<int> valores;
    valores.reserve(N);
    for (int i = 1; i <= N; i++) valores.push_back(i);
    std::shuffle(valores.begin(), valores.end(), rng);

    
}

int main() {
    std::cout << "Bench treap\n";
    run(1000);
    run(10000);
    run(100000);
    return 0;
}