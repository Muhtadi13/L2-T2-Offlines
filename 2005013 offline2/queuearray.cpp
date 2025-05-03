#include <bits/stdc++.h>
#define cout fout

using namespace std;

template <class T>
class Queue_Array
{
    int front;
    int rear;
    int len;
    int max_size;
    T *arr;

    void grow()
    {

        T *tmp = new T[max_size * 2];
        int front_temp=front;
        int i=0;

        //cout<<"gsgs"<<endl;

       while(true)
       {
            tmp[i++]=arr[front_temp++];

            if(front_temp==max_size)
            front_temp=0;

            if(i == len){
                break;
            }
            

       }
        delete[] arr;

        arr = tmp;
        front=0;
        rear=len;
        max_size = max_size * 2;
    }

    void shrink()
    {
        
        T *tmp = new T[max_size /2];
        int front_temp=front;
        int i=0;
        //cout<<"MUHAHA"<<endl;

       while(true)
       {
            tmp[i++]=arr[front_temp++];

            if(front_temp==max_size)
            front_temp=0;

             if(i == len){
                break;
            }
            

       }
        delete[] arr;

        arr = tmp;
        front=0;
        rear=len;
        max_size = max_size / 2;
    }



public:
    Queue_Array(int sz = 10)
    {
        
        front=0;
        rear=0;
        len=0;
        max_size = sz;
        arr = new T[max_size];
    }

    void enqueue(T data)
    {
        //cout<<"enq"<<endl;
        if (len == max_size) {
           grow();
            
        }

        len++;

        arr[rear] = data;
        rear++;

        if(rear == max_size)
        {
            rear=0;

        }      
        
    }

    T deque()
    {
        if (len==0)
        {
            return -1;
        }

        else
        {
            T dt=arr[front];

            front++;
            len--;

            if(front>=max_size)
            front=0;

            // cout<<front<<"fft"<<endl;
            // cout<<rear<<"rer"<<endl;

            if((len==max_size/2) && (len>=6))            
            {
                //cout<<len<<"lll"<<endl;
                shrink();
            }  

            return dt;       
         
        }
 
       
    }

    void clear()
    {
         max_size = 10;
        len = 0;
        front=0;
        rear=0;

       
        delete[] arr;
        arr = new T[max_size];
    }

    int length()
    {
        return len;
    }
    
    T frontValue()
    {
        return arr[front];
    }
    T rearValue()
    {
        if(rear==0)
        {
            return arr[max_size-1];
        }
        else
        return arr[rear-1];
    }

    T leaveQueue()
    {
         if (len==0) {
            return -1;
        }

        else
        {
            if(rear==0)
            rear=max_size;
            
            rear--;
            len--;


            if(len==max_size/2 && len>=6)
            {
                shrink();
            } 

            return arr[rear];        
         
        }
    }

    void show(ofstream &fout)
    {
        cout<<"< ";
        int cnt=0;
        int i=front;
       
        while(cnt<len)
        {
            if(i==front)
            {
                cout<<"| ";
            }
            cout<<arr[i]<<" ";

            i=(i+1)%max_size;
            cnt++;

        }
        cout<<">"<<endl;
    }



};
