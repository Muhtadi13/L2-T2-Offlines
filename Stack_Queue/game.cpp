#include <bits/stdc++.h>
#include "stackarray.cpp"
#include "stacklinked.cpp"
#include "queuearray.cpp"
#include "queuelinked.cpp"

#define cin fin
#define cout fout

class person
{
    public:

    int ind;
    int arrival;
    int duration;
    person(int index=0,int arr=0,int dur=0)
    {
        ind=index;
        arrival=arr;
        duration=dur;
    }
};


using namespace std;
int main()
{

    ifstream fin("task2input.txt");
    ofstream fout("task2output.txt");
   
   
    Queue_Array<int> qucoming(4);
    Queue_Array<int> quduration(4);
    Queue_Array<int> quindex(4);

    // Queue_Linked<int> qucoming;
    // Queue_Linked<int> quduration;
    // Queue_Linked<int> quindex;

    Stack_Array<int> stcoming;
    Stack_Array<int> stduration;
    Stack_Array<int> stindex;
    // Stack_Linked<int> stcoming;
    // Stack_Linked<int> stduration;
    // Stack_Linked<int> stindex;

    int number,timelimit;
    cin>>number>>timelimit;

    int *p=new int[number];
    int last1=0;
    int last2=0;
    int occupied1=0;
    int occupied2=0;


    for(int i=0;i<number;i++)
    {
        
        int arrive,dur;
        cin>>arrive>>dur;

        if(arrive>=last1)
        {
            occupied1=0;
        }


        if(occupied1==0)
        {
            qucoming.enqueue(arrive);
            quduration.enqueue(dur);
            quindex.enqueue(i);

            int c=qucoming.deque();
            int d=quduration.deque();
            int indx=quindex.deque();

            occupied1=1;
            last1=max(c,last1)+d;

            //cout<<indx<<"fir"<<last1<<endl;

            p[indx]=min(last1,timelimit);

        } 
        else if(occupied1==1 && qucoming.length()<3 )
        {  
            qucoming.enqueue(arrive);
            quduration.enqueue(dur);
            quindex.enqueue(i);
        
        }
        else
        {
           if(arrive>last2)
           {
                while(arrive>=last2 && stcoming.length()>0)
                {
                    
                    int come=stcoming.pop();
                    int du=stduration.pop();
                    int indc=stindex.pop();

                    

                    last2=max(last2,come)+du;
                    p[indc]=min(last2,timelimit);

                    // cout<<indc<<" sec"<<last2<<endl;

                }
                if(stcoming.length()>0)
                {
                    stcoming.push(arrive);
                    stduration.push(dur);
                    stindex.push(i);
                }
                else
                {
                    
                    
                    last2=max(last2,arrive)+dur;
                    p[i]=min(last2,timelimit);

                    // cout<<i<<" thi"<<last2<<endl;
                }

           }
           else if(arrive==last2)
           {
                last2+=dur;
                p[i]=min(last2,timelimit);

                 //cout<<i<<" for"<<last2<<endl;

           }
            else{
                stcoming.push(arrive);
                stduration.push(dur);
                stindex.push(i);
            } 

        }

       
    }

    while(quduration.length()>0)
    {
        last1=max(last1,qucoming.deque())+quduration.deque();
        //int i=quindex.deque();
        
        p[quindex.deque()]=min(last1,timelimit);
         // cout<<i<<" fiv"<<last1<<endl;

        
    }
    while(stduration.length()>0)
    {
        last2=max(last2,stcoming.pop())+stduration.pop();
        //int i=stindex.pop();
        p[stindex.pop()]=min(last2,timelimit);
         // cout<<i<<" six"<<last2<<endl;
    }
    for(int j=0;j<number;j++)
    {
        cout<<j+1<<" > "<<p[j]<<endl;
    }

    
}