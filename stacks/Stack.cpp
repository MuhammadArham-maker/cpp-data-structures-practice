#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

#define MAX_SIZE 100

// ==========================================
// 1. STACK USING ARRAY (Q19)
// ==========================================
class ArrayStack {
private:
    int arr[MAX_SIZE];
    int top;

public:
    ArrayStack() { top = -1; }

    bool isFull() { return top == MAX_SIZE - 1; }
    bool isEmpty() { return top == -1; }

    void push(int val) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = val;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[top];
    }

    void display() {
        if (isEmpty()) { cout << "Stack is empty." << endl; return; }
        cout << "Array Stack (Top -> Bottom): ";
        for (int i = top; i >= 0; i--) cout << arr[i] << " ";
        cout << endl;
    }
};

// ==========================================
// 2. STACK USING LINKED LIST (Q20)
// ==========================================
struct StackNode {
    char data; // Polymorphic node for characters/numbers
    StackNode* next;
    StackNode(char val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    StackNode* topNode;

public:
    LinkedListStack() { topNode = nullptr; }

    bool isEmpty() { return topNode == nullptr; }

    void push(char val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode; // New node becomes the new top (Front insertion)
    }

    char pop() {
        if (isEmpty()) return '\0';
        StackNode* temp = topNode;
        char poppedValue = temp->data;
        topNode = topNode->next;
        delete temp;
        return poppedValue;
    }

    char peek() {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    ~LinkedListStack() {
        while (!isEmpty()) pop();
    }
};

// ==========================================
// 3. STACK APPLICATIONS (Q21 - Q24)
// ==========================================

// Q22: Reverse String using Custom Stack
string reverseString(const string& str) {
    LinkedListStack s;
    for (char ch : str) s.push(ch);
    
    string reversed = "";
    while (!s.isEmpty()) {
        reversed += s.pop();
    }
    return reversed;
}

// Q21: Check Balanced Parentheses ({[()]})
bool isBalanced(const string& expr) {
    LinkedListStack s;
    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) return false;
            char topChar = s.pop();
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                return false;
            }
        }
    }
    return s.isEmpty(); // Balanced if stack is completely emptied
}

// Q23 Helpers: Operator Precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

// Q23: Infix to Postfix Conversion
string infixToPostfix(const string& infix) {
    LinkedListStack s;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) { // If operand, output immediately
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            if (!s.isEmpty()) s.pop(); // Pop '('
        } else { // Operator encountered
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    // Pop remaining operators
    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

// Q24: Evaluate Postfix Expression
int evaluatePostfix(const string& postfix) {
    ArrayStack s; // Using array stack for numerical calculation

    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0'); // Convert char digit to integer
        } else {
            int val2 = s.pop(); // First pop is operand 2
            int val1 = s.pop(); // Second pop is operand 1

            switch (ch) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                case '^': s.push(pow(val1, val2)); break;
            }
        }
    }
    return s.pop();
}

// ==========================================
// INTERACTIVE MAIN INTERFACE
// ==========================================
int main() {
    int choice;
    ArrayStack arrStack;

    do {
        cout << "\n===== THE STACK ENGINE & PARSER =====" << endl;
        cout << "1. Test Array Stack Operations (Push, Pop, Peek) (Q19)" << endl;
        cout << "2. Reverse a String using Stack (Q22)" << endl;
        cout << "3. Check Balanced Parentheses (Q21)" << endl;
        cout << "4. Convert Infix to Postfix (Q23)" << endl;
        cout << "5. Evaluate Postfix Expression (Q24)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                arrStack.push(10);
                arrStack.push(20);
                arrStack.push(30);
                arrStack.display();
                cout << "Popped Top Value: " << arrStack.pop() << endl;
                cout << "Current Top (Peek): " << arrStack.peek() << endl;
                arrStack.display();
                break;
            }
            case 2: {
                string inputStr;
                cout << "Enter string to reverse: ";
                cin >> inputStr;
                cout << "Reversed String: " << reverseString(inputStr) << endl;
                break;
            }
            case 3: {
                string expr;
                cout << "Enter bracket expression (e.g., {[()]}): ";
                cin >> expr;
                if (isBalanced(expr)) {
                    cout << "Result: Valid & Balanced Brackets!" << endl;
                } else {
                    cout << "Result: Unbalanced Brackets detected." << endl;
                }
                break;
            }
            case 4: {
                string infix;
                cout << "Enter Infix Expression (e.g., (A+B)*C-D): ";
                cin >> infix;
                cout << "Postfix Notation: " << infixToPostfix(infix) << endl;
                break;
            }
            case 5: {
                string postfix;
                cout << "Enter Single-Digit Postfix Expression (e.g., 231*+9-): ";
                cin >> postfix;
                cout << "Evaluated Result: " << evaluatePostfix(postfix) << endl;
                break;
            }
            case 0:
                cout << "Exiting Stack Engine." << endl;
                break;
            default:
                cout << "Invalid Option!" << endl;
        }
    } while (choice != 0);

    return 0;
}