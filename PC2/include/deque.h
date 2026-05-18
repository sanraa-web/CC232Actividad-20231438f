#pragma once

#include <vector>
#include <algorithm>
#include <cassert>

namespace ods {

template<class T>
class array {
    std::vector<T> data_;
public:
    explicit array(int n = 0) : data_(n) {}

    int length() const {
        return data_.size();
    }

    T& operator[](int i) {
        assert(0 <= i && i < length());
        return data_[(std::size_t)i];
    }

    const T& operator[](int i) const {
        assert(0 <= i && i < length());
        return data_[(std::size_t)i];
    }
};

template<class T>
class Deque {
protected:
    struct Node {
        T value;
        int index;

        Node() : value(T()), index(-1) {}
        Node(T val, int idx) : value(val), index(idx) {}
    };

    array<Node> a;
    int j;
    int n;

    virtual void resize() {
        int cap = std::max(1, 2 * n);
        array<Node> b(cap);
        for (int k = 0; k < n; ++k) {
            b[k] = a[(j + k) % a.length()];
        }
        a = b;
        j = 0;
    }

public:
    Deque() : a(1), j(0), n(0) {}
    virtual ~Deque() = default;

    bool empty() const {
        return n == 0;
    }

    virtual void add(int i, T x, int index = -1) {
        assert(0 <= i && i <= n);
        if (n + 1 > a.length()) {
            resize();
        }
        assert(n + 1 <= a.length());
        if (i < n / 2) {
            j = (j == 0) ? a.length() - 1 : j - 1;
            for (int k = 0; k < i; ++k) {
                a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
            }
        } else {
            for (int k = n; k > i; --k) {
                a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
            }
        }
        a[(j + i) % a.length()] = Node(x, index);
        ++n;
    }

    T remove(int i) {
        assert(0 <= i && i < n);
        T x = a[(j + i) % a.length()].value;
        if (i < n / 2) {
            for (int k = i; k > 0; --k) {
                a[(j + k) % a.length()] = a[(j + k - 1) % a.length()];
            }
            j = (j + 1) % a.length();
        } else {
            for (int k = i; k < n - 1; ++k) {
                a[(j + k) % a.length()] = a[(j + k + 1) % a.length()];
            }
        }
        --n;
        if (a.length() >= 3 * std::max(1, n)) {
            resize();
        }
        return x;
    }

    T removeFront() {
        return remove(0);
    }

    T removeBack() {
        return remove(n - 1);
    }

    T front() const {
        assert(n > 0);
        return a[j].value;
    }

    T back() const {
        assert(n > 0);
        return a[(j + n - 1) % a.length()].value;
    }

    void addBack(T x, int index = -1) {
        add(n, x, index);
    }

};

}