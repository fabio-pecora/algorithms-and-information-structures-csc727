#include <iostream>
using namespace std;


class MaxHBLT {
public:
    MaxHBLT();                    
    ~MaxHBLT();                   
    void Insert(const int& key);   
    void DeleteMax(int& max);      
    void Merge(MaxHBLT& other);   

private:
    struct Node {                  
        int element;          
        Node* left;                
        Node* right;              
        int sValue;           

        Node(int elem) : element(elem), left(nullptr), right(nullptr), sValue(1) {}
    };

    Node* root;                  
    void Clear(Node* t);           
    Node* Merge(Node* h1, Node* h2); 
    void SwapChildren(Node* t);  
};

MaxHBLT::MaxHBLT() {
    root = nullptr;
}

MaxHBLT::~MaxHBLT() {
    Clear(root);
}

void MaxHBLT::Insert(const int& key) {
    Node* newNode = new Node(key);
    root = Merge(root, newNode);
}

void MaxHBLT::DeleteMax(int& max) {
    if (root == nullptr) throw "Tree is empty";
    max = root->element;
    Node* oldRoot = root;
    root = Merge(root->left, root->right);
    delete oldRoot;
}

void MaxHBLT::Merge(MaxHBLT& other) {
    root = Merge(root, other.root);
    other.root = nullptr;
}

void MaxHBLT::Clear(Node* t) {
    if (t != nullptr) {
        Clear(t->left);
        Clear(t->right);
        delete t;
    }
}

MaxHBLT::Node* MaxHBLT::Merge(Node* h1, Node* h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    if (h1->element < h2->element) std::swap(h1, h2);

    h1->right = Merge(h1->right, h2);

    if (h1->left == nullptr || h1->left->sValue < h1->right->sValue) {
        std::swap(h1->left, h1->right);
    }

    if (h1->right == nullptr) h1->sValue = 1;
    else h1->sValue = h1->right->sValue + 1;

    return h1;
}

int main() {
    int A[100];  
    int n;      

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    MaxHBLT maxHeap;

    for (int i = 0; i < n; i++) {
        maxHeap.Insert(A[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        maxHeap.DeleteMax(A[i]);
    }

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    if (n >= 3) {
        cout << "Three smallest elements are: " << A[0] << ", " << A[1] << ", " << A[2] << endl;
    } else {
        cout << "The array has fewer than 3 elements." << endl;
    }

    return 0;
}
