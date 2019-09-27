#include <iostream>
using namespace std;

struct node {
   int data;
   node* next;
};

class Stack{

  public:
    Stack();
    /*Narrative: Stack default constructor
    Pre-condition: n/a
    Post-condition: stack is constructed*/

    ~Stack();
    /*Narrative: Stack destructor
    Pre-condition: stack created
    Post-condition: stack is destroyed*/

    Stack(const Stack& otherStack);
    /*Narrative: Stack copy constructor
    Pre-condition: otherStack created
    Post-condition: stack is constructed based on otherStack*/

    Stack& operator=(const Stack& otherStack);
    /*Narrative: Stack overloaded assignment operator
    Pre-condition: stack and otherStack created
    Post-condition: stack is cleared and made identical to otherStack*/

    void Push(int val);
    /*Narrative: pushes data onto stack
    Pre-condition: stack is created
    Post-condition: data is pushed onto the stack*/

    void Pop();
    /*Narrative: removes top node
    Pre-condition: stack is created
    Post-condition: removes top node from stack if stack is not empty*/

    int Peek() const;
    /*Narrative: returns the data from the top node
    Pre-condition: stack is created
    Post-condition: returns data stored in top node as long as stack is not empty*/

    bool IsEmpty() const;
    /*Narrative: returns bool indicating if stack is empty
    Pre-condition: stack is created
    Post-condition: returns bool indicating emptiness*/

    void Append(int data);
    /*Narrative: adds to end of stack instead of pushing (only for copy copnstructor)
    Pre-condition: stack is created
    Post-condition: add data to a new node added to end*/

    void Display() const;

  private:

    void CopyToMe(const Stack& otherStack);
    /*Narrative: Makes deep copy of otherStack
    Pre-condition: stack & otherStack created
    Post-condition: stack will contain deep copy of otherStack*/

    void Clear();
    /*Narrative: clears stack
    Pre-condition: stack created
    Post-condition: stack will have no elements*/

    node* top;
};
