#include <iostream>

using namespace std;

class circularQueue {
    int *queue;
    int front, rear, length;

public:
    circularQueue(int);
    void enqueue(int);
    void dequeue();
    bool isFull();
    bool isEmpty();
    void display();
};

int main() {
    int choice;
    int var;
    circularQueue q = circularQueue(4);
    while (true)
    {
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << ">>> ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            cout << "Enter a integer: ";
            cin >> var;
            q.enqueue(var);
            break;
        case 2:
            q.dequeue();
            break;
        case 3:
            q.display();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "Please enter a valid choice!!\n";
            break;
        }
        cout << endl;
    }
}

circularQueue::circularQueue(int size) {
    this->front = 0;
    this->rear = -1;
    this->length = size;
    this->queue = new int[size];
}

void circularQueue::enqueue(int val) {
    if (this->isFull()) {
        cout << "\nQueue is full!\nCan't Enqueue\n";
    } else {
        this->rear = (this->rear + 1) % length;
        this->queue[this->rear] = val;
    }
}

void circularQueue::dequeue() {
    if (this->rear == this->front) {
        cout << this->queue[this->front] << " was removed from the queue\n";
        this->front = 0;
        this->rear = -1;
        return;
    }
    if (this->isEmpty()) {
        cout << "Queue is empty!\nCan't Dequeue\n";
        return;
    }  
    cout << this->queue[this->front] << " was removed from the queue\n";
    this->front = (this->front + 1) % length;
    
}

bool circularQueue::isFull() {
    if (this->rear == -1) {
        return false;
    } else if ((this->front == (this->rear + 1) % length) || (this->front == 0 && this->rear == length - 1)) {
        return true;
    }
    return false;
}

bool circularQueue::isEmpty() {
    if (this->rear == -1) {
        return true;
    } else if (this->front == this->rear && this->front != 0) {
        return true;
    }
    return false;
}

void circularQueue::display() {
    if (this->isEmpty()) {
        cout << "Queue is empty!!\n";
        return;
    }
    if (this->rear < this->front) {
        for (int i = this->front; i <= (this->rear + length); i++) {
            cout << queue[i % length] << '\t';
        }
    } else {
        for (int i = this->front; i <= this->rear; i++) {
            cout << queue[i] << '\t';
        }
    }
    cout << endl;
}