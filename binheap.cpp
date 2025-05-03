#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 30005
#define lgmax 30
// #define cin in
lli MOD = 100000007LL;
using namespace std;

template <class T>
class Node
{
    T value;
    int order;
    Node *rightsibling;
    Node *leftchild;

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
    Node<int> *first;

    Node<int> *mergeTrees(Node<int> *par, Node<int> *child)
    {

        child->setRightSibling(par->getLeftChild());
        par->setLeftChild(child);
        par->setOrder(par->getOrder() + 1);
        return par;
    }

    Node<int> *getFirst()
    {
        return first;
    }
    void setFirst(Node<int> *f)
    {
        first = f;
    }

public:
    BinomialHeap()
    {
        first = NULL;
    }
    BinomialHeap(Node<int> *init)
    {
        first = init;
        first->setLeftChild(NULL);
        first->setRightSibling(NULL);
        first->setOrder(0);
    }
    Node<int> *findMin()
    {
        Node<int> *it = first;
        Node<int> *ret = first;
        lli mn = MOD;
        while (it != NULL)
        {
            if (it->getValue() < mn)
            {
                mn = it->getValue();
                ret = it;
            }
            it = it->getRightSibling();
        }
        return ret;
    }

    void Union(BinomialHeap a)
    {
        if (a.getFirst() == NULL)
        {
            // print();
            // cout<<"nullinull\n";
            return;
        }
        else if (first == NULL)
        {
            first = a.getFirst();
            // cout<<"firstnull\n";
            // print();
            return;
        }

        auto root1 = first;
        auto root2 = a.getFirst();

        Node<int> *it = NULL;
        if (root1->getOrder() <= root2->getOrder())
        {
            it = root1;
            root1 = root1->getRightSibling();
        }
        else
        {
            it = root2;
            root2 = root2->getRightSibling();
        }

        Node<int> *res = it;

        while (root1 != NULL && root2 != NULL)
        {
            if (root1->getOrder() > root2->getOrder())
            {
                it->setRightSibling(root2);
                root2 = root2->getRightSibling();
            }
            else
            {
                it->setRightSibling(root1);
                root1 = root1->getRightSibling();
            }
            it = it->getRightSibling();
        }
        while (root1 != NULL)
        {
            it->setRightSibling(root1);
            root1 = root1->getRightSibling();
            it = it->getRightSibling();
        }
        while (root2 != NULL)
        {
            it->setRightSibling(root2);
            root2 = root2->getRightSibling();
            it = it->getRightSibling();
        }

        Node<int> *it1 = NULL;
        Node<int> *it2 = NULL;
        Node<int> *it3 = NULL;

        it2 = res;
        if (it2 != NULL)
            it3 = it2->getRightSibling();

        while (it3 != NULL)
        {

            if (it3->getOrder() != it2->getOrder())
            {
                it1 = it2;
                it2 = it3;
            }
            else if (it3->getRightSibling() != NULL && it3->getOrder() == it2->getOrder() && it3->getRightSibling()->getOrder() == it3->getOrder())
            {
                it1 = it2;
                it2 = it3;
            }
            else
            {
                if (it2->getValue() <= it3->getValue())
                {
                    auto tmp = it3->getRightSibling();
                    mergeTrees(it2, it3);
                    it2->setRightSibling(tmp);
                }
                else
                {
                    if (it1 == NULL)
                    {
                        res = it3;
                    }
                    else
                    {
                        it1->setRightSibling(it3);
                    }
                    // auto tmp = it2->getRightSibling();
                    mergeTrees(it3, it2);
                    it2 = it3;
                    // it1->setRightSibling(tmp);
                }
            }
            it3 = it2->getRightSibling();
        }

        first = res;
        // print();
    }

    void insert(int val)
    {

        Node<int> *nw = new Node<int>;
        nw->setValue(val);
        BinomialHeap h(nw);
        // cout << h.getFirst()->getValue() << "\n";
        Union(h);
    }

    void insertTree(Node<int> *root)
    {
        BinomialHeap h(root);
        Union(h);
    }

    Node<int> *extractMin()
    {
        if (first == NULL)
        {
            //cout << "\n";
            return NULL;
        }

        Node<int> *toremove = findMin();
        Node<int> *it1 = first;
        Node<int> *prev = NULL;

        while (it1->getValue() != toremove->getValue())
        {
            prev = it1;
            it1 = it1->getRightSibling();
        }

        if (prev == NULL)
            first = toremove->getRightSibling();
        else
            prev->setRightSibling(toremove->getRightSibling());

        BinomialHeap treeheap;
        Node<int> *tmp = toremove->getLeftChild();
        vector<Node<int> *> v;

        while (tmp != NULL)
        {
            v.push_back(tmp);
            tmp = tmp->getRightSibling();
        }
        // cout<<v.size()<<"huh\n";

        for (int i = v.size() - 1; i > 0; i--)
        {
            v[i]->setRightSibling(v[i - 1]);
        }
        if (v.size() > 0)
        {
            v[0]->setRightSibling(NULL);
            //cout << "ahare\n";
            treeheap.setFirst(v[v.size() - 1]);

            Union(treeheap);
        }

        // first=f;

        return toremove;
    }

    void print()
    {
        Node<int> *now = first;
        cout << "Printing Binomial Heap...\n";

        while (now != NULL)
        {
            cout << "Binomial Tree, B" << now->getOrder() << "\n";
            queue<Node<int> *> tr;
            tr.push(now);
            int l = now->getOrder();
            int ct = 0;
            int lvl = 0;
            int range = 1;
            cout << "Level 0 : ";
            while (!tr.empty())
            {
                auto a = tr.front();
                tr.pop();

                if (ct == range)
                {
                    range = (range * (l - lvl)) / (lvl + 1);
                    lvl++;
                    cout << "\nLevel " << lvl << " : ";
                    // cout<<"gdfd\n";
                    ct = 0;
                    // cout<<"gdfd\n";
                }
                ct++;
                cout << a->getValue() << " ";
                // cout<<"rdg "<<range<<" ";
                //  if(a->getRightSibling()!=NULL)
                //      cout<<"child "<<a->getRightSibling()->getValue()<<"\n";

                if (a->getLeftChild() != NULL)
                {
                    Node<int> *sec = a->getLeftChild();
                    while (sec != NULL)
                    {
                        // cout << "ssssss\n";
                        tr.push(sec);
                        sec = sec->getRightSibling();
                    }
                }
            }
            now = now->getRightSibling();
            cout << "\n";
        }
    }
};

int main()
{
    BinomialHeap heap1;
    freopen("in10.txt", "r", stdin);
    freopen("out.txt","w",stdout);
    istringstream stin;
    string s;
    char input;

    cin >> input;

    while (!cin.eof())
    {
        if (input == 'F')
        {
            cout << "Find-Min returned " << heap1.findMin()->getValue() << "\n";
        }
        else if (input == 'E')
        {
            //cout << "hahaha\n";
            cout << "Extract-Min returned " << heap1.extractMin()->getValue() << "\n";
        }
        else if (input == 'P')
        {
            heap1.print();
        }
        else if (input == 'I')
        {
            int num;
            cin >> num;
            heap1.insert(num);
        }
        else if (input == 'U')
        {

            BinomialHeap h2;
            getline(cin, s);
            stin.str(s);
            int num;

            while (stin >> num)
                h2.insert(num);
            heap1.Union(h2);
            stin.clear();
        }
        else
            cout << "invalid\n";
        cin>>input;
    }
}