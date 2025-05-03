#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli,lli>
using namespace std;
#define cin in
#define cout out


vector<plli> pairs; 



lli merge(vector<lli> &p,lli left,lli mid,lli right)
{
    lli res=0;


    //lli ind=left.size()+right.size();
    vector<lli> sorted(p.size());

    lli lind=left;
    lli rind=mid+1;
    lli tmpind=left;
    while(lind<=mid && rind<=right)
    {
        
        if(p[lind]>p[rind])
        {
            res+=(mid-lind+1); 
            //cout<<res<<"haha"<<lind<<rind<<"\n";
            for(lli j=lind;j<=mid;j++)
            {
                pairs.push_back({p[j],p[rind]});

            } 
            
            sorted[tmpind]=p[rind];      
            rind++;
            tmpind++;
        }   
        else
        {
            sorted[tmpind]=p[lind];      
            lind++;
            tmpind++;

        }

    }
    while(lind<=mid)
    {
        
        sorted[tmpind]=p[lind];      
        lind++;
        tmpind++;
        

    }
    while(rind<=right)
    {
       
        sorted[tmpind]=p[rind];      
        rind++;
        tmpind++;
        
    }

    for(lli j=left;j<=right;j++)
    {
        p[j]=sorted[j];

    }

    //cout<<res<<" "<<left<<" "<<right<<"\n";

    return res;


}


lli mergeSort(vector<lli> &p,lli first,lli last)
{
    if(first==last)
    {
        return 0;

    }

    lli mid=(first+last)/2;

    lli leftc=mergeSort(p,first,mid);

    lli rightc=mergeSort(p,mid+1,last);

    lli res=0;
    
    res=leftc+rightc+merge(p,first,mid,last);

    return res;
   

}



int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    lli n;
    cin>>n;

    vector<lli> nums;
    

    for(lli j=0;j<n;j++)
    {
        lli x;

        cin>>x;

        nums.push_back(x);

    }
    

    cout<<mergeSort(nums,0,n-1)<<"\n";
    cout<<"The inverted pairs are\n";

    for(lli j=0;j<pairs.size();j++)
    {
        cout<<"("<<pairs[j].first<<","<<pairs[j].second<<")\n";
    }

}