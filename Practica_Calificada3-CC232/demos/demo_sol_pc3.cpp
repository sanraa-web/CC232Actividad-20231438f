#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/treap.h"

std::vector<int> runCase(const std::string& input) {
    std::istringstream in(input);
    std::vector<int> output;
    int Q; in >> Q;
    ods::Treap<int> treap;
    while (Q--) {
        int type, x; in >> type >> x;
        if (type == 1) {
            treap.add(x);
        } else {
            int val = treap.kth(static_cast<std::size_t>(x));
            output.push_back(val);
            treap.remove(val);
        }
        treap.inorder();
    }
    return output;
}
 
int main() {
    const std::string input =
        "12\n"
        "1 8932\n"
        "1 183450\n"
        "1 34323\n"
        "1 81486\n"
        "1 127874\n"
        "1 114850\n"
        "1 55277\n"
        "1 112706\n"
        "2 3\n"
        "1 39456\n"
        "1 52403\n"
        "2 4\n";
 
    const std::vector<int> expected = {55277, 52403};
    const std::vector<int> got = runCase(input);
 
    std::cout << "Ejm2 del Atcoder\n";
    std::cout << "Obtenido:" << '\n';
    for (int v : got)      std::cout << v << '\n';
    std::cout << "Esperado:" << '\n';
    for (int v : expected) std::cout << v << '\n';
 
    assert(got == expected);
    return 0;
}
