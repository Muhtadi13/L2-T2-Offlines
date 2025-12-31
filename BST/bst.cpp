#include <bits/stdc++.h>
using namespace std;
#define lli long long int
//#define endl "\n"
#define MOD 1000000007
#define INF 1000000000000000000


class BST
{
    lli* arr;
    int ind;
    lli* traverse_array;
    int cnt;

    int InOrder(lli *arr,lli* trarray,int ind,int trind)
    {
        if(arr[ind]==INF)
        {
            return trind-1;
        }
        cout<<ind<<"HAHA"<<"\n";
        if(2*ind+1>=cnt)
        {
            trarray[trind]=arr[ind];
            return trind;
           
        }
        else
        {
            int nwindex=InOrder(arr,trarray,2*ind+1,trind);
            trarray[nwindex+1]=arr[ind];
            nwindex=InOrder(arr,trarray,2*ind+2,nwindex+2);

            return nwindex;
     
        }     

    }
    void PreOrder(lli *arr,lli* trarray,int ind,int trind)
    {
        if(2*ind+1>=cnt)
        {
            trarray[trind]=arr[ind];
           
        }
        else
        {
            trarray[trind]=arr[ind];
            PreOrder(arr,trarray,2*ind+1,trind+1);   
            PreOrder(arr,trarray,2*ind+2,trind+2);

           
        }     


    }
     void PostOrder(lli *arr,lli* trarray,int ind,int trind)
    {
        if(2*ind+1>=cnt)
        {
            trarray[trind]=arr[ind];         
        }
        else
        {
           
            PostOrder(arr,trarray,2*ind+1,trind);   
            PostOrder(arr,trarray,2*ind+2,trind+1);
             trarray[trind+2]=arr[ind];    
        }     

    }

    public:
    BST(int s=10000)
    {
        arr=new lli[s];
        //traverse_array=new lli[s];
        cnt=0;

        for(int i=0;i<s;i++)
        {
            arr[i]=INF;
            ind=0;

        }
    }
    ~BST()
    {
        delete []arr;
    }

    lli* Insert(lli num)
    {
        if(arr[ind]==num)
        {
            cout<<num<<" Already Exists"<<"\n";
            ind=0;
            
            return arr;
        }
        if(arr[ind]==INF)
        {
            arr[ind]=num;
            ind=0;
            cnt++;
            return arr;
        }

        if(num<arr[ind])
        {
            ind=ind*2+1;
            return Insert(num);

        }

        else
        {
            ind=ind*2+2;
            return Insert(num);
        }
    }

    lli* Delete(lli num)
    {
        if(arr[ind]==num)
        {
            arr[ind]=INF;
            ind=0;
            cnt--;
            return arr;
        }

        else if(arr[ind]==INF)
        {
            cout<<"INVALID"<<"\n";
            ind=0;
            return arr;
        }

        if(num<arr[ind])
        {
            ind=ind*2+1;
            return Delete(num);
        }
        else
        {
            ind=ind*2+2;
            return Delete(num);
        }
    }

    bool Search(lli num)
    {
         if(arr[ind]==num)
        {            
            ind=0;
            return true;
        }

        else if(arr[ind]==INF)
        {         
            return false;
        }

        if(num<arr[ind])
        {
            ind=ind*2+1;
            return Search(num);
        }
        else
        {
            ind=ind*2+2;
            return Search(num);
        }

    }

    lli *Traversal(string s)
    {
        lli* traverse_array=new lli[cnt+1];

        if(s=="1")
        InOrder(arr,traverse_array,0,0);

        if(s=="2")
        PreOrder(arr,traverse_array,0,0);

        if(s=="3")
        PostOrder(arr,traverse_array,0,0);

        return traverse_array;
        
    }


};

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // int t;
    // cin >> t;
    // while (t--)
    // {
        
    // }

    BST bb;
    bb.Insert(8);
    bb.Insert(23);
    bb.Insert(7);
    bb.Insert(2);
    bb.Insert(80);
    bb.Insert(3);
    //bb.Delete(80);

    lli *arr;
    arr=bb.Traversal("1");

    for(int i=0;i<6;i++)
    {
        cout<<arr[i]<<endl;
    }


}