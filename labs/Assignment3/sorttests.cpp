
#include <iostream>
#include <vector>
#include <algorithm>

#include "timer.h"
#include "timetable.h"

// Print a vector of integers:

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vect) {
    for (size_t i = 0; i != vect.size(); ++i)
        out << i << " : " << vect[i] << "\n";

    return out;
}


// Create a vector of size k filled with random ints:

std::vector<int> randomvector(size_t k) {
    std::vector<int> res;
    for (size_t i = 0; i != k; ++i)
        res.push_back(rand());
    return res;
}


void bubble_sort(std::vector<int> &vect) {
    if (vect.size() < 2) return;
    // Every shorter vector is sorted.

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 0; i + 1 != vect.size(); ++i) {
            if (vect[i] > vect[i + 1]) {
                std::swap(vect[i], vect[i + 1]);
                sorted = false;
            }
        }
    }
}

void restore_heap(std::vector<int> &vect, size_t s) {
    size_t p = 0;
    while (2 * p + 1 < s) {
        if (2 * p + 2 == s) {
            if (vect[p] < vect[2 * p + 1])
                std::swap(vect[p], vect[2 * p + 1]);
            return;
        } else {
            if (vect[p] < vect[2 * p + 1] || vect[p] < vect[2 * p + 2]) {
                if (vect[2 * p + 1] < vect[2 * p + 2]) {
                    std::swap(vect[p], vect[2 * p + 2]);
                    p = 2 * p + 2;
                } else {
                    std::swap(vect[p], vect[2 * p + 1]);
                    p = 2 * p + 1;
                }
            } else
                return;
        }
    }
}


void heap_sort(std::vector<int> &vect) {
    if (vect.size() < 2) return;
    // Every shorter vector is sorted.

    // In the first pass, we establish the heap condition:

    for (size_t i = 1; i != vect.size(); ++i) {
        for (size_t p = i; p != 0; p = (p - 1) / 2) {
            if (vect[p] > vect[(p - 1) / 2])
                std::swap(vect[p], vect[(p - 1) / 2]);
        }
    }

    size_t i = vect.size();
    while (i) {
        --i;
        std::swap(vect[0], vect[i]);

        // And we restore heap condition between 0 and i:

        restore_heap(vect, i);
    }

}


void quick_sort(std::vector<int> &vect) {
    std::sort(vect.begin(), vect.end());
}


std::list<int>::iterator
findmin(std::list<int>::iterator p1,
        std::list<int>::iterator p2) {
    if (p1 == p2)
        return p2;

    auto min = p1++;
    while (p1 != p2) {
        if (*p1 < *min)
            min = p1;
        ++p1;
    }

    return min;
}


void insertion_sort(std::list<int> &lst) {
    for (auto p = lst.begin(); p != lst.end(); ++p) {
        auto m = findmin(p, lst.end());
        std::swap(*p, *m);
    }
}


int main(int argc, char *argv[]) {

    timetable algQs("quick_sort");
    timetable algBs("bubble_sort");
    timetable algIs("insertion_sort");
    timetable algHs("heap_sort");

    // Doubling s is better than adding a fixed number to s:
    for (size_t s = 1000; s < 100000; s = 2 * s) {
        std::vector<int> test = randomvector(s);
        // A random vector of size s.
        auto test2 = test;
        // Be very careful not to sort the same vector twice.
        // It is useless.
        timer tt;
        for (int i = 0; i < 1000; i++) {
            bubble_sort(test);
        }

        algQs.insert(s, tt.time());

        tt.clear();
        quick_sort(test2);
        algHs.insert(s, tt.time());
    }

    std::cout << algQs << "\n";
    std::cout << algHs << "\n";
    // Answer question 2 in the comments:
    //
    // Is there a difference between compilation with optimization
    // on and compilation with optimization off?
    // .....


    // Answer question 3 in the comments:
    //
    // Establish which sorting algorithms have O(n^2) performance, and which
    // ones have O(n. log(n)) performance.
    //

    // Answer question 4 in the comments:
    //
    // Among those with O(n^2), which one is faster?
    // ....


    // Answer question 5 in the comments:
    //
    // Among those with O(n. log(n)), which one is faster?
    // ....

    std::cout << "have a nice day\n";
}
 
