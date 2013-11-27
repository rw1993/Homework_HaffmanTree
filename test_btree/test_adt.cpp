#include <iostream>
#include "BTree.h"
using namespace std;
int main()
{
  BTree<int>*t=new BTree<int>;
  cout<<"if t empty(1=yes,0=no):";
  cout<<t->isemptytree()<<endl;
  node<int>*n=new node<int>(5);
  BTree<int>*t1=new BTree<int>(n);
  cout<<"if t1 empty(1=yes,0=no):";
  cout<<t1->isemptytree()<<endl;
  node<int>*n1=new node<int>(6);
  node<int>*n2=new node<int>(4);
  n->leftchild=n1;
  n->rightchild=n2;
  BTree<int>*t2=new BTree<int>(n);
  cout<<"后续访问t2"<<endl;
  t2->postorder_vist_this_tree();
   cout<<"前续访问t2"<<endl;
   t2->preorder_vist_this_tree();
   cout<<"中续访问t2"<<endl;
   t2->inorder_the_tree() ;
   cout<<"层续访问t2"<<endl;
   t2->leverorder_the_tree();
   cout<<"求t2树高"<<endl;
  cout<<t2->hight_of_this_tree()<<endl;
  cout<<"访问t2左儿子"<<endl;
  node<int>*tmpn;
  tmpn=t2->Leftchild_of_this_tree();
  cout<<tmpn->data<<endl;
 cout<<"访问t2右儿子"<<endl;
  tmpn=t2->Rightchild_of_this_tree();
  cout<<tmpn->data<<endl;
   return 0;
}

