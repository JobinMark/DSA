#include <iostream>

const int MAX_SIZE = 100;

class Stack {
private:
    int arr[MAX_SIZE];
    int top;

public:
    Stack() {
        top = -1; // Initialize the top of the stack
    }

    void push(int value) {
        if (top >= MAX_SIZE - 1) {
            std::cout << "Stack overflow! Cannot push more elements." << std::endl;
            return;
        }

        arr[++top] = value;
        std::cout << value << " pushed to the stack." << std::endl;
    }

    void pop() {
        if (top < 0) {
            std::cout << "Stack underflow! Cannot pop from an empty stack." << std::endl;
            return;
        }

        std::cout << arr[top--] << " popped from the stack." << std::endl;
    }

    int peek() {
        if (top < 0) {
            std::cout << "Stack is empty. Cannot peek." << std::endl;
            return -1; // Assuming -1 represents an error or an empty stack in this example
        }

        return arr[top];
    }

    bool isEmpty() {
        return top < 0;
    }
};

int main() {
    Stack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    std::cout << "Top element: " << myStack.peek() << std::endl;

    myStack.pop();
    myStack.pop();

    std::cout << "Is the stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
