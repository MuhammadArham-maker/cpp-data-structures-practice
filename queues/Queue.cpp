#include <iostream>
#include <queue>
#include <stack>

using namespace std;

#define MAX_QUEUE 5

// ==========================================
// 1. CIRCULAR QUEUE USING ARRAY (Q25)
// ==========================================
class CircularQueue {
private:
    int arr[MAX_QUEUE];
    int front, rear;

public:
    CircularQueue() : front(-1), rear(-1) {}

    bool isFull() {
        return (rear + 1) % MAX_QUEUE == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        if (isEmpty()) front = 0; // First insertion
        rear = (rear + 1) % MAX_QUEUE;
        arr[rear] = val;
        cout << "Enqueued: " << val << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        int val = arr[front];
        if (front == rear) { // Last element cleared
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_QUEUE;
        }
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty." << endl; return; }
        cout << "Circular Queue contents: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % MAX_QUEUE;
        }
        cout << endl;
    }
};

// ==========================================
// 2. QUEUE USING LINKED LIST (Q26)
// ==========================================
struct QNode {
    int data;
    QNode* next;
    QNode(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue {
private:
    QNode *frontNode, *rearNode;

public:
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr) {}

    bool isEmpty() { return frontNode == nullptr; }

    void enqueue(int val) {
        QNode* newNode = new QNode(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
            return;
        }
        rearNode->next = newNode;
        rearNode = newNode;
    }

    int dequeue() {
        if (isEmpty()) return -1;
        QNode* temp = frontNode;
        int val = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr; // Queue becomes empty
        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Linked List Queue empty." << endl; return; }
        QNode* temp = frontNode;
        cout << "LL Queue (Front -> Rear): ";
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// ==========================================
// 3. CROSS IMPLEMENTATIONS (Q27, Q28, Q29)
// ==========================================

// Q27: Implement Stack using Two Queues
class StackUsingQueues {
private:
    queue<int> q1, q2;

public:
    void push(int val) {
        // Step 1: Push new item into q2
        q2.push(val);
        // Step 2: Transfer all items from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        // Step 3: Swap q1 and q2
        swap(q1, q2);
    }

    int pop() {
        if (q1.empty()) return -1;
        int val = q1.front();
        q1.pop();
        return val;
    }

    int top() {
        if (q1.empty()) return -1;
        return q1.front();
    }
};

// Q28: Implement Queue using Two Stacks
class QueueUsingStacks {
private:
    stack<int> s1, s2;

public:
    void enqueue(int val) {
        s1.push(val);
    }

    int dequeue() {
        if (s1.empty() && s2.empty()) return -1;
        
        // Transfer elements to s2 only when s2 is completely empty
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int val = s2.top();
        s2.pop();
        return val;
    }
};

// Q29: Reverse a Queue using a Stack
void reverseQueue(queue<int>& q) {
    stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

// ==========================================
// 4. DEQUE USING DOUBLY LINKED LIST (Q30)
// ==========================================
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    DNode *front, *rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}

    bool isEmpty() { return front == nullptr; }

    void insertFront(int val) {
        DNode* newNode = new DNode(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void insertRear(int val) {
        DNode* newNode = new DNode(val);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }

    int deleteFront() {
        if (isEmpty()) return -1;
        DNode* temp = front;
        int val = temp->data;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return val;
    }

    int deleteRear() {
        if (isEmpty()) return -1;
        DNode* temp = rear;
        int val = temp->data;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        return val;
    }

    void display() {
        if (isEmpty()) { cout << "Deque is empty." << endl; return; }
        DNode* temp = front;
        cout << "Deque: NULL <-> ";
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// ==========================================
// INTERACTIVE MAIN INTERFACE
// ==========================================
int main() {
    int choice;
    CircularQueue cq;
    LinkedListQueue llq;
    Deque deque;

    do {
        cout << "\n===== THE QUEUE ECOSYSTEM SUITE =====" << endl;
        cout << "1. Circular Array Queue Operations (Q25)" << endl;
        cout << "2. Linked List Queue Operations (Q26)" << endl;
        cout << "3. Test Stack using Two Queues (Q27)" << endl;
        cout << "4. Test Queue using Two Stacks (Q28)" << endl;
        cout << "5. Reverse a Queue using Stack (Q29)" << endl;
        cout << "6. Deque (Double-Ended Queue) Operations (Q30)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cq.enqueue(10);
                cq.enqueue(20);
                cq.enqueue(30);
                cq.display();
                cout << "Dequeued: " << cq.dequeue() << endl;
                cq.display();
                break;

            case 2:
                llq.enqueue(100);
                llq.enqueue(200);
                llq.display();
                cout << "Dequeued: " << llq.dequeue() << endl;
                llq.display();
                break;

            case 3: {
                StackUsingQueues customStack;
                customStack.push(1);
                customStack.push(2);
                customStack.push(3);
                cout << "Stack Top (Expect 3): " << customStack.top() << endl;
                cout << "Stack Pop: " << customStack.pop() << endl;
                cout << "Stack Top now (Expect 2): " << customStack.top() << endl;
                break;
            }

            case 4: {
                QueueUsingStacks customQueue;
                customQueue.enqueue(10);
                customQueue.enqueue(20);
                cout << "Queue Dequeue (Expect 10): " << customQueue.dequeue() << endl;
                break;
            }

            case 5: {
                queue<int> q;
                q.push(1); q.push(2); q.push(3); q.push(4);
                cout << "Reversing Queue [1, 2, 3, 4]..." << endl;
                reverseQueue(q);
                cout << "Reversed Queue: ";
                while (!q.empty()) {
                    cout << q.front() << " ";
                    q.pop();
                }
                cout << endl;
                break;
            }

            case 6:
                deque.insertFront(10);
                deque.insertRear(20);
                deque.insertFront(5);
                deque.display();
                cout << "Delete Front: " << deque.deleteFront() << endl;
                cout << "Delete Rear: " << deque.deleteRear() << endl;
                deque.display();
                break;

            case 0:
                cout << "Exiting Queue Suite." << endl;
                break;

            default:
                cout << "Invalid Choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}