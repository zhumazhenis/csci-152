
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

queue::queue() : current_size(0), first(nullptr), last(nullptr) {}

queue::queue(const queue &q) : current_size(0), first(nullptr), last(nullptr) {
    for (qnode *current = q.first; current != nullptr; current = current->next) {
        push(current->val);
    }
}

const queue &queue::operator=(const queue &q) {
    clear();
    for (qnode *current = q.first; current != nullptr; current = current->next) {
        push(current->val);
    }
    return *this;
}

queue::~queue() {
    clear();
}

queue::queue(std::initializer_list<double> init) : current_size(0), first(nullptr), last(nullptr) {
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
    for (qnode *current = first; current != nullptr; current = current->next) {
        os << current->val << ' ';
    }
}

void testqueue() {
    queue q1 = {1, 2, 3, 4, 5};
    queue q2 = q1; // Copy constructor.
    for (unsigned int j = 0; j < 30; ++j) {
        q1.push(j * j);
        q1.checkinvariant();
        if (j % 5 == 0) {
            while (q1.size()) {
                std::cout << q1.peek() << "\n";
                q1.pop();
                q1.checkinvariant();
            }
        }
    }
    q1 = q2; // Assignment.
    q1 = q1; // Self assignment.
    q1.checkinvariant();
    queue q3 = {1, 2, 3, 4, 5, 6};
    std::cout << q3 << "\n";

    // Try to show in your solution that you enjoy programming!
    // If you don’t, a life full of unhappiness is ahead of you.

    // test constructors
    queue myQueue;
    queue myQueueClone = myQueue;
    queue myQueue2 = {1, 3, 2, 5, 7, 10};
    myQueue.checkinvariant();
    myQueueClone.checkinvariant();
    myQueue2.checkinvariant();

    // test push
    myQueue.push(1);
    myQueueClone.push(2);
    myQueue2.push(3);
    myQueue.checkinvariant();
    myQueueClone.checkinvariant();
    myQueue2.checkinvariant();

    // test pop
    myQueue.pop();
    myQueueClone.pop();
    myQueue2.pop();
    myQueue.checkinvariant();
    myQueueClone.checkinvariant();
    myQueue2.checkinvariant();

    // test clear
    myQueue.clear();
    myQueueClone.clear();
    myQueue2.clear();
    myQueue.checkinvariant();
    myQueueClone.checkinvariant();
    myQueue2.checkinvariant();
}





