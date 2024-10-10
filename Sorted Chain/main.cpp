#include <iostream>

template <typename E, typename K>
struct Node {
    E data;
    K key;
    Node* next;

    Node(E d, K k) : data(d), key(k), next(nullptr) {}
};

template <typename E, typename K>
class SortedChain {
public:
    Node<E, K>* head;

    SortedChain() : head(nullptr) {}

    // inserting nodes in sorted order
    void Insert(E data, K key) {
        Node<E, K>* newNode = new Node<E, K>(data, key);
        if (!head || key < head->key) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<E, K>* temp = head;
            while (temp->next && temp->next->key < key) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    SortedChain<E, K>& Merge(const SortedChain<E, K>& S2);

    //  printing the chain for testing
    void Print() const {
        Node<E, K>* temp = head;
        while (temp) {
            std::cout << temp->key << " -> ";
            temp = temp->next;
        }
        std::cout << "null" << std::endl;
    }
};

template <typename E, typename K>
SortedChain<E, K>& SortedChain<E, K>::Merge(const SortedChain<E, K>& S2) {
    Node<E,K>* s1Pointer = this->head;
    Node<E,K>* s2Pointer = S2.head;
    Node<E,K>* previous = nullptr;

    if (!s1Pointer) {
        this->head = s2Pointer;
        return *this;
    }

    if (!s2Pointer) return *this;

    while (s1Pointer && s2Pointer) {
        if (s2Pointer->key < s1Pointer->key) {
            Node<E,K>* temporary = s2Pointer->next;
            if (previous) {
                previous->next = s2Pointer;
            } else {
                this->head = s2Pointer;
            }
            s2Pointer->next = s1Pointer;
            previous = s2Pointer;
            s2Pointer = temporary;
        } else {
            previous = s1Pointer;
            s1Pointer = s1Pointer->next;
        }
    }

    if (s2Pointer) {
        if (previous) {
            previous->next = s2Pointer;
        } else {
            this->head = s2Pointer;
        }
    }

    return *this;
}


int main() {
    
    SortedChain<int, int> chain1;
    SortedChain<int, int> chain2;

    
    chain1.Insert(1, 5);
    chain1.Insert(2, 8);
    chain1.Insert(3, 9);

    
    chain2.Insert(4, 4);
    chain2.Insert(5, 10);

    
    std::cout << "Chain 1 before merge: ";
    chain1.Print();

    std::cout << "Chain 2 before merge: ";
    chain2.Print();

    
    chain1.Merge(chain2);

  
    std::cout << "Merged Chain: ";
    chain1.Print();

    return 0;
}
