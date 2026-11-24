#include <iostream>
using namespace std;

// ==========================================
// 1. SINGLY LINKED LIST (Q11 - Q15)
// ==========================================
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
public:
    Node* head;
    SinglyLinkedList() : head(nullptr) {}

    // Q11: Insert at Beginning
    void insertBeginning(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // Q12: Insert at End
    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Q13: Delete Node by Key
    void deleteKey(int key) {
        if (!head) {
            cout << "List is empty!" << endl;
            return;
        }
        // Case 1: Head itself holds the key
        if (head->data == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted " << key << " from beginning." << endl;
            return;
        }
        // Case 2: Search for key in remaining nodes
        Node* curr = head;
        Node* prev = nullptr;
        while (curr != nullptr && curr->data != key) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
            cout << "Key " << key << " not found in the list." << endl;
            return;
        }
        prev->next = curr->next;
        delete curr;
        cout << "Deleted " << key << " successfully." << endl;
    }

    // Q14: Reverse Iterative (The Three-Pointer Dance)
    void reverseIterative() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next; // 1. Save next
            curr->next = prev; // 2. Reverse link
            prev = curr;       // 3. Move prev forward
            curr = next;       // 4. Move curr forward
        }
        head = prev; // Reset head to new front
        cout << "Singly list reversed iteratively!" << endl;
    }

    // Q15: Reverse Recursive Helper
    Node* reverseRecursiveHelper(Node* node) {
        if (node == nullptr || node->next == nullptr) {
            return node; // Base case: empty or 1 node
        }
        Node* rest = reverseRecursiveHelper(node->next);
        node->next->next = node;
        node->next = nullptr;
        return rest;
    }

    void reverseRecursive() {
        head = reverseRecursiveHelper(head);
        cout << "Singly list reversed recursively!" << endl;
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

// ==========================================
// 2. DOUBLY LINKED LIST (Q16 & Q17)
// ==========================================
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    DNode* head;
    DoublyLinkedList() : head(nullptr) {}

    // Q16a: Insert Front
    void insertBeginning(int val) {
        DNode* newNode = new DNode(val);
        if (head) {
            head->prev = newNode;
            newNode->next = head;
        }
        head = newNode;
    }

    // Q16b: Insert End
    void insertEnd(int val) {
        DNode* newNode = new DNode(val);
        if (!head) {
            head = newNode;
            return;
        }
        DNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    // Q16c: Delete by Value
    void deleteValue(int key) {
        if (!head) return;
        DNode* curr = head;
        while (curr && curr->data != key) curr = curr->next;

        if (!curr) {
            cout << "Value not found." << endl;
            return;
        }
        if (curr->prev) curr->prev->next = curr->next;
        else head = curr->next; // Key was at head

        if (curr->next) curr->next->prev = curr->prev;

        delete curr;
        cout << "Deleted " << key << " from Doubly list." << endl;
    }

    // Q16d: Display Forward & Backward
    void displayForward() {
        DNode* temp = head;
        cout << "Forward: NULL <-> ";
        while (temp) {
            cout << temp->data << " <-> ";
            if (!temp->next) break; // Keep pointer at tail for backward display
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void displayBackward() {
        if (!head) { cout << "Backward: NULL" << endl; return; }
        DNode* temp = head;
        while (temp->next) temp = temp->next; // Go to tail

        cout << "Backward: NULL <-> ";
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    // Q17: Reverse Doubly Linked List
    void reverse() {
        if (!head) return;
        DNode* temp = nullptr;
        DNode* curr = head;

        // Swap next and prev for all nodes
        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev; // Move forward (which is currently stored in prev)
        }

        if (temp) head = temp->prev; // Reset head
        cout << "Doubly list reversed!" << endl;
    }
};

// ==========================================
// 3. CIRCULAR SINGLY LINKED LIST (Q18)
// ==========================================
class CircularLinkedList {
public:
    Node* head;
    CircularLinkedList() : head(nullptr) {}

    // Insert Beginning
    void insertBeginning(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next; // Find tail

        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }

    // Insert End
    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;

        temp->next = newNode;
        newNode->next = head;
    }

    // Delete Node
    void deleteNode(int key) {
        if (!head) return;

        Node *curr = head, *prev = nullptr;
        
        // Handle Head Deletion
        if (head->data == key) {
            if (head->next == head) { // Single node case
                delete head;
                head = nullptr;
                return;
            }
            Node* tail = head;
            while (tail->next != head) tail = tail->next;
            
            Node* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
            return;
        }

        // Searching for key
        while (curr->next != head && curr->data != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr->data == key) {
            prev->next = curr->next;
            delete curr;
        } else {
            cout << "Key not found in Circular List." << endl;
        }
    }

    void display() {
        if (!head) { cout << "Circular List is empty." << endl; return; }
        Node* temp = head;
        cout << "Circular: ";
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(Back to Head: " << head->data << ")" << endl;
    }
};

// ==========================================
// INTERACTIVE MAIN INTERFACE
// ==========================================
int main() {
    SinglyLinkedList sll;
    DoublyLinkedList dll;
    CircularLinkedList cll;

    int choice;
    do {
        cout << "\n===== GRAND LINKED LIST PLAYGROUND =====" << endl;
        cout << "1. Singly List: Insert Front / End & Display (Q11, Q12)" << endl;
        cout << "2. Singly List: Delete Key (Q13)" << endl;
        cout << "3. Singly List: Reverse Iterative (Q14)" << endl;
        cout << "4. Singly List: Reverse Recursive (Q15)" << endl;
        cout << "5. Doubly List: Insert, Display Forward/Backward (Q16)" << endl;
        cout << "6. Doubly List: Delete Value & Reverse (Q16, Q17)" << endl;
        cout << "7. Circular List: Insert, Delete, Display (Q18)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sll.insertEnd(10);
                sll.insertEnd(20);
                sll.insertBeginning(5);
                cout << "Current Singly List: ";
                sll.display();
                break;
            case 2: {
                int k; cout << "Enter value to delete: "; cin >> k;
                sll.deleteKey(k);
                sll.display();
                break;
            }
            case 3:
                sll.reverseIterative();
                sll.display();
                break;
            case 4:
                sll.reverseRecursive();
                sll.display();
                break;
            case 5:
                dll.insertBeginning(100);
                dll.insertEnd(200);
                dll.insertEnd(300);
                dll.displayForward();
                dll.displayBackward();
                break;
            case 6: {
                int val; cout << "Enter value to delete from DLL: "; cin >> val;
                dll.deleteValue(val);
                dll.reverse();
                dll.displayForward();
                break;
            }
            case 7:
                cll.insertBeginning(1);
                cll.insertEnd(2);
                cll.insertEnd(3);
                cll.display();
                cout << "Deleting 2..." << endl;
                cll.deleteNode(2);
                cll.display();
                break;
            case 0:
                cout << "Exiting Playground." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}