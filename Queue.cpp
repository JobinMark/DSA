#include <iostream>
class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            front = front->next;
            delete temp;
        } else {
            std::cerr << "Queue is empty." << std::endl;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return front->data;
        } else {
            std::cerr << "Queue is empty." << std::endl;
            return -1; // You can choose a different sentinel value
        }
    }
};

int main() {
    Queue queue;

    char choice;
    int value;

    do {
        std::cout << "1. Enqueue" << std::endl;
        std::cout << "2. Dequeue" << std::endl;
        std::cout << "3. Peek" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter a value to enqueue: ";
                std::cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                queue.dequeue();
                std::cout << "Dequeued one element." << std::endl;
                break;
            case 3:
                if (!queue.isEmpty()) {
                    std::cout << "Front element: " << queue.peek() << std::endl;
                } else {
                    std::cerr << "Queue is empty." << std::endl;
                }
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
