#include <iostream>
using namespace std;

int heap[100];
int size = 0;

int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

void heapifyUp(int i) {
    while (i > 0 && heap[parent(i)] < heap[i]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void heapifyDown(int i) {
    int largest = i;
    int l = left(i);
    int r = right(i);

    if (l < size && heap[l] > heap[largest])
        largest = l;

    if (r < size && heap[r] > heap[largest])
        largest = r;

    if (largest != i) {
        swap(heap[largest], heap[i]);
        heapifyDown(largest);
    }
}

void insert(int val) {
    heap[size] = val;
    heapifyUp(size);
    size++;
}

void deletemax() {
    if (size == 0) return;

    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
}

void display() {
    for (int i = 0; i < size; i++)
        cout << heap[i] << " ";
}

int main() {
    int choice, a;
    int val;
    do {
        cout << "1.insert\n2.delete\n3.display";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "insert";
            cin >> val;
            insert(val);
            break;
        case 2:
            cout << "delete";
            deletemax();
            break;
        case 3:
            cout << "Display";
            display();
            break;
        }
        cout << "Continue?";
        cin >> a;
    } while (a == 1);
    return 0;
}