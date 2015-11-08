#include <vector>
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
        delete right;
    }
};

class BinSearchTree {
    Node* root;

    static Node* findMin(Node* node, Node** parent = 0) {
        if (!node) return NULL;

        while (node->left) {
            if (parent) *parent = node;
            node = node->left;
        }

        return node;
    }

    static Node* findKey(Node* root, int key, Node** parent = 0) {
        if (parent) *parent = NULL;

        Node* curr = root;
        while (curr) {
            if (curr->key == key) {
                return curr;
            } else if (key < curr->key) {
                if (parent) *parent = curr;
                curr = curr->left;
            } else {
                if (parent) *parent = curr;
                curr = curr->right;
            }
        }

        return NULL;
    }

    Node** getLeadingPtr(Node* parent, Node* child) {
        if (parent == NULL) {
            return &root;
        }

        if (parent->left == child) {
            return &(parent->left);
        } else {
            return &(parent->right);
        }
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
        Node* node = findKey(root, key);

        if (!node)
            throw NotFoundException();

        return node->key;
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

    void erase(int key) {
        Node* parent;
        Node* node = findKey(root, key, &parent);
        if (!node) {
            return;
        }

        Node** leadingPtr = getLeadingPtr(parent, node);

        // is leaf?
        if (!node->left && !node->right) {
            delete node;
            *leadingPtr = NULL;
            return;
        }

        // has single child
        if (node->left && !node->right) {
            *leadingPtr = node->left;
            delete node;
            return;
        }

        if (node->right && !node->left) {
            *leadingPtr = node->right;
            delete node;
            return;
        }

        // has both children
        // replace with the inorder successor
        Node* successorParent = node;
        Node* inorderSuccessor = findMin(node->right, &successorParent);
        // inorder successor might still have a right ptr
        *getLeadingPtr(successorParent, inorderSuccessor) = inorderSuccessor->right;
        
        *leadingPtr = inorderSuccessor;
        inorderSuccessor->left = node->left;
        inorderSuccessor->right = node->right;

        node->left = NULL;
        node->right = NULL;
        delete node;
    }

    std::vector<int> keys() {
        std::vector<int> result;
        BinSearchTree::iterator iter = begin();
        while (iter.hasNext()) {
            result.push_back(iter.next());
        }
        return result;
    }

    iterator begin() {
        return iterator(&root);
    }

    ~BinSearchTree() {
        delete root;
    }
};

#ifdef TEST
void assertEquals(int expected, int value) {
    if (expected != value) {
        std::cout << "Expected: " << expected << " - actual: " << value << std::endl;
    }
}

void assertEquals(const std::vector<int>& expected, const std::vector<int>& value) {
    if (expected != value) {
        std::cout << "Expected: ";
        for (int num: expected) std::cout << num << " ";
        std::cout << std::endl;

        std::cout << "Actual:   ";
        for (int num: value) std::cout << num << " ";
        std::cout << std::endl;
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
    tree.put(3, 3);

    assertEquals(1, tree.get(1));
    assertEquals(2, tree.get(2));
    assertEquals(0, tree.get(0));
    assertThrows([&tree] { tree.get(100); });

    assertEquals(vector<int>({-5, 0, 1, 2, 3}), tree.keys());

    tree.erase(-5);
    assertEquals(vector<int>({0, 1, 2, 3}), tree.keys());
    tree.erase(1);
    assertEquals(vector<int>({0, 2, 3}), tree.keys());
}
#endif