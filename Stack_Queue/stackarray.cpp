#include <bits/stdc++.h>
#define cout fout
using namespace std;

template <class T>
class Stack_Array
{
    int tos;
    int max_size;
    T *arr;

    void grow()
    {

        T *tmp = new T[max_size * 2];

        for (int i = 0; i < max_size; i++)
        {
            tmp[i] = arr[i];
        }
        delete[] arr;

        arr = tmp;
        max_size = max_size * 2;
    }

    void shrink()
    {
        if (max_size > 1)
            max_size /= 2;

        T *tmp = new T[max_size];

        for (int i = 0; i < tos; i++)
        {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
    }



public:
    Stack_Array(int sz = 100)
    {
        
        tos = 0;
        max_size = sz;
        arr = new T[max_size];
    }


    void push(T item)
    {
        if (tos == max_size)
        {
            grow();
        }
        arr[tos] = item;
        tos++;
    }

    T pop()
    {
        if(tos==max_size/2 && tos>2)
        {
            shrink();
        }
        if(tos>0)
        {
            T el=arr[tos-1];
            tos--;
            return el;

        }

    }

    int length()
    {
        return tos;
    }

    T topValue()
    {
        
        if(tos>0)
        {
            T el=arr[tos-1];
            return el;

        }

    }

    


     void clear()
    {

        max_size = 3;
        tos = 0;
       
        delete[] arr;
        arr = new T[max_size];
        
    }
     void show(ofstream &fout)
    {
        cout<<"< ";
        for(int i=0;i<tos;i++)
        {
            if(i==tos-1)
            cout<<"| "<<arr[i]<<" ";
            
            else
            cout<<arr[i]<<" ";

        }
        cout<<">"<<endl;
    }
};

