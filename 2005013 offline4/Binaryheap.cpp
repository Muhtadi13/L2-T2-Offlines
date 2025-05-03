
#include<bits/stdc++.h>
using namespace std;
#define INF 1000000009
//#define cout out





template<class T>
class Myheap
{
    T *nums;
    int length;
    int maxsize;

    void swapElements(T& a,T& b)
    {
        T tmp;
        tmp=b;
        b=a;
        a=tmp;
    }

    int searchKey(T key)
    {
        int no=-1;
        for(int j=1;j<=length;j++)
        {
            if(nums[j]==key)
            {
                return j;
            }
        }
        return no;
    }

    int findSmaller(int ind1,int ind2)
    {
        if(nums[ind1]>nums[ind2])
        {
            return ind2;

        }
        return ind1;
    }
    void grow()
    {

        T *tmp = new T[maxsize*2 + 1];

        for (int i = 0; i <= maxsize; i++)
        {
            tmp[i] = nums[i];
        }
        delete[] nums;

        nums = tmp;
        maxsize = maxsize * 2;
    }

    void shrink()
    {
        if(maxsize<=5)
        return;


        //cout<<length<<"shri\n";

       
        maxsize /= 2;

        // cout<<maxsize<<" size"<<endl;

        T *tmp = new T[maxsize+1];

        for (int i = 0; i <= length; i++)
        {
            tmp[i] = nums[i];
        }
        delete[] nums;
        nums = tmp;
    }

    public:
    Myheap(int init_sz=500)
    {
        nums=new T[init_sz+1];
        for(int j=0;j<=init_sz;j++)
        {
            nums[j]=INF;
        }
        length=0;
        maxsize=init_sz;


    }
    ~Myheap()
    {
        delete[] nums;
    }

    void Insert(T num)
    {
        if(length==maxsize)
        {
            grow();
        }

        nums[++length]=num;
        int i=length;

        while((i/2)>0 && nums[i/2]>nums[i])
        {
            swapElements(nums[i/2],nums[i]);
            i/=2;
        }
        cout<<"INSERTED "<<num<<"\n";
    }

    void DecreaseKey(T oldkey,T newkey)
    {
        int ind=searchKey(oldkey);

        if(ind==-1)
        {
            cout<<"number not found\n";
            

        }
        else
        {
            nums[ind]=newkey;
            while((ind/2>0) && nums[ind/2]>nums[ind])
            {
                swapElements(nums[ind/2],nums[ind]);
                ind/=2;
            }

            cout<<oldkey<<" decreased to "<<newkey<<"\n";


        }


    }
    T ExtractMin()
    {
        if(length==0)
        {
            cout<<"Empty Heap\n";
            return -INF;
        }
       

        T ans=nums[1];
        swapElements(nums[length],nums[1]);
        nums[length]=INF;
        length--;
        
        int i=1;
        while(2*i<=length)
        {
            if((2*i)==length && nums[2*i]<nums[i])
            {
                swapElements(nums[i],nums[2*i]);
                i*=2;
                break;

            }
            else if((2*i)<length && !(nums[2*i]>nums[i] && nums[2*i+1]>nums[i]))
            {
                int ind=findSmaller(2*i,2*i+1);

                swapElements(nums[ind],nums[i]);
                i=ind;

            }
            else
            break;
        }

        if(length==maxsize/2)
        {
            shrink();
        }

        cout<<"ExtractMin returned ";
        return ans;
        
    }

    T FindMin()
    {
         if(length==0)
        {
            cout<<"Empty Heap\n";
            return -INF;
        }
        cout<<"FindMin returned ";
        return nums[1];
    }

    void Print()
    {
        cout<<"Printing the binary heap...\n- - - - - - - - - - - - - - - - - - - -";
        int level=0;
        int tr=1;
        for(int i=1;i<=length;i++)
        {
            if(i==tr)
            {
                cout<<"\nlevel "<<level<<": ";
                tr*=2;
                level++;
                
            }
            cout<<nums[i]<<" ";

        }
        cout<<"\n- - - - - - - - - - - - - - - - - - - -\n";

    }



};

int main()
{
    ifstream in("input.txt");

    ofstream out("output.txt");
    streambuf *obuf=cout.rdbuf();

    cout.rdbuf(out.rdbuf());
   
    if (!in)
    {
        cout<<"Cannot open file";
        return -1;
    }
        /*
        INS 7
        INS 10
        INS 5
        PRI
        INS 12
        INS 15
        PRI
        DEC 15 3
        PRI
        FIN
        EXT
        PRI*/

    string com;
    Myheap<int> mhp;
   

    while (!in.eof())
    {
        in >> com;

       if(com=="INS")
       {
        int num;
        in>>num;
        mhp.Insert(num);
        

       }
       else if(com=="DEC")
       {
        int old,nw;
        in>>old>>nw;
        mhp.DecreaseKey(old,nw);
       }

       else if(com=="FIN")
       {
        int x=mhp.FindMin();
        if(x!=-INF)
        cout<<x<<"\n";
       }
       else if(com=="EXT")
       {
            int x=mhp.ExtractMin();
            if(x!=-INF)
            cout<<x<<"\n";
       }

       else if(com=="PRI")
       {
            mhp.Print();
       }
       else
       {
            cout<<"INVALID INPUT\n";
            break;
       }
    }
    
    cout.rdbuf(obuf);
    in.close();
    out.close();




}
