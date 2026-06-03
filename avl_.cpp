// AVL Tree

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* n) {
    if (n == NULL)
    return 0;
    return n->height;
}

int getBalance(Node* n) {
    if (n == NULL)
    return 0;
    return getHeight(n->left) - getHeight(n->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* createNode(int value) {
    Node* n = new Node;
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

Node* rightRotate(Node* y) {
    Node* x  = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left  = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y  = x->right;
    Node* T2 = y->left;

    y->left  = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValue(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (key == root->data) return true;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    do {
        cout << "\n--- AVL MENU ---\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                root = insert(root, value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
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