#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/treap.h"

void test_minimo() {
    ods::Treap<int> t;
    t.add(42);

    assert(t.size() == 1);
    assert(t.kth(1) == 42);
    t.remove(42);
    assert(t.size() == 0);
    std::cout << "test_minimo\n";
}

void test_vacio_frontera() {
    ods::Treap<int> t;

    assert(t.size() == 0);
    assert(t.empty());

    assert(t.size() < 1);

    t.add(7);
    assert(t.size() == 1);
    t.remove(7);
    assert(t.empty());
    std::cout << "test_vacio_frontera\n";
}

void test_duplicados() {
    ods::Treap<int> t;
    t.add(5);

    bool segundo  = t.add(5);
    bool tercero  = t.add(5);

    assert(segundo == false);
    assert(tercero == false);
    assert(t.size() == 1);
    assert(t.kth(1) == 5);
    std::cout << "test_duplicados\n";
}

void test_extremo_manual() {
    ods::Treap<int> t;
    for (int x : {4, 1, 5, 2, 3}) t.add(x);

    assert(t.size() == 5);
    assert(t.kth(1) == 1);
    assert(t.kth(2) == 2);
    assert(t.kth(3) == 3);
    assert(t.kth(4) == 4);
    assert(t.kth(5) == 5);
    std::cout << "test_extremo_manual\n";
}

void test_vs_ingenuo() {
    ods::Treap<int> t;
    std::vector<int> ingenuo;

    for (int x : {8, 3, 6, 1, 9, 4}) {
        t.add(x);
        ingenuo.push_back(x);
    }

    for (int i = 0; i < 3; i++) {
        std::sort(ingenuo.begin(), ingenuo.end());

        int esperado = ingenuo.front();
        ingenuo.erase(ingenuo.begin());

        int real = t.kth(1);
        t.remove(real);

        assert(real == esperado);
    }
    std::cout << "test_vs_ingenuo\n";
}

void check_sizes(ods::Treap<int>::Node* u) {
    if (!u) return;
    check_sizes(u->left);
    check_sizes(u->right);

    std::size_t left  = u->left  ? u->left->subtreeSize  : 0;
    std::size_t right = u->right ? u->right->subtreeSize : 0;
    assert(u->subtreeSize == 1 + left + right);
}

void test_invariante_subtreesize() {
    ods::Treap<int> t;
    for (int x : {5, 2, 8, 1, 4, 7, 9}) t.add(x);
    check_sizes(t.root());

    t.remove(5);
    check_sizes(t.root());

    t.remove(1);
    t.remove(9);
    check_sizes(t.root());
    std::cout << "test_invariante_subtreesize\n";
}

int main() {
    test_minimo();
    test_vacio_frontera();
    test_duplicados();
    test_extremo_manual();
    test_vs_ingenuo();
    test_invariante_subtreesize();

    std::cout << "Todos los tests pasaron\n";
    return 0;
}