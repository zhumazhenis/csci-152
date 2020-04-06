
#include "set.h"


void print(std::ostream &out, const treenode *n, size_t indent) {

    for (size_t i = 0; i != indent; ++i)
        out << "|  ";
    if (n) {
        out << (n->val) << "\n";
        print(out, n->left, indent + 1);
        print(out, n->right, indent + 1);
    } else
        out << "#\n";
}


// both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween(const treenode *n,
                  const int *lowerbound, const int *upperbound) {
    while (n) {
        if (lowerbound && *lowerbound >= n->val) {
            std::cout << "value " << (n->val);
            std::cout << " is not above lower bound " << *lowerbound << "\n";
            std::abort();
        }

        if (upperbound && n->val >= *upperbound) {
            std::cout << "value " << (n->val);
            std::cout << "is not below upperbound " << *upperbound << "\n";
            std::abort();
        }

        checkbetween(n->left, lowerbound, &(n->val));
        lowerbound = &(n->val);
        n = n->right;
    }
}


void deallocate(treenode *n) {
    while (n) {
        deallocate(n->left);
        treenode *bye = n;
        n = n->right;
        delete bye;
    }
}


void writecopy(treenode **to, treenode *from) {
    while (from) {
        *to = new treenode{from->val};

        writecopy(&(*to)->left, from->left);
        to = &(*to)->right;
        from = from->right;
    }
}


void set::checksorted() const {
    ::checkbetween(tr, nullptr, nullptr);
}


std::ostream &set::print(size_t indent, std::ostream &out) const {
    ::print(out, tr, indent);
    return out;
}

// TODO: Task 1
size_t log_base2(size_t s) {
    if (s == 0) {
        return 0;
    }
    size_t count = 0;
    for (size_t curr = 1; curr <= s; curr *= 2, count++);
    return count - 1;
}


// TODO: Task 2
const treenode *find(const treenode *n, int i) {
    if (n == nullptr) {
        return nullptr;
    }
    if (i == n->val) {
        return n;
    }
    if (i < n->val) {
        return find(n->left, i);
    }
    return find(n->right, i);
}

// TODO: Task 2
treenode **find(treenode **n, int i) {
    if (*n == nullptr || (*n)->val == i) {
        return n;
    }
    if (i < (*n)->val) {
        return find(&(*n)->left, i);
    }
    return find(&(*n)->right, i);
}

// TODO: Task 3
bool set::insert(int i) {
    treenode **node = find(&tr, i);
    if (*node == nullptr) {
        *node = new treenode(i);
        return true;
    }
    return false;
}

// TODO: Task 4
bool set::contains(int i) const {
    return find(tr, i) != nullptr;
}


// TODO: Task 5
treenode *removerightmost(treenode **from) {
    if (*from == nullptr) {
        return nullptr;
    }
    treenode **curr = from;
    while ((*curr)->right != nullptr) {
        curr = &(*curr)->right;
    }
    treenode *temp = *curr;
    *curr = (*curr)->left;
    return temp;
}

bool set::remove(int i) {
    treenode **node = find(&tr, i);
    if (*node != nullptr) {
        treenode *rightmost = removerightmost(&(*node)->left);
        if (rightmost == nullptr) {
            treenode *temp = *node;
            *node = (*node)->right;
            delete temp;
        } else {
            (*node)->val = rightmost->val;
            delete rightmost;
        }
        return true;
    }
    return false;
}

// TODO: Task 6
size_t size(const treenode *n) {
    if (n == nullptr) {
        return 0;
    }
    return size(n->left) + size(n->right) + 1;
}

void clear(treenode *n) {
    if (n == nullptr) {
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}

void set::clear() {
    ::clear(tr);
    tr = nullptr;
}


// TODO: Task 7
bool set::isempty() {
    return tr == nullptr;
}

// TODO: Task 8
size_t height(const treenode *n) {
    if (n == nullptr) {
        return 0;
    }
    return std::max(height(n->left), height(n->right)) + 1;
}

// TODO: Task 9

