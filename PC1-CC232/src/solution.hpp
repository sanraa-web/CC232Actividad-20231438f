#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Stack {
public:
    void    push(const T& value);
    void    pop();
    T&      top();
    bool    empty() const;
    size_t  size()  const;

private:
    std::vector<T> data_;
};

int evalRPN(const std::vector<std::string>& tokens);

// Implementacion del stack

template <typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template <typename T>
void Stack<T>::pop() {
    if (data_.empty())
        throw std::underflow_error("Stack::pop() en stack vacio");
    data_.pop_back();
}

template <typename T>
T& Stack<T>::top() {
    if (data_.empty())
        throw std::underflow_error("Stack::top() en stack vacio");
    return data_.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return data_.empty();
}

template <typename T>
size_t Stack<T>::size() const {
    return data_.size();
}

#endif /* SOLUTION_HPP */