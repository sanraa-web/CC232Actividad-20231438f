#include <iostream>
#include "../include/treap.h"
 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 
    int Q;
    std::cin >> Q;
 
    ods::Treap<int> treap;
 
    while (Q--) {
        int T, X;
        std::cin >> T >> X;
 
        if (T == 1) { // Operacion 1
            treap.add(X);
        } else { // Operacion 2
            const int val = treap.kth(static_cast<std::size_t>(X));
            std::cout << val << "\n";
            treap.remove(val);
        }
    }
 
    return 0;
}