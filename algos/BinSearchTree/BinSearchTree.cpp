
#include <stddef.h>
#include <exception>
#include <cassert>

#define TEST

#ifdef TEST
#include <iostream>
#endif

struct NotFoundException : std::exception {
};

struct Node {
    Node* left;
    Node* right;
    int key, val;

    Node(int key, int val) : left(NULL), right(NULL), key(key), val(val) {}
    ~Node() {
        delete left;
        left = NULL;
        delete right;
        right = NULL;
    }
};

class BinSearchTree {
    Node* root;

    static Node* findMin(Node* node) {
        if (!node) return NULL;

        while (node->left) {
            node = node->left;
        }

        return node;
    }

public:

    struct iterator {
        iterator(Node** root) : root(root), curr(NULL) {}

        bool hasNext() {
            return successor() != NULL;
        }

        int next() {
            curr = successor();
            return curr->val;
        }

    private:
        Node* successor() const {
            if (!curr) {
                return findMin(*root);
            }

            if (curr->right) {
                return findMin(curr->right);
            }

            const int searchKey = curr->key;
            Node* prev = NULL;
            Node* ptr = *root;
            while (ptr != curr) {
                if (searchKey < ptr->key) {
                    prev = ptr;
                    ptr = ptr->left;
                } else if (searchKey > ptr->key) {
                    ptr = ptr->right;
                }
            }

            assert(ptr == curr);

            return prev;
        }

        Node** root;
        Node* curr;
    };

    BinSearchTree() : root(NULL) {}

    int get(const int key) const {
        Node* curr = root;
        while (curr) {
            if (curr->key == key) {
                return curr->val;
            } else if (key < curr->key) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        throw NotFoundException();
    }

    void put(const int key, const int value) {
        if (!root) {
            root = new Node(key, value);
            return;
        }

        Node* current = root;
        while (current) {
            if (key < current->key) {
                if (!current->left) {
                    current->left = new Node(key, value);
                    return;
                } else {
                    current = current->left;
                }
            } else if (key > current->key) {
                if (!current->right) {
                    current->right = new Node(key, value);
                    return;
                } else {
                    current = current->right;
                }
            } else { // key already exists
                current->val = value;
                return;
            }
        }
    }

    iterator begin() {
        return iterator(&root);
    }

    ~BinSearchTree() {
        delete root;
        root = NULL;
    }
};

#ifdef TEST
void assertEquals(int expected, int value) {
    if (expected != value) {
        std::cout << "Expected: " << expected << " - actual: " << value << std::endl;
    }
}

void assertThrows(std::function<void()> expr) {
    try {
        expr();
    } catch (std::exception e) {
        return;
    }
    std::cout << "Expected exception" << std::endl;
}

int main() {
    using namespace std;
    BinSearchTree tree;

    tree.put(1, 1);
    tree.put(2, 2);
    tree.put(0, 0);
    tree.put(-5, -5);

    assertEquals(1, tree.get(1));
    assertEquals(2, tree.get(2));
    assertEquals(0, tree.get(0));
    assertThrows([&tree] { tree.get(100); });

    BinSearchTree::iterator iter = tree.begin();
    while (iter.hasNext()) {
        std::cout << iter.next() << std::endl;
    }
}
#endif