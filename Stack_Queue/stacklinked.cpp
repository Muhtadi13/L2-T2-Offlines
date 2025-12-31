#include <bits/stdc++.h>
#define cout fout

using namespace std;

template <class T>
class SNode
{
    T value;
    SNode *down;

public:
    void setValue(T v)
    {
        value = v;
    }

    T getValue()
    {
        return value;
    }

    void setDown(SNode *x)
    {
        down = x;
    }
    SNode *getDown()
    {
        return down;
    }
};


template <class T>
class Stack_Linked
{
    SNode<T>* head;
    int len;



public:
    Stack_Linked()
    {
        
        head=NULL;
        len=0;
    }


    void push(T item)
    {
        if(head==NULL)
        {
            head=new SNode<T>;
            head->setValue(item);
            head->setDown(NULL);
            len++;     
        }
        else{
            
            SNode<T> *nd=new SNode<T>;
            nd->setValue(item);
            nd->setDown(head);
            head=nd;
            len++;
        }
        
         
    }

    T pop()
    {
       
        if(len>0)
        {
           SNode<T>* temp=new SNode<T>;
           temp=head;
           head=head->getDown();
           len--;
           T val=temp->getValue();
           free(temp);
           return val;

        }

    }

    int length()
    {
        return len;
    }

    T topValue()
    {
        
        if(len>0)
        {
            return head->getValue();

        }

    }

    


    void clear()
    {
        SNode<T>* curr=new SNode<T>;
        

         while (head != NULL)
        {
            curr = head;
            head = head->getDown();
            free(curr);
        }
        len=0;
        head=NULL;

        
    }

    void show(ofstream &fout)
    {

        cout << "< ";
        
        if(len>0)
        {
            T *q=new T[len];
            SNode<T> *tmp = head;

            for (int i = 0; i < len; i++)
            {
                //cout << tmp->getValue() << " ";
                q[i] = tmp->getValue();
                tmp = tmp->getDown();
            }
             for (int i = len-1; i>=0 ; i--)
            {
                if(i==0)
                cout<<"| ";
                //cout << tmp->getValue() << " ";
                cout<<q[i]<<" ";
                
               
            }
        }
            
        cout << ">" << endl;
    }
};

