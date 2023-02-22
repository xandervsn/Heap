#include <iostream>
#include <cstring>

using namespace std;

int getParent(int);
int getLeft(int);
int getRight(int);
int* add(int, int*);
int* checkAdd(int, int*, int);
int* clear(int*);
int getLast(int*);
void print(int*);

int main(){
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
	int uin;
	cin >> uin;
	tree = add(uin, tree);
	//cout << tree[1] << endl;
      }else if(strcmp(input, "F") == 0){

      }
    }else if(strcmp(input, "DLT") == 0){
      
    }else if(strcmp(input, "DLTALL") == 0){

    }else if(strcmp(input, "PRINT") == 0){
      print(tree);
    }
  }
  return 0;
}

void print(int* tree){
  cout << tree[1] << endl;
  cout << tree[2] << ", " << tree[3] << endl;
}

int* checkAdd(int num, int* tree, int i){
  int parent = getParent(i);
  cout << "0: " << parent << endl;
  cout << "1: " << tree[parent] << endl;
  cout << "2: " << tree[i] << endl;
  if(parent = 1){
    return tree;
  }
  if(tree[parent] > num){
    //if the parent is greater than the child (or it's the 1st input), we're in the right place
    return tree;
  }else{
    //if it's not, swap them and recurse
    int temp = tree[parent];
    tree[parent] = num;
    tree[i] = temp;
    checkAdd(num, tree, parent);
  }
}

int getLast(int* tree){
  for(int i = 0; i <= 101; i++){
    if(tree[i] == -1){
      return i;
    }
  }
  cout << "ERROR: Binary tree is full" << endl;
  return -1;
}

int* add(int num, int* tree){
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
  for(int i = 0; i <= 101; i++){
    tree[i] = -1;
  }
  tree[0] = -2;
  return tree;
}
