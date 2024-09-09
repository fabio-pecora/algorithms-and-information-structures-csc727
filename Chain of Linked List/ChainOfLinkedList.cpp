#include <iostream>
#include <new>
using namespace std;

class NoMem {
 public:
    NoMem() {}
};
void my_new_handler()
{
    throw NoMem();
}
class OutOfBounds {
 public:
    OutOfBounds() {}
};

template <class T>
struct Node{
 T data;
 Node<T> *next;
};
template <class T>
class Chain {
 public:
     Chain (){first=0; length=0;}  // constructor
     ~Chain();
     bool IsEmpty () const {return (first==0);}
     int Length() const {return length;} //
     bool Find (int k, T& x) const; // return kth element into x
     int Search (const T& x) const; // return position of x
     Chain<T>& Delete (int k, T& x); // delete k element into x 
     Chain<T>& Insert (int k,const T& x); // insert x at  k element
     Chain<T>& Extend(const Chain<T>& B); // method to attach a Chain B to the end of a Chain A
     void Output () const;
 private:
  Node<T> *first; //pointer to the first node
  int length;
};

//destructor
// complexity O(length)
template <class T>
Chain<T>::~Chain()
{
     Node<T> *nextp;
     
     while (first) {
           nextp=first->next;
           delete first;
           first=nextp;
     }
  
}

// Find kth element and return true if possible
// Complexity O(length)
template <class T>
bool Chain<T>::Find (int k, T& x) const
{
  
  Node<T> *current=first;
  if (k < 1 || k > length)
     return (false);
  for (int j = 1; j < k; j++)
       current=current->next;
  x=current->data;
  return (true);
}

// Find the position of first occurence of x, 0 otherwise
// Complexity  O(length)
template <class T>
int Chain<T>::Search(const T& x) const
{
  Node<T> *current=first;
  for (int index=0; index < length ; index++){
      if (current->data==x)
         return (++index);
      current=current->next;
  }
  return 0;
}
        
//Delete kth element of the list and return value to x
//OutOfBound exception is thrown if k< 1 or k > length
//complexity O(length-k)=O(length)
template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
   Node<T> *current=first,*prior=first;
   int index=1;
   if (Find(k,x)) { // able to locate k node
       while (index < k) {
              prior=current;
              current=current->next;
              index++;
       }
       x=current->data;
       if (k==1)   //we want to delete first node
          first = current->next;
       else  //we want to delete another node
          prior->next = current->next;
       delete current; //delete node
       length--;
       return *this;
   }
   throw OutOfBounds();
}



// insert x into k position
// throws exception OutOfBound if k < 1 or k > 
// throws exception NoMem if list is full;
template <class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
   if (k < 1 || k > length + 1)
      throw OutOfBounds();
   Node<T> *current=first, *prior=first;
   for (int index=1; index < k; index++) {
       prior=current;
       current=current->next;
   }
   Node <T> *newnode=new Node<T>;
   newnode->data=x;
   if (k==1) {
       first = newnode;
   } else {
       prior->next = newnode;
     }
   newnode->next = current;
   length++;
   return *this;
}

template <class T>
Chain<T>& Chain<T>::Extend(const Chain<T>& B) {
    // when B is empty we simply return A (this)
    if (B.IsEmpty()) {
        return *this; 
    }
    // start from first node of B
    Node<T> *currentB = B.first;
    // traverse linkedlist till the next of current B exists and it is not null
    while (currentB) {
        // insert and move to the next node
        Insert(length + 1, currentB->data);
        currentB = currentB->next; 
    }
    return *this;
}


//outputs list
template<class T>
void Chain<T>::Output() const
{
  Node<T> *current=first; 
  while (current){
    cout << current->data << " ";
    current=current->next;
  }
}
main()
{ 
  
  set_new_handler(my_new_handler);//when new fails, new call my_new_handler
                                  // which in return throws a NoMem exception
 try {
    Chain<int> A;
        Chain<int> B;
        A.Insert(1, 8).Insert(2, 12).Insert(3, 44).Insert(4, 3);
        cout << "Chain A: ";
        A.Output();
        cout << endl;
        B.Insert(1, 18).Insert(2, 9).Insert(3, 123);
        cout << "Chain B: ";
        B.Output();
        cout << endl;
        A.Extend(B);
        cout << "Extended Chain A: ";
        A.Output();
  }
  catch(NoMem) {
    cerr << "Not enough memory" << endl;
  }
  catch(OutOfBounds) {
    cerr << "Out of bounds " << endl;
  }
}