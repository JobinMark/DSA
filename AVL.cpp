#include <iostream>
#include <cstdlib>


struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};


struct Node* insert(struct Node* root, int key);
struct Node* deleteNode(struct Node* root, int key);
int isAVL(struct Node* root);
int findHeight(struct Node* root);
struct Node* rightRotate(struct Node* y);
struct Node* leftRotate(struct Node* x);
int max(int a, int b);


int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


struct Node* newNode(int key) {
    struct Node* node = new struct Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  
    return node;
}


struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;


    x->right = y;
    y->left = T2;

    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    
    return x;
}

// Function to perform a left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return the new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key into the AVL tree
struct Node* insert(struct Node* root, int key) {
    // Perform standard BST insert
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;  // Duplicate keys are not allowed

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // No rotation needed
    return root;
}

// Function to find the node with the minimum key value in a tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with a given key from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else  // One child case
                *root = *temp;  // Copy the contents of the non-empty child

            delete temp;
        } else {
            // Node with two children
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to check if a tree is AVL
int isAVL(struct Node* root) {
    if (root == NULL)
        return 1;

    int balance = getBalance(root);
    if (balance > 1 || balance < -1)
        return 0;

    return isAVL(root->left) && isAVL(root->right);
}

// Function to find the height of an AVL tree
int findHeight(struct Node* root) {
    if (root == NULL)
        return 0;
    return root->height;
}

// Function to create a balanced AVL tree from a sorted array
struct Node* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct Node* root = newNode(arr[mid]);

    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

// Function to count the number of nodes at a given level in an AVL tree
int countNodesAtLevel(struct Node* root, int level) {
    if (root == NULL)
        return 0;

    if (level == 1)
        return 1;

    return countNodesAtLevel(root->left, level - 1) + countNodesAtLevel(root->right, level - 1);
}

// Function to perform AVL tree operations based on user input
void performOperations() {
    struct Node* root = NULL;
    int choice, key;

    do {
        std::cout << "\nAVL Tree Operations:\n";
        std::cout << "1. Insert a node\n";
        std::cout << "2. Delete a node\n";
        std::cout << "3. Check if tree is AVL\n";
        std::cout << "4. Find the height of the tree\n";
        std::cout << "5. Convert a sorted array to AVL tree\n";
        std::cout << "6. Count nodes at a given level\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                root = insert(root, key);
                break;
            case 2:
                std::cout << "Enter key to delete: ";
                std::cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                if (isAVL(root))
                    std::cout << "The tree is AVL.\n";
                else
                    std::cout << "The tree is not AVL.\n";
                break;
            case 4:
                std::cout << "The height of the tree is: " << findHeight(root) << std::endl;
                break;
            case 5:
                {
                    int n, i;
                    std::cout << "Enter the size of the sorted array: ";
                    std::cin >> n;
                    int arr[n];
                    std::cout << "Enter the sorted array elements:\n";
                    for (i = 0; i < n; i++)
                        std::cin >> arr[i];
                    root = sortedArrayToBST(arr, 0, n - 1);
                    std::cout << "Sorted array converted to AVL tree.\n";
                }
                break;
            case 6:
                {
                    int level;
                    std::cout << "Enter the level to count nodes: ";
                    std::cin >> level;
                    std::cout << "Number of nodes at level " << level << ": " << countNodesAtLevel(root, level) << std::endl;
                }
                break;
            case 7:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 7);
}

// Main function
int main() {
    performOperations();
    return 0;
}


