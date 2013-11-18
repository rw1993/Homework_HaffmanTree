#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

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

public:
    node<T> *root;
    BTree():root(NULL){};
    BTree(node<T>*nw)//��һ���ڵ�Ϊ���ڵ�
    {
        root=new node<T>;
        root=nw;
    }
    BTree(T v,node<T>*LT,node<T>*RT)//����ֵ������ӣ��Ҷ��Ӵ���һ����
    {
        root =new node<T>;
        root->data=v;
        root->leftchild=LT;
        root->rightchild=RT;
    };
    bool isemptytree()//�ж����Ƿ�Ϊ��
    {
        if(isnodeempty(root)) return 1;
        else return 0;
    }
    bool isnodeempty(node<T>*n)//�жϽڵ��Ƿ�Ϊ��
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

    node<T>*Leftchild(node<T>*Tree);//��������ӷ��������
    node<T>*Rightchild(node<T>*Tree);//�����Ҷ��ӷ����Ҷ���
    T Data()//���ظ��ڵ����ֵ
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
    void preorder(node<T>*n)//��˳�����ĳ��������Ҫ�������������������Ϊ���ڵ�
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
    int Count(node<T>*n)
    {
        if(n==NULL) return 0;
        else return 1+Count(n->leftchild)+Count(n->rightchild);
    };
    int Count_thi_tree()
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
