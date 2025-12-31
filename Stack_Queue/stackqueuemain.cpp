#include <bits/stdc++.h>
#include "stackarray.cpp"
#include "stacklinked.cpp"
#include "queuearray.cpp"
#include "queuelinked.cpp"
#define cin fin
#define cout fout

using namespace std;

int main()
{
    ifstream fin("task1input.txt");
    ofstream fout("task1output.txt");

    int K,X;
    cin>>K>>X;
    //Queue_Array<int> myqueue(X);
     Queue_Linked<int> myqueue;
     for(int i=0;i<K;i++)
     {
        int num;
        cin>>num;
        myqueue.enqueue(num);
     }

     int M,Y;

     cin>>M>>Y;
     Stack_Linked<int> mystack;
     //Stack_Array<int> mystack(X);

     for(int i=0;i<M;i++)
     {
        int num;
        cin>>num;
        mystack.push(num);
     }

     int insnum;
     cin>>insnum;

     myqueue.show(fout);
     mystack.show(fout);

     while(insnum--)
     {
        int ins,param;
        cin>>ins>>param;

        switch(ins)
        {
            case 1:
            myqueue.clear();
            myqueue.show(fout);
            cout<<-1<<endl;
            break;

            case 2:
            myqueue.enqueue(param);
            myqueue.show(fout);
            cout<<-1<<endl;
            break;

             case 3:
            int nn;
            nn=myqueue.deque();
            myqueue.show(fout);
            cout<<nn<<endl;
            break;

             case 4:
            myqueue.show(fout);
            cout<<myqueue.length()<<endl;
            break;

             case 5:
            myqueue.show(fout);
            cout<<myqueue.frontValue()<<endl;
            break;

             case 6:
            myqueue.show(fout);
            cout<<myqueue.rearValue()<<endl;
            break;

            case 7:
            int nnn;
            nnn=myqueue.leaveQueue();
            myqueue.show(fout);
            cout<<nnn<<endl;
            break;

             case 8:
            mystack.clear();
            mystack.show(fout);
            cout<<-1<<endl;
            break;

             case 9:
            mystack.push(param);
            mystack.show(fout);
            cout<<-1<<endl;
            break;

             case 10:
            int pp;
            pp=mystack.pop();
            mystack.show(fout);
            cout<<pp<<endl;
            break;

             case 11:
            mystack.show(fout);
            cout<<mystack.length()<<endl;
            break;

             case 12:
             mystack.show(fout);
            cout<<mystack.topValue()<<endl;
            break;





        }

     }





}