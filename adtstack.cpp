#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }
    void pop() {
        if (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return top->data;
        } else {
            std::cerr << "Stack is empty." << std::endl;
            return -1; // You can choose a different sentinel value
        }
    }
};

int main() {
    Stack stack;

    char choice;
    int value;

    do {
        std::cout << "1. Push" << std::endl;
        std::cout << "2. Pop" << std::endl;
        std::cout << "3. Peek" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter a value to push: ";
                std::cin >> value;
                stack.push(value);
                break;
            case 2:
                stack.pop();
                std::cout << "Popped one element." << std::endl;
                break;
            case 3:
                std::cout << "Top element: " << stack.peek() << std::endl;
                break;
            case 4:
                std::cout << "Quitting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);
    return 0;
}
