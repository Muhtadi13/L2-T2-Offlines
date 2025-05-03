#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 505LL
#define MOD 1000000007
#define cin in

using namespace std;

vector<pair<int,pair<int,int> > > adj;
vector<lli> parent(MAX);
vector<lli> _rank(MAX);
lli find_root(lli node)
{
    if(parent[node]==node)
    return node;

    lli root=find_root(parent[node]);

    parent[node]=root;
    return root;

}

void set_union(lli node1,lli node2)
{
    lli ancs1=find_root(node1);
    lli ancs2=find_root(node2);

    if(ancs1==ancs2)
    return;

    if(_rank[ancs1]>_rank[ancs2])
    {
        parent[ancs2]=ancs1;

    }
    else if(_rank[ancs1]<_rank[ancs2])
    {
        parent[ancs1]=ancs2;
    }
    else
    {
        _rank[ancs1]++;
        parent[ancs2]=ancs1;
    }

}

void initialize(lli n)
{
    for(int i=0;i<=n;i++)
    {
        parent[i]=i;
        _rank[i]=0;
    }
}

bool comp(pair<int,pair<int,int>>t1, pair<int,pair<int,int> > t2)
{
    return t1.second.second<t2.second.second;
}

int main()
{
    ifstream in("in.txt");
   
    lli n,m;
    cin>>n>>m;

     initialize(n);

    for(int i=0;i<m;i++)
    {
        int x,y ,z;
        cin>>x>>y>>z;

        adj.push_back({x,{y,z}});

    }
    sort(adj.begin(),adj.end(),comp);

    vector<pair<int,pair<int,int> > > ans;
    lli sum=0;

    for(int i=0;i<adj.size();i++)
    {
        lli a=find_root(adj[i].first);
        lli b=find_root(adj[i].second.first);

    

        if(a!=b)
        {
            //cout<<adj[i].first<<" "<<adj[i].second.first<<" "<<a<<" "<<b<<" ";
             
            ans.push_back(adj[i]);
            sum+=adj[i].second.second;
            set_union(adj[i].first,adj[i].second.first);
            //cout<<parent[a]<<" "<<parent[b]<<"\n";
           
            
        }
        
    }

    cout<<"Kruskal's Algorithm:\n";
    cout<<"Total weight = "<<sum<<"\n";

    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i].first<<" "<<ans[i].second.first<<"\n";
    }

    






    

}