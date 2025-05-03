#include <bits/stdc++.h>
using namespace std;

template <class T>
class Node
{
    T value;
    Node *next;

public:
    void setValue(T v)
    {
        value = v;
    }

    T getValue()
    {
        return value;
    }

    void setNext(Node *x)
    {
        next = x;
    }
    Node *getNext()
    {
        return next;
    }
};

template <class T>
class MyList_Linked
{
    // T value;

    Node<T> *head;
    Node<T> *tail;
    Node<T> *curr;

    int len;
    int cur_pos;

public:
   

    MyList_Linked()
    {
        len = 0;
        cur_pos = 0;
        head = NULL;
        tail = NULL;
        curr = NULL;
    }

    ~MyList_Linked()
    {

        delete head;
        delete tail;
        delete curr;
    }
    Node<int> *getHead()
    {
        return head;
    }

    int size()
    {
        return len;
    }

    int setToPos(int x)
    {
        if (x < len && x > -1)
        {
            curr = head;
            int count = 0;
            while (curr != NULL)
            {
                if (count == x)
                {
                    cur_pos = count;
                    // cout<<cur_pos<<endl;
                    // cout<<len<<"lll"<<endl;
                    return cur_pos;
                }
                count++;
                curr = curr->getNext();
            }
        }
    }

    void push(T item)
    {
        if (head == NULL)
        {
            head = new Node<T>;
            head->setValue(item);
            tail = head;
            curr = head;
            tail->setNext(NULL);
            cur_pos = 0;
            len++;
            // cout<<"hahaha"<<endl;
        }
        else if (head && cur_pos == 0)
        {
            Node<T> *nd = new Node<T>;
            nd->setValue(item);
            nd->setNext(head);
            // cout<<nd->getValue()<<" nodeval"<<endl;
            // cout<<nd->getNext()->getValue()<<" nodenextval"<<endl;

            head = nd;
            curr = nd;
            cur_pos = 0;
            // cout<<head->getNext()->getValue()<<" headval"<<endl;
            // cout<<curr->getValue()<<" currval"<<endl;
            len++;
            // cout<<"LOL"<<endl;
        }
        else
        {
            Node<T> *node = new Node<T>;

            int ind = setToPos(cur_pos - 1);

            node->setValue(item);
            node->setNext(curr->getNext());
            curr->setNext(node);
            curr = node;
            cur_pos++;
            len++;
        }
    }

    void pushBack(T item)
    {
        if (head == NULL)
        {
            head = new Node<T>;
            head->setValue(item);
            tail = head;
            curr = head;
            tail->setNext(NULL);
            cur_pos = 0;
            len++;
        }
        else
        {
            Node<T> *node = new Node<T>;
            node->setValue(item);
            tail->setNext(node);
            tail = node;
            tail->setNext(NULL);
            len++;
        }
    }

    T erase()
    {
        if (head)
        {
            Node<T> *temp = new Node<T>;
            Node<T> *prev = new Node<T>;
            temp = head;
            prev = head;
            if (cur_pos == 0)
            {
                T val = temp->getValue();
                len--;

                if (len > 0)
                {
                    head = head->getNext();
                }
                else
                {
                    head = NULL;
                    tail = NULL;
                }

                curr = head;
                free(temp);
                return val;
            }
            else
            {
                for (int i = 0; i <= cur_pos; i++)
                {

                    if (i == cur_pos && temp)
                    {
                        T val = curr->getValue();
                        prev->setNext(temp->getNext());
                        curr = temp->getNext();

                        if (cur_pos == len - 1 && len > 1)
                            int x = setToPos(cur_pos - 1);

                        len--;
                        free(temp);
                        return val;
                    }
                    else
                    {
                        prev = temp;
                        if (prev == NULL)
                            break;
                        temp = temp->getNext();
                    }
                }
            }
        }
        return "";
    }

    void setToBegin()
    {
        cur_pos = 0;
        curr = head;
    }

    void setToEnd()
    {
        curr = tail;
        cur_pos = len - 1;
    }

    void prev()
    {
        if (cur_pos > 0)
            int x = setToPos(cur_pos - 1);
    }

    void next()
    {
        if (cur_pos < len - 1)
            int x = setToPos(cur_pos + 1);
    }

    int currPos()
    {
        return cur_pos;
    }

    T getValue()
    {
        return curr->getValue();
    }

    int find(T x)
    {
        int count = 0;
        Node<T> *temp = head;

        while (temp != NULL)
        {
            if (temp->getValue() == x)
                return count;
            count++;
            temp = temp->getNext();
        }
        return -1;
    }

    void clear()
    {

        while (head != NULL)
        {
            curr = head;
            head = head->getNext();
            free(curr);
        }

        curr = NULL;
        head = NULL;
        tail = NULL;

        len = 0;
        cur_pos = 0;
    }
    void print(ofstream &out)
    {

        // cout<<p<<endl;

        out << "<";
        // cout<<-3<<endl;
        if (len > 0)
        {
            Node<T> *tmp = head;

            for (int i = 0; i < cur_pos; i++)
            {
                out << tmp->getValue() << " ";
                tmp = tmp->getNext();
            }
            out << "|"
                << " ";
            for (int i = cur_pos; i < len; i++)
            {
                out << tmp->getValue() << " ";
                tmp = tmp->getNext();
            }
            // if(p<marray.size())
            //  out<<tmp->getValue();
        }

        out << ">" << endl;
    }
};