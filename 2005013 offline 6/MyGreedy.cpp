#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli,lli>

#define cin in
#define cout out

using namespace std;

bool comp(pair<lli,lli> p1,pair<lli,lli> p2)
{
    if(p2.second==p1.second)
        return p2.first>p1.first;
    return p2.second>p1.second;
}

vector<plli> merge(vector<plli> left,vector<plli> right)
{
    vector<plli> res;


    //lli ind=left.size()+right.size();

    lli lind=0;
    lli rind=0;
    while(lind<left.size() && rind<right.size())
    {
        if(left[lind].second==right[rind].second)
        {
            if(left[lind].first<right[rind].first)
            {
                res.push_back(left[lind]);
                lind++;
            }

            else
            {

                res.push_back(right[rind]);
                rind++;
            }
        }

        else if(left[lind].second<right[rind].second)
        {
            res.push_back(left[lind]);
            lind++;
        }

        

        else
        {
            res.push_back(right[rind]);
            rind++;

        }

    }
    while(lind<left.size())
    {
        
        res.push_back(left[lind]);
        lind++;
        

    }
    while(rind<right.size())
    {
       
        res.push_back(right[rind]);
        rind++;
        

    }

    return res;


}


vector<plli> mergeSort(vector<pair<lli,lli> > p,lli first,lli last)
{
    if(first==last)
    {
        
         vector<plli> res;
         res.push_back(p[first]);

         return res;

    }

    lli mid=(first+last)/2;

    vector<plli> left;
    left=mergeSort(p,first,mid);

    vector<plli> right;
    right=mergeSort(p,mid+1,last);

    vector<plli> res;
    res=merge(left,right);

    return res;
   

}



int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    lli n;
    cin>>n;

    vector<pair<lli,lli>> timestamp;

    for(lli j=0;j<n;j++)
    {
        lli x,y;

        cin>>x>>y;

        timestamp.push_back({x,y});

    }
    //sort(timestamp.begin(),timestamp.end(),comp);

    timestamp=mergeSort(timestamp,0,n-1);


    lli last=0;
    vector<pair<int,int>> ans;

    for(lli j=0;j<n;j++)
    {
        if(timestamp[j].first>=last)
        {
            last=timestamp[j].second;
            ans.push_back(timestamp[j]);
        }
    }

    cout<<ans.size()<<"\n";

    for(lli j=0;j<ans.size();j++)
    {
        cout<<ans[j].first<<" "<<ans[j].second<<"\n";
    }
}

/*
#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 1003LL
#define MOD 1000000007

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        lli n, p;
        cin >> n >> p;

        vector<lli> num(n);
        vector<lli> num2(n);
        vector<lli> num3(n);

        set<lli> kekease;
        

        for (lli j = 0; j < n; j++)
        {
            cin >> num[j];
            num3[j]=num2[j]=num[j];

            kekease.insert(num[j]);
        }

        lli huh=num[n-1];
        lli cnt1 = 0;

        for (lli j = 0; j < n; j++)
        {
           if (num[j] != -1)
            {
                lli nw = (num[n - 1] - j + p) % p;

                for(lli h=0;h<n;h++)
                {
                    if(num[h]==nw)
                    {
                        num[h]=-1;
                    }
                }

                if (kekease.find(nw) != kekease.end())
                {
                    cnt1++;
                    
                }
                else
                    break;
            }
        }

        if (huh != 0)
        {
            lli i = n - 2;

            if (i >= 0)
                kekease.insert((num3[i] + 1 + p) % p);

            //cout << (num3[i] + 1 + p) % p;

            while (i >= 0 && num3[i] == (p - 1))
                i--;

            lli a = 0;

            if (i >= 0)
            {
                a = num3[i];
            }

            kekease.insert((a + 1 + p) % p);
        }

        lli cnt2 = 0;
        lli last = (num3[n - 1] - 1 + p) % p;

        for (lli j = 0; j < n; j++)
        {
            if (num2[j] != -1)
            {
                lli nw = (num2[n - 1] - j + p) % p;

                cout<<nw<<"werrr\n";

                for(lli h=0;h<n;h++)
                {
                    if(num2[h]==nw)
                    {
                        num2[h]=-1;
                    }
                }

                if (kekease.find(nw) != kekease.end())
                {
                    cnt2++;
                    last = nw;
                }
                else
                    break;
            }
        }
        //cout << cnt1 << "sghfd";

        if (cnt1 < cnt2)
        {
            if (last == 0)
            {
                cnt2--;
            }
        }

        cout << p - cnt2 << "\n";
    }
}*/