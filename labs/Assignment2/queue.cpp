
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant

bool queue::checkinvariant() const {
    if (current_size == 0) {
        if (first) {
            std::cout << "INVARIANT: ";
            std::cout << "current_size == 0, but first != nullptr\n";
            return false;
        }

        if (last) {
            std::cout << "INVARIANT: ";
            std::cout << "current_size == 0, but last != nullptr\n";
            return false;
        }

        return true;
    }

    size_t s = 0;
    const qnode *l = nullptr; // This will remember the last node.

    for (const qnode *p = first; p; p = p->next) {
        if (s == current_size) {
            std::cout << "INVARIANT: ";
            std::cout << "current_size is less than real size: ";
            std::cout << current_size << "\n\n";
            // I don't want to count further because list may be corrupt.
            return false;
        }
        ++s;
        l = p;
    }

    if (s != current_size) {
        std::cout << "INVARIANT ";
        std::cout << "current_size is not equal to real size\n";
        std::cout << "current_size = " << current_size << "\n";
        std::cout << "real size    = " << s << "\n";

        return false;
    }

    if (l != last) {
        std::cout << "INVARIANT: last is not correct, ";
        std::cout << "it is " << last << " but must be " << l << "\n";
        return false;
    }

    return true;
}

queue::queue() : current_size(0) {}

queue::queue(const queue &q) : current_size(0) {
    qnode *current = q.first;
    while (current != nullptr) {
        push(current->val);
        current = current->next;
    }
}

const queue &queue::operator=(const queue &q) {
    clear();
    qnode *current = q.first;
    while (current != nullptr) {
        push(current->val);
        current = current->next;
    }
    return *this;
}

queue::~queue() {
    clear();
}

queue::queue(std::initializer_list<double> init) : current_size(0) {
    for (auto entry : init) {
        push(entry);
    }
}

void queue::push(double d) {
    if (empty()) {
        first = last = new qnode(d);
    } else {
        last->next = new qnode(d);
        last = last->next;
    }
    current_size++;
}

void queue::pop() {
    if (empty()) {
        throw std::runtime_error("pop: queue is empty!");
    }
    qnode *temp = first;
    first = first->next;
    delete temp;
    current_size--;
    if (current_size == 0) {
        first = last = nullptr;
    }
}

void queue::clear() {
    while (!empty()) {
        pop();
    }
}

double queue::peek() const {
    if (empty()) {
        throw std::runtime_error("peek: queue is empty!");
    }
    return first->val;
}

void queue::print(std::ostream &os) const {
    qnode *current = first;
    while (current != nullptr) {
        os << current->val << ' ';
        current = current->next;
    }
}





