// Red-Black Tree

#include <iostream>
using namespace std;

struct Node {
    int    data;
    bool   color;
    Node*  left;
    Node*  right;
    Node*  parent;
};

Node* NIL;

void initNIL() {
    NIL         = new Node;
    NIL->color  = false;
    NIL->left   = NIL;
    NIL->right  = NIL;
    NIL->parent = NIL;
}

Node* createNode(int value) {
    Node* n  = new Node;
    n->data   = value;
    n->color  = true;
    n->left   = NIL;
    n->right  = NIL;
    n->parent = NIL;
    return n;
}

void rightRotate(Node* y) {
    Node* x  = y->left;
    Node* B  = x->right;

    x->right = y;
    y->left  = B;

    x->parent = y->parent;
    if (y->parent == NIL)
        ;
    else if (y == y->parent->left)
        y->parent->left  = x;
    else
        y->parent->right = x;

    y->parent = x;
    if (B != NIL)
        B->parent = y;
}

void leftRotate(Node* x) {
    Node* y  = x->right;
    Node* B  = y->left;

    y->left  = x;
    x->right = B;

    y->parent = x->parent;
    if (x->parent == NIL)
        ;
    else if (x == x->parent->left)
        x->parent->left  = y;
    else
        x->parent->right = y;

    x->parent = y;
    if (B != NIL)
        B->parent = x;
}

void fixInsert(Node*& root, Node* z) {

    while (z->parent != NIL && z->parent->color == true) {

        Node* parent      = z->parent;
        Node* grandparent = parent->parent;

        if (grandparent == NIL) break;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle->color == true) {
                parent->color      = false;
                uncle->color       = false;
                grandparent->color = true;
                z = grandparent;
            } else {
                if (z == parent->right) {
                    z = parent;
                    leftRotate(z);
                    parent      = z->parent;
                    grandparent = parent->parent;
                }
                parent->color      = false;
                grandparent->color = true;
                rightRotate(grandparent);
                if (grandparent == root)
                    root = parent;
                else if (parent->parent != NIL && grandparent == parent->parent->left)
                    parent->parent->left  = parent;
                else if (parent->parent != NIL)
                    parent->parent->right = parent;
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle->color == true) {
                parent->color      = false;
                uncle->color       = false;
                grandparent->color = true;
                z = grandparent;
            } else {
                if (z == parent->left) {
                    z = parent;
                    rightRotate(z);
                    parent      = z->parent;
                    grandparent = parent->parent;
                }
                parent->color      = false;
                grandparent->color = true;
                leftRotate(grandparent);
                if (grandparent == root)
                    root = parent;
                else if (parent->parent != NIL && grandparent == parent->parent->right)
                    parent->parent->right = parent;
                else if (parent->parent != NIL)
                    parent->parent->left  = parent;
            }
        }
    }

    root->color = false;
}

void insert(Node*& root, int key) {

    Node* z = createNode(key);

    Node* parent  = NIL;
    Node* current = root;

    while (current != NIL) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else {
            cout << "Duplicate " << key << " — not inserted.\n";
            delete z;
            return;
        }
    }

    z->parent = parent;

    if (parent == NIL)
        root = z;
    else if (key < parent->data)
        parent->left  = z;
    else
        parent->right = z;

    fixInsert(root, z);
}

void transplant(Node*& root, Node* u, Node* v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left  = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void fixDelete(Node*& root, Node* x) {
    while (x != root && x->color == false) {

        if (x == x->parent->left) {
            Node* sibling = x->parent->right;

            if (sibling->color == true) {
                sibling->color     = false;
                x->parent->color   = true;
                leftRotate(x->parent);
                if (x->parent->parent == NIL) root = sibling;
                sibling = x->parent->right;
            }
            if (sibling->left->color == false && sibling->right->color == false) {
                sibling->color = true;
                x = x->parent;
            } else {
                if (sibling->right->color == false) {
                    sibling->left->color = false;
                    sibling->color       = true;
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }
                sibling->color        = x->parent->color;
                x->parent->color      = false;
                sibling->right->color = false;
                leftRotate(x->parent);
                if (x->parent->parent == NIL) root = sibling;
                x = root;
            }
        } else {
            Node* sibling = x->parent->left;

            if (sibling->color == true) {
                sibling->color     = false;
                x->parent->color   = true;
                rightRotate(x->parent);
                if (x->parent->parent == NIL) root = sibling;
                sibling = x->parent->left;
            }
            if (sibling->right->color == false && sibling->left->color == false) {
                sibling->color = true;
                x = x->parent;
            } else {
                if (sibling->left->color == false) {
                    sibling->right->color = false;
                    sibling->color        = true;
                    leftRotate(sibling);
                    sibling = x->parent->left;
                }
                sibling->color       = x->parent->color;
                x->parent->color     = false;
                sibling->left->color = false;
                rightRotate(x->parent);
                if (x->parent->parent == NIL) root = sibling;
                x = root;
            }
        }
    }
    x->color = false;
}

Node* minValue(Node* node) {
    while (node->left != NIL)
        node = node->left;
    return node;
}

void deleteNode(Node*& root, int key) {

    Node* z = root;
    while (z != NIL) {
        if      (key == z->data) break;
        else if (key <  z->data) z = z->left;
        else                     z = z->right;
    }

    if (z == NIL) {
        cout << "Not found!\n";
        return;
    }

    Node* y              = z;
    bool yOriginalColor = y->color;
    Node* x;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);

    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);

    } else {
        y              = minValue(z->right);
        yOriginalColor = y->color;
        x              = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(root, y, y->right);
            y->right         = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left          = z->left;
        y->left->parent  = y;
        y->color         = z->color;
    }

    delete z;

    if (yOriginalColor == false)
        fixDelete(root, x);
}

bool search(Node* root, int key) {
    if (root == NIL) return false;
    if (key == root->data) return true;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

void inorder(Node* root) {
    if (root != NIL) {
        inorder(root->left);
        cout << root->data
             << (root->color == true ? "(R)" : "(B)") << " ";
        inorder(root->right);
    }
}

int main() {
    initNIL();
    Node* root = NIL;
    int choice, value;

    do {
        cout << "\n--- RBT MENU ---\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display (Inorder)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                insert(root, value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(root, value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Element Found\n";
                else
                    cout << "Element Not Found\n";
                break;

            case 4:
                cout << "Inorder: ";
                inorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 5);

    return 0;
}