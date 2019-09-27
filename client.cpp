#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "stack.h"
using namespace std;

const int numWomen = 3;
const int numMen = 3;
//const int numWomen = 5;
//const int numMen = 5;


int mPref[numMen][numWomen];
int wPref[numWomen][numMen];

//keep track of women if they get proposed to indexed by w #
bool Next[numWomen] = {0};

//holds man number of currently engaged man
int Current[numWomen] = {0};

//holds bool indicating if woman is taken indexed by w #
bool IsTaken[numWomen] = {0};

//keeps track of how many women we proposed to
int ProposedTo[numMen] = {0};

void ReadMen();
void ReadWomen();
void WritePairs();

int main(){

  ReadMen();
  ReadWomen();

  //build rank table based on womans pref
  int Rank[numWomen][numMen];
    for (int i = 0; i < numWomen; ++i){
      for(int j = 0; j < numMen; ++j){
        int rank = j;
        Rank[i][wPref[i][j]] = rank;
      }
    }



  //create stack
  Stack stack = Stack();

  //push all men onto stack
  for (int i = numMen-1; i >= 0; --i){
    stack.Push(i);
  }
  /*
  stack.Push(2);
  stack.Push(1);
  stack.Push(0);
  */


  //while men are still free
  while (!stack.IsEmpty()){


      //choose man (choose top of stack)
      int chosenMan = stack.Peek();
    //  cout << "ChosenMan: " << stack.Peek();
        //get highest ranking woman on mans pref list that hasn't been proposed to

          int chosenWoman = mPref[chosenMan][ProposedTo[chosenMan]];
      //    cout << "Chosen Woman: " << chosenWoman << endl;
          //check if she has been proposed to
          //if she is free, get engaged
          if (IsTaken[chosenWoman] == false){

          //    cout << "Not taken loop\n";
            //update current array for the indexed womans man
              Current[chosenWoman] = chosenMan;
            //update next array showing woman is taken by chosenMan
              Next[chosenWoman] == chosenMan;

            //pop off Stack
          //    cout << "Popping:" << stack.Peek() << endl;
              stack.Pop();

            // update IsTaken array to show woman is now taken
              IsTaken[chosenWoman] = true;

            //update proposedTo by one
              ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
          }

          //if she is not free
          else{
          //    cout << "Taken Loop\n";
            //check if she prefers old man over us
              if (Rank[chosenWoman][chosenMan] > Rank[chosenWoman][Current[chosenWoman]]){
                    //if she likes old man more
                        //we stay on stack and go through again with next woman
                        ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
                      //  cout << "Like old more stay on, proposed to: " << Current[chosenWoman];
                      //  cout << endl;
              }
              else{
                  //if she likes us more
                  //cout << "Likes us more in taken loop\n";
                  //we pop off stack
                  //cout << "Popping: " << stack.Peek() << endl;
                  stack.Pop();

                  //old man gets put back on stack
                //  cout << "Pushing: " << Current[chosenWoman] << endl;
                  stack.Push(Current[chosenWoman]);

                  //her current man gets updated
                  Current[chosenWoman] = chosenMan;

                  //add one to number of women proposed to
                  ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
              }
          }


  }


  WritePairs();
//*/

/* ***************************SCRIPT TESTING CODE HERE

cout << "SC01:\n";
Stack Stack1 = Stack();

cout << "Ctm01 && CC01:\n";
Stack Stack2(Stack1);

cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 2: " << endl;
Stack2.Display();


cout << "op01 && Ctm01:\n";
Stack1 = Stack2;

cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 2: " << endl;
Stack2.Display();

cout << "IE01: " << Stack1.IsEmpty() << endl;

cout << "CL01:\n";
Stack1.Clear();

cout << "Pe01:";
cout << Stack1.Peek();

cout << "Pop01:\n";
Stack1.Pop();
cout << endl;

cout << "Pu01:\n";
Stack1.Push(1);
cout << "Pu02:\n";
Stack1.Push(02);

cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 2: " << endl;
Stack2.Display();

cout << "IE02: " << Stack1.IsEmpty() << endl;

cout << "Ctm02 && CC02:\n";
Stack Stack3(Stack1);
cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 3: " << endl;
Stack3.Display();

cout << "Pop02: \n";
Stack1.Pop();
cout << "Pe02: " << Stack1.Peek() << endl;


cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 2: " << endl;
Stack2.Display();

cout << "op02 && CL02:\n";
Stack2 = Stack1;
cout << "Confirm with display...\n";
cout << "Stack 1: " << endl;
Stack1.Display();
cout << "Stack 2: " << endl;
Stack2.Display();

Stack Stack4 = Stack();
cout << "AP01:\n";
Stack4.Append(1);
cout << "AP02:\n";
Stack4.Append(2);
cout << "Confirm with Peek: " << Stack4.Peek() << endl;
cout << "Confirm with Display: \n";
Stack4.Display();








*/


  return 0;
}

void ReadMen(){

  ifstream inFile ("man_pref.txt");

  if (inFile.is_open()){

    //int array[numMen][numWomen];
    for (int i = 0; i < numMen; ++i){
      for (int j = 0; j < numWomen; ++j){
        inFile >> mPref[i][j];
      }
    }

    inFile.close();
  }
  else{
    cout << "Cannot open file\n";
  }

}

void ReadWomen(){

  ifstream inFile ("w_pref.txt");


  if (inFile.is_open()){

    //int array[numWomen][numMen];
    for (int i = 0; i < numWomen; ++i){
      for (int j = 0; j < numMen; ++j){
        inFile >> wPref[i][j];
      }
    }

    inFile.close();
  }
  else{
    cout << "Cannot open file\n";
  }

}

void WritePairs(){

  ofstream outFile("results.txt");

  if (outFile.is_open()){
    for (int i = 0; i < numWomen; ++i){
      outFile << "W: " << i << " M:" << Current[i] << endl;
    }
  }
  else{
    cout << "Cannot open file\n";
  }
}
