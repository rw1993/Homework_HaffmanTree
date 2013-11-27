#include <iostream>
#include "BTree.h"
using namespace std;
int main()
{
  BTree<int>*t=new BTree<int>;
  cout<<t->isemptytree()<<endl;
  return 0;
}

