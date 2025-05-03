#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 21
#define MOD 100000009
using namespace std;

class Graph
{
public:
    lli adjmat[MAX][MAX];
    lli total;

    Graph(lli n)
    {
        total=n;
        for (lli i = 0; i < n; i++)
        {
            adjmat[i][i] = 0;
            for (lli j = i + 1; j < n; j++)
            {
                adjmat[i][j] = MOD;
                adjmat[j][i] = MOD;
            }
        }
    }
};




lli dp[MAX + 1][(1 << MAX) + 1];



Graph Create_Random_Graph(lli n)
{
    Graph g(n);
    for (lli i = 0; i < n; i++)
    {
        for (lli j = i + 1; j < n; j++)
        {
            lli mx = 200;
            lli mn = 50;
            for (lli k = 0; k < n; k++)
            {
                if (k == i || k == j)
                    continue;
                if (g.adjmat[i][k] != MOD && g.adjmat[j][k] != MOD)
                    mn = max(mn, abs(g.adjmat[i][k] - g.adjmat[j][k]));

                mx = min(mx, g.adjmat[i][k] + g.adjmat[j][k]);
            }
            if (mn > mx)
                mx = mn;

            lli val = mn + (rand() % (mx - mn + 1));

            g.adjmat[i][j] = val;
            g.adjmat[j][i] = val;
        }
    }
    return g;
}

void dfs(lli node, lli par,vector<lli> *mstree,vector<lli> &preorder)
{
    // cout<<node<<"nodenode\n";
    preorder.push_back(node);
    for (auto child : mstree[node])
    {
        if (child == par)
            continue;

        dfs(child, node,mstree,preorder);
    }
}

vector<lli> Metric_App_TSP(Graph g)
{
    lli n = g.total;
    vector<bool> vis(n, 0);
    vector<lli> mstree[n];
    vector<lli> preorder;
    lli root = 0;
    priority_queue<plli> pq;
    vector<lli> parent(n, -1);
    vector<lli> dist(n, MOD);
    pq.push({0, root});
    dist[root] = 0;

    while (!pq.empty())
    {
        lli a = pq.top().second;
        pq.pop();

        if (vis[a])
            continue;

        vis[a] = true;

        for (lli i=0;i<n;i++)
        {
            // cout<<child.first<<"\n";
            if (vis[i])
                continue;
            if (dist[i] > g.adjmat[a][i])
            {

                dist[i] = g.adjmat[a][i];
                pq.push({-dist[i], i});
                parent[i] = a;
            }
        }
    }

    for (lli i = 0; i < n; i++)
    {
        // cout<<i<<" "<<parent[i]<<"\n";
        if (i == root)
            continue;

        mstree[parent[i]].push_back(i);
        mstree[i].push_back(parent[i]);
    }
    // for(lli i=0;i<n;i++)
    // {

    //     for(auto child:mstree[i])
    //     cout<<child<<" cfcf ";
    //     cout<<"\n";
    // }

    dfs(root, -1,mstree,preorder);
    preorder.push_back(root);

    // lli sum = 0;
    // for (lli i = 0; i < preorder.size(); i++)
    // {
    //     sum += g.adjmat[preorder[i]][preorder[(i + 1) % preorder.size()]];
    // }
    // cout << preorder[0] << "\n";
    return preorder;
}

vector<lli> Exact_TSP(Graph g)
{
    lli n = g.total;

    lli root = 0;
    for (lli i = 0; i <= n; i++)
    {
        for (lli j = 0; j <= (1 << n); j++)
        {
            dp[i][j] = MOD;
        }
    }
    dp[0][1]=0;
    // for (lli i = 0; i < n; i++)
    // {
    //     // dp[i][0] = 0;
    //     dp[i][(1 << i)] = 0;
    // }
    vector<lli> parent(n, -1);

    for (lli mask = 1; mask < (1 << n); mask++)
    {
        for (lli i = 0; i < n; i++)
        {
            if ((mask & (1 << i)) != 0)
                continue;

            for (lli j = 0; j < n; j++)
            {
                if ((mask & (1 << j)) == 0)
                    continue;
                if (dp[i][mask ^ (1 << i)] > dp[j][mask] + g.adjmat[j][i])
                {
                    dp[i][mask ^ (1 << i)] = dp[j][mask] + g.adjmat[j][i];
                    parent[i] = j;
                }
            }
        }
    }

    // for(int i=0;i<n;i++)
    // {
    //     cout<<i<<" "<<parent[i]<<"\n";
    // }
    // cout<<"\n";
    // for (lli i = 0; i < n; i++)
    // {
    //     for (lli j = 0; j < (1 << n); j++)
    //     {
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    lli sum = MOD;
    lli mnind = 0;
    for (lli i = 0; i < n; i++)
    {
        if(i==root)
        continue;

        if (sum > dp[i][(1 << n) - 1] + g.adjmat[i][root])
        {
            sum = dp[i][(1 << n) - 1] + g.adjmat[i][root];
            mnind = i;
        }
    }
    lli mask = (1 << n) - 1;
    vector<lli> path;
    path.push_back(mnind);
    for (int i = 0; i < n - 1; i++)
    {
        lli nwmask = mask ^ (1 << mnind);
        // cout<<i<<" "<<mnind<<" "<<bitset<20>(nwmask)<<"\n";
        for (int j = 0; j < n; j++)
        {
            if ((nwmask & (1 << j)) && (dp[j][nwmask] + g.adjmat[j][mnind]) == dp[mnind][mask])
            {
                // cout<<"here\n";
                path.push_back(j);
                mnind = j;
                break;
            }
        }
        mask = nwmask;
    }
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == root)
        {
            mnind = i;
        }
    }
    vector<lli> nwpath;
    for(lli i=0;i<path.size();i++)
    {
        nwpath.push_back(path[(i+mnind)%path.size()]);
    }
    nwpath.push_back(root);
    reverse(nwpath.begin(),nwpath.end());

    // cout<<path[i]<<" ";
    // cout<<'\n';
    return nwpath;
}

lli Calculate_Tour_Length(vector<lli> &path,Graph g)
{
    lli sum=0;
    for(int i=0;i+1<path.size();i++)
    {
        sum+=g.adjmat[path[i]][path[i+1]];

    }
    return sum;
}

int main()
{
    lli t = 5;
    cin >> t;
    lli ff = t;

    while (t--)
    {
        // cout<<t+1<<'\n';

        lli n = 20;
        srand(t);

        Graph g=Create_Random_Graph(n);
        // for (lli i = 0; i < n; i++)
        // {
        //     for (lli j = 0; j < n; j++)
        //     {
        //         cout << g.adjmat[i][j] << " ";
        //     }
        //     cout << "\n";
        // }


        auto fir = Exact_TSP(g);
        auto sec = Metric_App_TSP(g);

        // for(int i=0;i<fir.size();i++)
        // {
        //     cout<<fir[i]<<" ";
        // }
        // cout<<"\n";
        // for(int i=0;i<sec.size();i++)
        // {
        //     cout<<sec[i]<<" ";
        // }
        lli ex=Calculate_Tour_Length(fir,g);
        lli ap=Calculate_Tour_Length(sec,g);


        //cout << ex << " " << ap << "\n";
        cout << "( " << ff - t << ", " << 1.0 * ap / ex  << " )\n";
    }
}
