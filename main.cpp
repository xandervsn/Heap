/* Xander Siruno-Nebel
   C++/Data Structures, Galbraith
   3/1/2023

   Heap: implementation of a max heap (binary tree in which each child is less than the parent) in C++
 */

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int getParent(int);
int getLeft(int);
int getRight(int);
int* add(int, int*);
int* pop(int*, int);
int* checkAdd(int, int*, int);
int* clear(int*);
int getLast(int*);
void print(int*, int);

int main(){
  srand(time(0));
  int* tree = new int[101];
  tree = clear(tree);
  while(true){
    cout << "Input a valid command (ADD, DLT, DLTALL, PRINT)" << endl;
    char input[10];
    cin >> input;
    if(strcmp(input, "ADD") == 0){
      cout << "Add by user (U) or file input (F)?" << endl;
      cin >> input;
      if(strcmp(input, "U") == 0){
	int intin = 0;
	cin >> intin;
        tree = add(intin, tree);
      }else if(strcmp(input, "F") == 0){
	cout << "How many numbers to add? (0-50)" << endl;
	int intin = 0;
	cin >> intin;

	for(int i = 0; i < intin; i++){
	  //follwing code taken from Hashmap
	  ifstream firstFile;
	  firstFile.open("nums.txt");
	  char arr[100][50];
	  int j = 0;
	  while(firstFile.getline(arr[j], 49, ' ')){
	    j++;
	  }
	  //pick random name from created char* array above
	  int random = rand() % 10;
	  //turn that char* into an int
	  int num = atoi(arr[random]);
	  tree = add(num, tree);
	}
      }
    }else if(strcmp(input, "DLT") == 0){
      if(tree[1] == -1){
	cout << "This heap is empty!" << endl;
      }else{
	cout << tree[1] << endl;
      }
      tree = pop(tree, 1);
    }else if(strcmp(input, "DLTALL") == 0){
      //slight redunancy, otherwise some nums not popped
      for(int i = 0; i <= 100; i++){
	//if a node has a value, print it, then pop
	if(tree[1] != -1){
	  cout << tree[1] << endl;
	}
	tree = pop(tree, 1);
      }
    }else if(strcmp(input, "PRINT") == 0){
      if(tree[1] == -1){
        cout << "This heap is empty!" << endl;
      }else{
	cout << "Each ordered pair corresponds to 1 parent, which is the 1st value in the above ordered pair." << endl;
	cout << "(" << tree[1] << ")" << endl;
      }
      print(tree, 2);
    }
  }
  return 0;
}

void print(int* tree, int i){
  if(tree[i] == -1 || i > 100){
    //we've reached the end of the tree
    return;
  }
  cout << "(";
  for(int j = i; j < i*2; j++){
    //visualize a tree - index of array at first node of new row = nodes in that row
    if(tree[j] == -1 || i > 100){
      cout << ")" << endl;
      return;
    }else{
      cout << tree[j] << ",";
    }
    if(j % 2 != 0){
      cout << ") (";
    }
  }
  cout << ")" << endl;
  print(tree, i*2);
}

int* pop(int* tree, int i){
  int left = tree[getLeft(i)];
  int right = tree[getRight(i)];
  int greatest = 0;
  //goes from top of tree to bottom through highest child, setting each parent to its child
  if(left > right){
    greatest = left;
  }else{
    greatest = right;
  }
  tree[i] = greatest;

  if(greatest == -1){
    return tree;
  }
  if(greatest == left){
    i = getLeft(i);
  }else{
    i = getRight(i);
  }
  pop(tree, i);
}

int* checkAdd(int num, int* tree, int child){
  int parent = getParent(child);
  if(child == 1){
    return tree;
  }
  if(tree[parent] > tree[child]){
    //if the parent is greater than the child (or it's the 1st input), all is well
    return tree;
  }else{
    //if it's not, swap them and recurse
    int temp = tree[parent];
    tree[parent] = num;
    tree[child] = temp;
    checkAdd(num, tree, parent);
  }
}

int getLast(int* tree){
  int i = 1;
  while(true){
    if(tree[i] == -1){
      return i;
    }
    i++;
  }
  cout << "ERROR: Binary tree is full" << endl;
  return -1;
}

int* add(int num, int* tree){
  //pretty boilerplate, real stuff in checkAdd
  int i = getLast(tree);
  tree[i] = num;
  tree = checkAdd(num, tree, i);
  return tree;
}

int getLeft(int i){
  return i*2;
}

int getRight(int i){
  return i*2+1;
}

int getParent(int i){
  if(i % 2 == 0){
    //even num
    return i/2;
  }else{
    //odd num
    return (i-1)/2;
  }
}

int* clear(int* tree){
  //init arr
  for(int i = 0; i <= 101; i++){
    tree[i] = -1;
  }
  tree[0] = -2;
  return tree;
}
