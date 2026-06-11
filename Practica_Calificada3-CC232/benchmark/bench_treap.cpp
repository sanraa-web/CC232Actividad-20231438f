#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "../include/treap.h"

using Clock = std::chrono::high_resolution_clock;
using us   = std::chrono::microseconds;

void run(int N) {
    ods::Treap<int> treap;
    std::mt19937 rng(44);

    std::vector<int> valores;
    valores.reserve(N);
    for (int i = 1; i <= N; i++) 
        valores.push_back(i);
    std::shuffle(valores.begin(), valores.end(), rng);
    
    auto t0 = Clock::now();
    for (int x : valores)
        treap.add(x);
    auto t1 = Clock::now();
    long long insert_tiempo = std::chrono::duration_cast<us>(t1-t0).count();

    auto t2 = Clock::now();
    for(int i = 0; i < N; i++){
        int k = 1 + (rng() % treap.size());
        const int val = treap.kth(k);
        treap.remove(val);
    }

    auto t3 = Clock::now();
    long long kth_remove_tiempo = std::chrono::duration_cast<us>(t3 - t2).count();

    int log2n = static_cast<int>(std::log2(N));

    std::cout << "N = " << N
                << " log2(N) = " << log2n
                << '\n' << " insert (t) " << insert_tiempo << " us, "
                << static_cast<double>(insert_tiempo) / N << " us/op, "
                << " (us/op)/log2N = "
                << (static_cast<double>(insert_tiempo) / N) / log2n
                << '\n' <<" kth+remove (t) " << kth_remove_tiempo << " us, "
                << static_cast<double>(kth_remove_tiempo) / N << " us/op, "
                << " (us/op)/log2N = "
                << (static_cast<double>(kth_remove_tiempo) / N) / log2n
                << '\n';

}   

int main() {
    std::cout << "Bench treap\n";
    run(1000);
    run(10000);
    run(100000);
    return 0;
}