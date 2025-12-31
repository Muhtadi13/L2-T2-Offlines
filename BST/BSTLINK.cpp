#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define endl "\n"
#define MOD 1000000007
#define cout out

template <class T>
class Node
{
    T value;
    Node *right;
    Node *left;

public:
    void setValue(T v)
    {
        value = v;
    }

    T getValue()
    {
        return value;
    }

    void setRight(Node *x)
    {
        right = x;
    }
    Node *getRight()
    {
        return right;
    }
    void setLeft(Node *x)
    {
        left = x;
    }
    Node *getLeft()
    {
        return left;
    }
};

class BST
{

    int cnt;
    Node<int> *root;
    int trind;
    // ofstream out;

    void InOrder(Node<int> *root, ofstream &out)
    {
        if (root->getLeft())
            InOrder(root->getLeft(), out);

        cout << root->getValue() << " ";

        if (root->getRight())
            InOrder(root->getRight(), out);
    }
    void PreOrder(Node<int> *root, ofstream &out)
    {

        cout << root->getValue() << " ";

        if (root->getLeft())
            PreOrder(root->getLeft(), out);

        if (root->getRight())
            PreOrder(root->getRight(), out);
    }
    void PostOrder(Node<int> *root, ofstream &out)
    {

        if (root->getLeft())
            PostOrder(root->getLeft(), out);

        if (root->getRight())
            PostOrder(root->getRight(), out);

        cout << root->getValue() << " ";
    }

 void clear(Node<int> *root)
    {

        if (root->getLeft())
            clear(root->getLeft());

        if (root->getRight())
            clear(root->getRight());

        delete root;
    }

public:
    BST()
    {

        root = NULL;
        //trind = 0;
        cnt = 0;
        // out.open("output.txt");
    }
    ~BST()
    {
        clear(root);
        // out.close();
    }

    void Insert(int num, ofstream &out)
    {
        // cout<<"HAHA"<<endl;
        if (root == NULL)
        {
            // cout<<"qwerty"<<endl;
            root = new Node<int>;
            root->setValue(num);
            root->setLeft(NULL);
            root->setRight(NULL);
            cnt++;
            print(root, out);
            cout << endl;
            return;
        }

        Node<int> *nwnode = new Node<int>;
        nwnode->setValue(num);
        nwnode->setLeft(NULL);
        nwnode->setRight(NULL);

        Node<int> *par = new Node<int>;
        Node<int> *tmp = new Node<int>;

        par = root;
        tmp = root;

        while (tmp != NULL)
        {
            // cout<<tmp->getValue()<<" "<<num<<endl;
            if (tmp->getValue() < num)
            {
                par = tmp;
                tmp = tmp->getRight();
            }
            else if (tmp->getValue() > num)
            {
                par = tmp;
                tmp = tmp->getLeft();
            }
            // else
            // cout<<"ONONO"<<endl;
        }

        if (par->getValue() < num)
        {
            // cout<<"DUNNO"<<endl;
            par->setRight(nwnode);
        }
        else if (par->getValue() > num)
        {
            // cout<<"DUNNOsdfg"<<endl;
            par->setLeft(nwnode);
        }
        // else
        // cout<<"DUNNO"<<endl;
        cnt++;

        print(root, out);
        cout << "\n";
    }

    void Delete(int num, ofstream &out)
    {
        if (root == NULL)
        {
            cout << "Tree is Empty" << endl;
            return;
        }

        Node<int> *par = root;
        Node<int> *tmp = root;

        while (tmp != NULL)
        {
            if (tmp->getValue() < num)
            {
                par = tmp;
                tmp = tmp->getRight();
            }
            else if (tmp->getValue() > num)
            {
                par = tmp;
                tmp = tmp->getLeft();
            }
            else
            {
                if (tmp->getLeft() == NULL && tmp->getRight() == NULL)
                {
                    if (par->getLeft() == tmp)
                        par->setLeft(NULL);

                    else
                        par->setRight(NULL);

                    free(tmp);
                    cnt--;
                    if (root != tmp) // root is not NULL yet
                    {
                        print(root, out);
                        cout << "\n";
                    }

                    else
                    {
                        root = NULL;
                        cout << "Tree is Empty"<< "\n";
                    }
                    return;
                }
                else
                {
                    cout << "Invalid Operation"<< "\n";
                    return;
                }

                break;
            }
        }

        if (tmp == NULL)
        {
            cout << "Number doesn't exist" << "\n";
            return;
        }
        cnt--;
        if (root)
        {
            print(root, out);
            cout << "\n";
        }

        else
            cout << "Tree is Empty"<< "\n";
    }

    bool Find(int num)
    {
        if (root == NULL)
        {
            return false;
        }
        Node<int> *tmp = root;

        while (tmp != NULL)
        {
            if (tmp->getValue() < num)
            {
                tmp = tmp->getRight();
            }
            else if (tmp->getValue() > num)
            {
                tmp = tmp->getLeft();
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void Traversal(string s, ofstream &out)
    {
        // int* traverse_array=new int[cnt+1];

        if (root == NULL)
        {
            cout << "Tree is Empty"<< "\n";
            return;
        }

        if (s == "In")
            InOrder(root, out);

        if (s == "Pre")
            PreOrder(root, out);

        if (s == "Post")
            PostOrder(root, out);

        cout << "\n";

        // return traverse_array;
    }

    void print(Node<int> *root, ofstream &out)
    {

        if (root)
        {
            cout << root->getValue();

            if (root->getLeft() || root->getRight())
            {
                cout << "(";

                print(root->getLeft(), out);
                cout << ")";
                cout << "(";
                print(root->getRight(), out);
                cout << ")";
            }
        }
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    if (!in)
    {
        cout << "Cannot open file" << endl;
        return -1;
    }

    BST bb;

    char com1;
    int com2;
    string com3;

    while (!in.eof())
    {
        in >> com1;

        switch (com1)
        {
        case 'I':
            in >> com2;
            bb.Insert(com2, out);
            break;
        case 'D':
            in >> com2;
            bb.Delete(com2, out);
            break;
        case 'F':
            in >> com2;
            cout << boolalpha << bb.Find(com2) << endl;
            break;
        case 'T':
            in >> com3;
            bb.Traversal(com3, out);
            break;

        default:
            cout<<"Wrong Input"<<"\n";
            break;
        }
    }
}