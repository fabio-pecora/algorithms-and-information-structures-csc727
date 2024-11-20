#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char letter;    
    int frequency;  
    Node* left;    
    Node* right;    
    
    Node(char l, int f) : letter(l), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency; 
    }
};

class MinHeap {
private:
    vector<Node*> heap;

    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left]->frequency < heap[smallest]->frequency)
            smallest = left;
        if (right < heap.size() && heap[right]->frequency < heap[smallest]->frequency)
            smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[index]->frequency < heap[parent]->frequency) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

public:
    void insert(Node* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    Node* extractMin() {
        if (heap.empty()) return nullptr;
        Node* minNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return minNode;
    }

    int size() const {
        return heap.size();
    }
};

void generateCodes(Node* root, string code, vector<pair<char, string>>& codes) {
    if (!root) return;
    if (!root->left && !root->right) { 
        codes.push_back({root->letter, code});
    }
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}


int main() {
    int n;
    cout << "Enter number of letters (up to 10): ";
    cin >> n;

    vector<Node*> nodes;
    for (int i = 0; i < n; ++i) {
        char letter;
        int freq;
        cout << "Enter letter and its frequency: ";
        cin >> letter >> freq;
        nodes.push_back(new Node(letter, freq));
    }

    MinHeap minHeap;
    for (Node* node : nodes) {
        minHeap.insert(node);
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();
        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        minHeap.insert(parent);
    }

    Node* root = minHeap.extractMin();
    vector<pair<char, string>> codes;
    generateCodes(root, "", codes);

 
    cout << "Huffman Codes:\n";
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
