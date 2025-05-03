#include <bits/stdc++.h>
#define cout fout

using namespace std;

template <class T>
class QNode
{
    T value;
    QNode *next;

public:
    void setValue(T v)
    {
        value = v;
    }

    T getValue()
    {
        return value;
    }

    void setNext(QNode *x)
    {
        next = x;
    }
    QNode *getNext()
    {
        return next;
    }
};

template <class T>
class Queue_Linked
{
    QNode<T> *front, *rear;
    int len=0;

    public:
    Queue_Linked()
    {
        front = NULL;
        rear = NULL;
    }

    void enqueue(T x)
    {
        QNode<T> *temp = new QNode<T>;
        temp->setValue(x);

        if (rear == NULL)
        {
            front = rear = temp;
            rear->setNext(NULL);
            len++;
            return;
        }
        rear->setNext(temp);
        rear = temp;
        rear->setNext(NULL);
        len++;
    }

    T deque()
    {
       
        if (front == NULL)
            return -1;

        
        QNode<T> *temp = front;
        T val=front->getValue();
        front = front->getNext();

        if (front == NULL)
            rear = NULL;
        
        len--;

        delete temp;
        return val;
    }

    int length()
    {
        return len;
    }

    T frontValue()
    {
        if(front)
        return front->getValue();

        return -1;

    }

    T rearValue()
    {
        if(rear)
        return rear->getValue();

        return -1;

    }

    T leaveQueue()
    {
        if (rear == NULL)
            return -1;

        if(len==1)
        {
            T val=rear->getValue();
            front=rear=NULL;
            len--;
            return val;
        }
        else
        {      
            QNode<T> *temp = front;
            QNode<T> *prev = front;

            for(int i=1;i<=len;i++)
            {

                if(i==len)
                {
                    T val = rear->getValue();
               
                    rear=prev;
                    rear->setNext(NULL);


                    len--;
                    free(temp);
                    return val;


                }

                else{
                    prev=temp;
                    temp=temp->getNext();
                }

            }
        }

    }

    void clear()
    {
        QNode<T> *temp = new QNode<T>;
        while (front != NULL)
        {
            temp=front;
            front = front->getNext();
            free(temp);
        }
      
        front=rear=NULL;
        len = 0;

    }
    void show(ofstream &fout)
    {

        cout << "< ";
        
        if(len>0)
        {
            cout<<"| ";
            QNode<T> *tmp = front;

            for (int i = 0; i < len; i++)
            {
                cout << tmp->getValue() << " ";
                tmp = tmp->getNext();
            }
        }
            
        cout << ">" << endl;
    }




};