#include <iostream>
#include "stack.h"
using namespace std;

Stack::Stack():top(NULL)
{}

Stack::~Stack(){
    while (!IsEmpty()){
      Pop();
    }
}

Stack::Stack(const Stack& otherStack):top(NULL){
  if (!otherStack.IsEmpty()){
    CopyToMe(otherStack);
  }
}

Stack& Stack::operator=(const Stack& otherStack){

  if (this != &otherStack){
    if(!IsEmpty()){
      Clear();
    }
    CopyToMe(otherStack);
  }

  return *this;
}

void Stack::CopyToMe(const Stack& otherStack){

  if (!otherStack.IsEmpty()){

    node* tracer = otherStack.top;
    while (tracer != NULL){
      Append(tracer->data);
      tracer = tracer->next;
    }

  }

}

void Stack::Clear(){
  while (!IsEmpty()){
    Pop();
  }
}

void Stack::Push(int data) {
  // create new node temp and allocate memory
  node* temp;
  temp = new node();

  // check if stack  is full
    if (!temp) {
      cout << "\nHeap Overflow";
    }

    // initialize data into temp data field
    temp->data = data;

    // put top pointer reference into temp link
    temp->next = top;

    // make temp as top of Stack
    top = temp;

}

void Stack::Append(int data){
  node* temp;
  temp = new node();

  temp->data = data;
  temp->next = NULL;

  if (top != NULL){
    node* tracer = top;
    while (tracer->next != NULL){
      tracer = tracer->next;
    }
    tracer->next = temp;
  }
  else{
    temp->next = top;
    top = temp;
  }
}

int Stack::Peek() const{
  if (!IsEmpty()){
    return (top->data);
  }
}

bool Stack::IsEmpty() const{
  bool empty = false;;
  if (top == NULL){
    empty = true;
  }
  return empty;
}

void Stack::Pop() {

   node* temp;

   if(IsEmpty())
      cout<<"\n"<<endl;
   else {
      temp = top;
      top = top->next;
      temp->next = NULL;
      delete(temp);
   }

}

void Stack::Display() const{
   if(IsEmpty())
      cout<<"\n";
   else {
      node* ptr = top;
      while (ptr != NULL) {
         cout<< ptr->data <<" ";
         ptr = ptr->next;
      }
   }
   cout<<endl;
}
