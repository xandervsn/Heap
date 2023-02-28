#include <iostream>
#include <cstring>

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
      tree = pop(tree, 1);
    }else if(strcmp(input, "DLTALL") == 0){

    }else if(strcmp(input, "PRINT") == 0){
      cout << "(" << tree[1] << ")" << endl;
      print(tree, 1);
    }
  }
  return 0;
}

void print(int* tree, int i){
  int last = getLast(tree);
  int left = getLeft(i);
  int right = getRight(i);
  cout << "(";
  if(tree[left] > -1){
    cout << tree[left] << ",";
  }
  if(tree[right] > -1){
    cout << tree[right];
  }
  cout << ") ";

  if(tree[left] > -1 && tree[right] > -1){
    print(tree, left);
    print(tree, right);
  }
}

int* pop(int* tree, int i){
  if(getLeft(1) == -1 && getRight(1) == -1){
    tree[1] = -1;
    return tree;
  }
  if(i == 1){
    int last = getLast(tree);
  }
  int parent = getParent(last);
  int parentval = tree[parent];
  int grandparent = getParent(parent);
  tree[last] = -1;
  tree[parent] = tree[last];
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
