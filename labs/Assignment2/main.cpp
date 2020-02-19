
#include "queue.h"

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
}

int main(int argc, char *argv[]) {
    testqueue();

    return 0;
}

