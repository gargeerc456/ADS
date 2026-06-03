// Threaded Binary Search Tree (TBST)

#include <iostream>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    int data;
    int lth;
    int rth;

    Node(int d) {
        data = d;
        left = right = NULL;
        lth = rth = 1;
    }
};

Node* root = NULL;

Node* insert(Node* root, int key) {
    Node* temp   = new Node(key);
    Node* parent = NULL;

    if (root == NULL) {
        root = temp;
        return root;
    }

    Node* curr = root;

    while (curr != NULL) {
        if (key == curr->data) {
            cout << "Duplicate not allowed\n";
            return root;
        }

        parent = curr;

        if (key < curr->data) {
            if (curr->lth == 0)
                curr = curr->left;
            else
                break;
        } else {
            if (curr->rth == 0)
                curr = curr->right;
            else
                break;
        }
    }

    if (key < parent->data) {
        temp->left   = parent->left;
        temp->right  = parent;
        parent->lth  = 0;
        parent->left = temp;
    } else {
        temp->left    = parent;
        temp->right   = parent->right;
        parent->rth   = 0;
        parent->right = temp;
    }

    return root;
}

bool search(Node* root, int key) {
    while (root != NULL) {
        if (root->data == key) {
            cout << "Found: " << key << endl;
            return true;
        }
        else if (key < root->data) {
            if (root->lth == 0)
                root = root->left;
            else
                break;
        }
        else {
            if (root->rth == 0)
                root = root->right;
            else
                break;
        }
    }
    cout << "Not Found\n";
    return false;
}

Node* inorderSuccessor(Node* curr) {
    if (curr->rth == 1)
        return curr->right;

    curr = curr->right;
    while (curr->lth == 0)
        curr = curr->left;

    return curr;
}

void inorder(Node* root) {
    if (root == NULL) {
        cout << "Tree empty\n";
        return;
    }

    Node* curr = root;

    while (curr->lth == 0)
        curr = curr->left;

    cout << "Inorder: ";
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = inorderSuccessor(curr);
    }
    cout << endl;
}

void storeInorder(Node* root, int arr[], int &i) {
    if (root == NULL) return;

    Node* curr = root;

    while (curr->lth == 0)
        curr = curr->left;

    while (curr != NULL) {
        arr[i++] = curr->data;
        curr = inorderSuccessor(curr);
    }
}

void mirrorArray(Node* root) {
    int arr[100], n = 0;

    storeInorder(root, arr, n);

    cout << "Mirror (using array): ";
    for (int i = n - 1; i >= 0; i--)
        cout << arr[i] << " ";
    cout << endl;
}

Node* reverseSuccessor(Node* curr) {
    if (curr->lth == 1)
        return curr->left;

    curr = curr->left;
    while (curr->rth == 0)
        curr = curr->right;

    return curr;
}

void mirrorTBT(Node* root) {
    if (root == NULL) return;

    Node* curr = root;

    while (curr->rth == 0)
        curr = curr->right;

    cout << "Mirror (using threads): ";
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = reverseSuccessor(curr);
    }
    cout << endl;
}

Node* deleteNode(Node* root, int key) {
    Node* parent = NULL;
    Node* curr   = root;

    while (curr != NULL) {
        if (key == curr->data)
            break;

        parent = curr;

        if (key < curr->data) {
            if (curr->lth == 0)
                curr = curr->left;
            else
                return root;
        } else {
            if (curr->rth == 0)
                curr = curr->right;
            else
                return root;
        }
    }

    if (curr == NULL) {
        cout << "Node not found\n";
        return root;
    }

    if (curr->lth == 1 && curr->rth == 1) {
        if (parent == NULL) {
            delete curr;
            return NULL;
        }

        if (parent->left == curr) {
            parent->lth  = 1;
            parent->left = curr->left;
        } else {
            parent->rth   = 1;
            parent->right = curr->right;
        }

        delete curr;
        cout << "Leaf deleted\n";
    } else {
        cout << "Only leaf delete implemented\n";
    }

    return root;
}

int main() {
    int choice, val;

    do {
        cout << "\n1.Insert\n2.Delete\n3.Search\n4.Display\n5.Mirror(Array)\n6.Mirror(Thread)\n7.Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            root = insert(root, val);
            break;

        case 2:
            cout << "Enter value to delete: ";
            cin >> val;
            root = deleteNode(root, val);
            break;

        case 3:
            cout << "Enter value to search: ";
            cin >> val;
            search(root, val);
            break;

        case 4:
            inorder(root);
            break;

        case 5:
            mirrorArray(root);
            break;

        case 6:
            mirrorTBT(root);
            break;

        case 7:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 7);

    return 0;
}