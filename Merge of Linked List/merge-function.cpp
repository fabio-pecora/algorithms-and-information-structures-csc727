// Merge function for assignment 3

template <typename E, typename K>
SortedChain<E,K>& SortedChain<E,K>::Merge(const SortedChain<E,K> &S2) {
    // I want to have two pointers, one to traverse chain 1 and one to traverse chain S2
    Node<E,K>* s1Pointer = this->head;
    Node<E,K>* s2Pointer = S2.head;
    
    Node<E,K>* previous = nullptr; // this is used to keep track of Chain1's last position
    
    // when s1 is an empty linked list we just want to return s2 
    if (!s1Pointer) {
        this->head = s2Pointer; // Set head to S2's head
        return *this;
    }
    
    // when s2 is an empty linked list we just want to return s1
    if (!s2Pointer) return *this;
    
    // we want to consider when there are elements in both of the linked lists to do comparison
    // if one of the two has no more elements we just add the head of the other one without need for comparison
    while (s1Pointer && s2Pointer) {
        if (s2Pointer->key < s1Pointer->key) {
            Node<E,K>* temporary = s2Pointer->next;
            // inserting the node of chain 2 into chain one before s1Pointer
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
    
    // if chain 2 still has elements and we added all the elements of chain 1 already
    if (s2Pointer) {
        if (previous) {
            previous->next = s2Pointer;
        } else {
            this->head = s2Pointer; 
        }
    }
    
    // if chain 1 still has elements and we added all the elements of chain 2 already we can just return it, or if all the elements have been added
    return *this;
}

