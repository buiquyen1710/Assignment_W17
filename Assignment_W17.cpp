#include <iostream>
#include <cmath>

using namespace std;

struct AVLNode {
    int data;
    AVLNode *left;
    AVLNode *right;
    int height;
};


int getHeight(AVLNode *node) {
    if (node == NULL) {
        return -1; 
    } else {
        return node->height; 
    }
}

int getBalanceFactor(AVLNode *node) {
    if (node == NULL) {
        return 0; 
    } else {
        int leftHeight = getHeight(node->left);  
        int rightHeight = getHeight(node->right); 
        return leftHeight - rightHeight; 
    }
}
AVLNode *createNode(int data) {
    AVLNode *node = new AVLNode;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}
AVLNode *rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T = x->right;
    x->right = y;
    y->left = T;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
AVLNode *rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T = y->left;
    y->left = x;
    x->right = T;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
AVLNode *insertNode(AVLNode *node, int data) {
    if (node == NULL)
        return createNode(data);
    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
void inOrderTraversal(AVLNode *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}
void preOrderTraversal(AVLNode *root) {
    if (root != NULL) {
        cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}
void postOrderTraversal(AVLNode *root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->data << " ";
    }
}
void printTree(AVLNode *root) {
    cout << "in-order: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "pre-order: ";
    preOrderTraversal(root);
    cout << endl;

    cout << "post-order: ";
    postOrderTraversal(root);
    cout << endl;
}

int main() {
    AVLNode *root = NULL;
    int n, value;
    int inputArray[100]; 

    cout << "Nh?p s? lu?ng ph?n t?: ";
    cin >> n;

    cout << "Nh?p các ph?n t?: ";
    for (int i = 0; i < n; i++) {
        cin >> inputArray[i];
    }

    for (int i = 0; i < n; i++) {
        root = insertNode(root, inputArray[i]);
        cout << "Sau khi chèn " << inputArray[i] << ":\n";
        printTree(root);
    }

    return 0;
}

