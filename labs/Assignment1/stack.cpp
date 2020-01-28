
#include "stack.h"

// Use this method for all your reallocations:

void stack::ensure_capacity(size_t c) {
    if (current_capacity < c) {
        // New capacity will be the greater of c and
        // 2 * current_capacity.

        if (c < 2 * current_capacity)
            c = 2 * current_capacity;

        double *newdata = new double[c];
        for (size_t i = 0; i < current_size; ++i)
            newdata[i] = data[i];

        current_capacity = c;
        delete[] data;
        data = newdata;
    }
}

stack::stack() : current_capacity(1), current_size(0), data(new double[1]) {}

stack::stack(const stack &s) : current_size(s.current_size), current_capacity(s.current_capacity) {
    data = new double[current_capacity];
    for (size_t i = 0; i < current_size; i++) {
        data[i] = s.data[i];
    }
}

stack::~stack() {
    delete[] data;
}

const stack &stack::operator=(const stack &s) {
    ensure_capacity(s.current_size);
    current_size = s.current_size;
    for (size_t i = 0; i < current_size; i++) {
        data[i] = s.data[i];
    }
    return *this;
}

stack::stack(std::initializer_list<double> init) : current_capacity(init.size()), current_size(init.size()) {
    data = new double[current_capacity];
    int i = 0;
    for (auto &entry : init) {
        data[i] = entry;
        i++;
    }
}

void stack::push(double d) {
    // increase capacity by 2 times if true
    ensure_capacity(current_size + 1);
    data[current_size] = d;
    current_size++;
}

void stack::pop() {
    if (current_size == 0) {
        throw std::runtime_error("pop: stack is empty!");
    }
    current_size--;
}

void stack::clear() {
    current_capacity = 1;
    current_size = 0;
    delete[] data;
    data = new double[1];
}

void stack::reset(size_t s) {
    current_size = s;
}

double stack::peek() const {
    if (empty()) {
        throw std::runtime_error("pop: stack is empty!");
    }
    return data[current_size - 1];
}

size_t stack::size() const {
    return current_size;
}

bool stack::empty() const {
    return current_size == 0;
}

std::ostream &operator<<(std::ostream &os, const stack &s) {
    for (size_t i = 0; i < s.size(); i++) {
        os << s.data[i] << ' ';
    }
    return os;
}
