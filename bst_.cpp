//-----------BST-----------

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct node {
    string data;
    node* left;
    node* right;

    node(string d) {
        data  = d;
        left  = NULL;
        right = NULL;
    }
};

class dict {
    node* root;

public:
    dict() {
        root = NULL;
    }

    void insert(string data) {
        node* temp = new node(data);
        if (root == NULL) {
            root = temp;
            return;
        }
        node* curr = root;
        while (curr != NULL) {
            if (data == curr->data) {
                cout << "Duplicate";
                return;
            } else if (data > curr->data) {
                if (curr->right == NULL) {
                    curr->right = temp;
                    return;
                }
                curr = curr->right;
            } else {
                if (curr->left == NULL) {
                    curr->left = temp;
                    return;
                }
                curr = curr->left;
            }
        }
        cout << "Inserted";
    }

    void inorder() {
        stack<node*> s;
        node* curr = root;

        if (curr == NULL) {
            cout << "Empty";
            return;
        }
        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    void display() {
        if (root == NULL) {
            cout << "Dictionary empty!" << endl;
            return;
        }
        queue<node*> q;
        q.push(root);
        while (!q.empty()) {
            node* curr = q.front();
            q.pop();
            cout << curr->data << endl;
            if (curr->right)
                q.push(curr->right);
            if (curr->left)
                q.push(curr->left);
        }
    }

    void del_leaf(string key) {
        node* curr   = root;
        node* parent = NULL;

        while (curr != NULL && curr->data != key) {
            parent = curr;
            if (key < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Key not found!" << endl;
            return;
        }

        if (curr->left != NULL || curr->right != NULL) {
            cout << "Not a leaf node!" << endl;
            return;
        }

        if (parent == NULL)
            root = NULL;
        else if (parent->left == curr)
            parent->left = NULL;
        else
            parent->right = NULL;

        delete curr;
        cout << "Leaf node deleted!" << endl;
    }

    void del_one_child(string key) {
        node* curr   = root;
        node* parent = NULL;

        while (curr != NULL && curr->data != key) {
            parent = curr;
            if (key < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Key not found!" << endl;
            return;
        }

        if (curr->left != NULL && curr->right != NULL) {
            cout << "Node has two children!" << endl;
            return;
        }

        if (curr->left == NULL && curr->right == NULL) {
            cout << "Node is leaf! Use leaf delete." << endl;
            return;
        }

        node* child = (curr->left != NULL) ? curr->left : curr->right;

        if (parent == NULL)
            root = child;
        else if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;

        delete curr;
        cout << "Node with one child deleted!" << endl;
    }

    void del_two_child(string key) {
        node* curr   = root;
        node* parent = NULL;

        while (curr != NULL && curr->data != key) {
            parent = curr;
            if (key < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL) {
            cout << "Key not found!" << endl;
            return;
        }

        if (curr->left == NULL || curr->right == NULL) {
            cout << "Node does not have two children!" << endl;
            return;
        }

        node* succParent = curr;
        node* succ       = curr->right;

        while (succ->left != NULL) {
            succParent = succ;
            succ       = succ->left;
        }

        curr->data = succ->data;

        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        delete succ;
        cout << "Node with two children deleted!" << endl;
    }

    void mirror() {
        if (root == NULL) {
            cout << "Dictionary empty!" << endl;
            return;
        }

        stack<node*> s;
        s.push(root);

        while (!s.empty()) {
            node* curr = s.top();
            s.pop();

            swap(curr->left, curr->right);

            if (curr->left)
                s.push(curr->left);
            if (curr->right)
                s.push(curr->right);
        }

        cout << "Mirror created!" << endl;
    }
};

int main() {
    dict wo;
    int  choice;
    string data;
    int c;

    do {
        cout << "\n1.Insert\n2.Display\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter data: ";
            cin >> data;
            wo.insert(data);
            break;
        case 2:
            cout << "Display";
            wo.display();
            break;
        }
        cout << "Continue?";
        cin >> c;
    } while (c == 1);

    return 0;
}