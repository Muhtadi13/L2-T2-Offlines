#include <bits/stdc++.h>
using namespace std;
#define lli int
#define INF 1000000009
#define MAX 200005
#define cin in
#define cout out

vector<int> vis(200005,0);
//vector<int> processed(MAX,0);

// int ans;

void dfs(int par, int root, vector<int> *nodes,vector<int> *list)
{

    // int h=1;
    vis[par]=1;
    //cout<<par<<"->";
    

    for (auto child : nodes[par])
    {
        if(child!=par)
        {
            if(vis[child]==0)
            {
                list[par].push_back(child);
                //cout<<par<<" "<<child<<"\n";
                //cout<<child<<" ";
                dfs(child, par, nodes,list);

            }
            
        }
    }
    // cout<<"\n";
    // processed[par]=1;
    
}

int main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

    ifstream in("input.txt");
    ofstream out("output.txt");
    
    int n, e;
    cin >> n >> e;
    int root;

    vector<int> adj[n + 1];
    vector<int> nodes[n+1];

    for (int i = 0; i < e; i++)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        //adj[y].push_back(x);
    }

    queue<int> pq;
    
    // for (int i = 1; i <= n; i++)
    // {
    int i;
    cin>>i;
    // if (vis[i] == 0)
    // {

    pq.push(i);

    while (!pq.empty())
    {
        int a = pq.front();
        pq.pop();

        // if (vis[a])
        //     continue;

        vis[a] = 1;
        
        //processed[a]=1;


        for (auto u : adj[a])
        {
            int b = u;
            if(b!=a)
            {

                if (vis[b]==0)
                {
                    vis[b]=1;
                    //processed[b]=1;
                    nodes[a].push_back(b);
                    //cout<<a<<" "<<b<<"\n";
                    pq.push(b);
                }
            }
        }
    }
    //}
    //}
    cout<<"BFS tree :\n";
    int fl=0;
    for(int in=0;in<=n;in++)
    {
        if(nodes[in].size()>0)       
        {
            cout<<in<<"->";
            fl=1;
        }

        for(int j=0;j<nodes[in].size();j++)
        {
            if(j>0)
            cout<<",";
            
            cout<<nodes[in][j];
            
        }

        if(nodes[in].size()>0)
         cout<<"\n";
    }
    if(fl==0)
    cout<<i<<"\n";
   
    

    for(int i=0;i<=n;i++)
    {
        vis[i]=0;
    }
    for(int j=0;j<n+1;j++)
    nodes[j].clear();

    cout<<"DFS tree :\n";
    // for(int j=0;j<n;j++)
    // {

    //     if(vis[i]==0)       
    //     {
            //cout<<i<<" ";
            //nodes.push_back({0,i});
    dfs(i,0,adj,nodes);
    //     }

    //     i++;
    //     if(i==n)
    //     i=0;

    // }
    
    
    fl=0;
    for(int in=0;in<=n;in++)
    {
        if(nodes[in].size()>0)       
        {
            cout<<in<<"->";
            fl=1;
        }

        for(int j=0;j<nodes[in].size();j++)
        {
            if(j>0)
            cout<<",";

            cout<<nodes[in][j];
        }

        if(nodes[in].size()>0)
         cout<<"\n";
    }

    if(fl==0)
    cout<<i<<"\n";

    


}
