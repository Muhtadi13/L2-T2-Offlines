#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 30005
#define lgmax 30
lli MOD = 100000007LL;
using namespace std;

template <class T>
class Node
{
    T value;
    int order;
    Node *rightsibling;
    Node *leftchild;
    Node *parent;

public:
    void setValue(T v)
    {
        value = v;
    }

    T getValue()
    {
        return value;
    }

    void setRightSibling(Node *x)
    {
        rightsibling = x;
    }
    Node *getRightSibling()
    {
        return rightsibling;
    }
    void setLeftChild(Node *x)
    {
        leftchild = x;
    }
    Node *getLeftChild()
    {
        return leftchild;
    }

    void setParent(Node *x)
    {
        parent = x;
    }
    Node *getParent()
    {
        return parent;
    }
    void setOrder(int o)
    {
        order = o;
    }
    int getOrder()
    {
        return order;
    }
};

class BinomialHeap
{
    vector<Node<int> *> roots;
    int cnt;
    Node<int>* head;

    Node<int> *mergeTrees(Node<int> *par, Node<int> *child)
    {
        child->setParent(par);
        child->setRightSibling(par->getLeftChild());
        par->setLeftChild(child);
        par->setOrder(par->getOrder() + 1);
        return par;
    }

public:
    BinomialHeap(vector<Node<int>*> r)
    {
        roots = r;
        cnt = r.size();
    }
    BinomialHeap()
    {
        cnt = 0;
    }

    BinomialHeap merge(BinomialHeap a,BinomialHeap b)
    {
        vector<Node<int> *> res;
        vector<Node<int> *> arr = a.roots;
        vector<Node<int> *> arr2=b.roots;
        int i = 0;
        int j = 0;

        while (i < a.cnt && j < (b.cnt))
        {
            if (arr[i]->getOrder() <= arr2[i]->getOrder())
            {
                res.push_back(arr[i]);
                i++;
            }
            else
            {
                res.push_back(arr2[j]);
                j++;
            }
        }

        while (i < a.cnt)
        {
            res.push_back(arr[i]);
            i++;
        }
        while (j < (b.cnt))
        {
            res.push_back(arr2[j]);
            j++;
        }

        vector<Node<int> *> fin;
        i = 0;
        int sz = res.size();

        while (i + 1 < sz)
        {
            if (res[i]->getOrder() < res[i + 1]->getOrder())
            {
                fin.push_back(res[i]);
            }
            else if (i + 2 < sz && res[i]->getOrder() == res[i + 1]->getOrder() && res[i + 1]->getOrder() == res[i + 2]->getOrder())
            {
                fin.push_back(res[i]);
            }
            else
            {
                Node<int> *add = mergeTrees(res[i], res[i + 1]);
                res[i + 1] = add;
            }
            i++;
        }
        fin.push_back(res[i]);
        BinomialHeap h(fin);
        return h;
    }

    Node<int>* findMin(BinomialHeap a)
    {
        Node<int> *ans = NULL;
        lli mn = MOD;
        for (int i = 0; i < a.cnt; i++)
        {
            if (a.roots[i]->getValue() < mn)
            {
                mn = a.roots[i]->getValue();
                ans = a.roots[i];
            }
        }
        return ans;
    }
    BinomialHeap treeHeapify(BinomialHeap m,Node<int> *root)
    {
        BinomialHeap h;
        h.roots.push_back(root);
        m = merge(m,h);
        return m;
    }

    BinomialHeap insert(BinomialHeap b,int val)
    {
        Node<int> *nw = new Node<int>;
        nw->setValue(val);
        return treeHeapify(b,nw);
    }

    BinomialHeap extractMin(BinomialHeap a)
    {
        Node<int> *toremove = findMin(a);
        Node<int> *it = toremove->getLeftChild();
        Node<int> *prev = it;

        BinomialHeap b;
        BinomialHeap treeheap;
        

        for (int i = 0; i < cnt; i++)
        {
            if (a.roots[i]->getValue() != toremove->getValue())
            {
                b.roots.push_back(a.roots[i]);
            }
        }

        while (it != NULL)
        {
            prev = it;
            it = it->getRightSibling();
            it->setRightSibling(NULL);
            treeheap.roots.push_back(it);
        }
        for (int i = 0; 2 * i < treeheap.roots.size(); i++)
        {
            swap(treeheap.roots[i], treeheap.roots[treeheap.roots.size() - i - 1]);
        }
        b=merge(b,treeheap);
        return b;
    }

};

int main()
{

}