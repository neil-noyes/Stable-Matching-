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


  //while men are still free
  while (!stack.IsEmpty()){


      //choose man (choose top of stack)
      int chosenMan = stack.Peek();

        //get highest ranking woman on mans pref list that hasn't been proposed to
          int chosenWoman = mPref[chosenMan][ProposedTo[chosenMan]];

          //check if she has been proposed to
          //if she is free, get engaged
          if (IsTaken[chosenWoman] == false){

            //update current array for the indexed womans man
              Current[chosenWoman] = chosenMan;
            //update next array showing woman is taken by chosenMan
              Next[chosenWoman] == chosenMan;

            //pop off Stack
              stack.Pop();

            // update IsTaken array to show woman is now taken
              IsTaken[chosenWoman] = true;

            //update proposedTo by one
              ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
          }

          //if she is not free
          else{
            //check if she prefers old man over us
              if (Rank[chosenWoman][chosenMan] > Rank[chosenWoman][Current[chosenWoman]]){
                    //if she likes old man more
                        //we stay on stack and go through again with next woman
                        ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
              }
              else{
                  //if she likes us more
                  //we pop off stack
                  stack.Pop();

                  //old man gets put back on stack
                  stack.Push(Current[chosenWoman]);

                  //her current man gets updated
                  Current[chosenWoman] = chosenMan;

                  //add one to number of women proposed to
                  ProposedTo[chosenMan] = ProposedTo[chosenMan]+1;
              }
          }


  }


  WritePairs();

  return 0;
}

void ReadMen(){

  ifstream inFile ("man_pref.txt");

  if (inFile.is_open()){

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
