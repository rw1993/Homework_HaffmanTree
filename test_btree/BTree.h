#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include "LinkedQueue.h"
using namespace std;
template<typename T>
struct node
{
    T data;
    node<T>* leftchild;
    node<T>* rightchild;
    node():leftchild(NULL),rightchild(NULL){}
    node(T x,node<T>*l=NULL,node<T>*r=NULL):leftchild(l),rightchild(r)
    {
        data=x;
    }
};
template<typename T>
class BTree
{
 private:
    node<T> *root;
public:
    
    BTree():root(NULL){};
    BTree(node<T>*nw)//以一个节点为根节点
    {
        root=new node<T>;
        root=nw;
    }
    BTree(T v,node<T>*LT,node<T>*RT)//以数值，左儿子，右儿子创建一棵树
    {
        root =new node<T>;
        root->data=v;
        root->leftchild=LT;
        root->rightchild=RT;
    };
    bool isemptytree()//判断树是否为空
    {
        if(isnodeempty(root)) return 1;
        else return 0;
    }
    bool isnodeempty(node<T>*n)//判断节点是否为空
    {
        if(n==NULL)
        {
            return true;
        }
        else
            return false;
    };
    ~BTree()
    {
        if(root!=NULL)
            delete root;
    }

    node<T>*Leftchild(node<T>*Tree);//若有左二子返回左儿子
    node<T>*Rightchild(node<T>*Tree);//若有右儿子返回右儿子
    node<T>*Leftchild_of_this_tree()
    {
        Leftchild(root);
    };
    node<T>*Rightchild_of_this_tree()
    {
        Rightchild(root);
    }
    T Data()//返回根节点的数值
    {
        if(!isnodeempty(root))
        {
            return root->data;
        }
        else cerr<<"not data"<<endl;
    };
    T nodedata(node<T>*n)
    {
        if(!isnodeempty(n)) return n->data;
        else cerr<<"empty!"<<endl;
    };
    void preorder(node<T>*n)//先顺序访问某课树，若要遍历整个树，则传入参数为根节点
    {
        if(!isnodeempty(n))
        {
            cout<<n->data<<endl;
            preorder(Leftchild(n));
            preorder(Rightchild(n));
        }

    };
    void  preorder_vist_this_tree()
    {
        preorder(root);
    };
    void postorder(node<T>*n)
    {
        if(!isnodeempty(n))
        {
            postorder(Leftchild(n));
            postorder(Rightchild(n));
            cout<<n->data<<endl;
        }

    };
    void postorder_vist_this_tree()
    {
        postorder(root);
    };
    void inorder(node<T>*n)
    {
        if(!isnodeempty(n))
        {
            inorder(Leftchild(n));
            cout<<n->data<<endl;
            inorder(Rightchild(n));
        }

    };
    void inorder_the_tree()
    {
        inorder(root);
    };
    void leverorder(node<T>*n)
    {
        node<T>*tmp;
        LinkedQueue<node<T>*>*s=new LinkedQueue<node<T>*>;     
         s->EnQueue(n);
             while(!s->IsEmpty())
             {
              s->DeQueue(tmp);
              cout<<tmp->data<<endl;
              if(tmp->leftchild)
              s->EnQueue(tmp->leftchild);
              if(tmp->rightchild)
              s->EnQueue(tmp->rightchild);
         }
};
    void leverorder_the_tree()
    {
          leverorder(root);
    };
    int Count(node<T>*n)
  {
        if(n==NULL) return 0;
        else return 1+Count(n->leftchild)+Count(n->rightchild);
    };
    int Count_this_tree()
    {
      return Count(root);
    };
    int hight(node<T>*n)
    {
        if(n==NULL) return 0;
        else
            {
                int m=hight(n->leftchild);
                int l=hight(n->rightchild);
                return (m>l)?(m+1):(l+1);
            }
    }
    int hight_of_this_tree()
    {
        return hight(root);
    }
    void destroy(node<T>*n)
    {
        if(n!=NULL)
        {
            destroy(n->leftchild);
            destroy(n->rightchild);
            delete n;
        }
    }
    void destroy_this_tree()
    {
        destroy(root);
    }
} ;
template<typename T>
node<T>* BTree<T>::Rightchild(node<T>*Tree)
{
    return Tree->rightchild;
}
template<typename T>
node<T>* BTree<T>::Leftchild(node<T>*Tree)
{
    return Tree->leftchild;
}


#endif // BTREE_H_INCLUDED
