#include <bits/stdc++.h>
#define lli long long
#define plli pair<lli, lli>
#define MAX 200005
#define MOD 1000000007
#define INF 1000000007
#define cin in
#define cout out

using namespace std;

void dijkstra(vector<pair<lli, lli>> *adj, lli n, lli root, lli dest,ostream &out)
{
    vector<lli> parent(n + 1, -1);
    vector<lli> distance(n + 1, INF);
    priority_queue<pair<lli, lli>> pq;

    pq.push({0, root});
    distance[root] = 0;

    vector<bool> processed(n + 1);

    while (!pq.empty())
    {
        lli a = pq.top().second;
        pq.pop();

        if (processed[a])
            continue;

        processed[a] = true;

        for (auto u : adj[a])
        {

            lli b = u.first;
            lli w = abs(u.second);
            if (processed[b])
                continue;
            if (distance[a] + w < distance[b])
            {
                distance[b] = distance[a] + w;
                pq.push({-distance[b], b});
                parent[b] = a;
            }
        }
    }
    cout<<"Dijkstra Algorithm:\n";
    cout << distance[dest] << "\n";
    stack<lli> path;
    lli cur = dest;

    while (cur != root && cur != -1)
    {
        path.push(cur);
        cur = parent[cur];
        // cout<<"haha\n";
    }
    path.push(root);
    // cout<<path.top();

    while (!path.empty())
    {
        cout << path.top();
        path.pop();
        if (!path.empty())
        {
            cout << " -> ";
        }
    }
    cout<<"\n";
}

void bellmanford(vector<pair<lli, lli>> *adj, lli n, lli root, lli dest,ostream &out)
{
    vector<lli> parent(n + 1, -1);
    vector<lli> distance(n + 1, INF);

    distance[root] = 0;

    for (lli i = 1; i <= n - 1; i++)
    {
        for (lli j = 0; j < n; j++)
        {
            if (distance[j] != INF)
            {
                for (auto child : adj[j])
                {
                    if (distance[j] + child.second < distance[child.first])
                    {
                        distance[child.first] = distance[j] + child.second;
                        parent[child.first] = j;
                    }
                }
            }
        }
    }

    lli neg = 0;

    for (lli j = 0; j < n; j++)
    {
        if (neg == 1)
            break;

        if (distance[j] != INF)
        {
            for (auto child : adj[j])
            {
                if (distance[j] + child.second < distance[child.first])
                {
                    neg = 1;
                    break;
                }
            }
        }
    }
    cout<<"Bellman Ford Algorithm:\n";
    if (neg == 1)
    {
        cout << "Negative weight cycle present\n";
    }

    else
    {
        cout << distance[dest] << "\n";
        stack<lli> path;
        lli cur = dest;

        while (cur != root && cur != -1)
        {
            path.push(cur);
            cur = parent[cur];
            // cout<<"haha\n";
        }
        path.push(root);
        // cout<<path.top();

        while (!path.empty())
        {
            cout << path.top();
            path.pop();
            if (!path.empty())
            {
                cout << " -> ";
            }
        }
        cout<<"\n";
    }
}

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");

    lli t = 1;
    // cin >> t;
    while (t--)
    {

        lli n, e;
        cin >> n >> e;
        vector<pair<lli, lli>> adj[n + 1];

        for (lli i = 0; i < e; i++)
        {
            lli node1, node2, w;
            cin >> node1 >> node2 >> w;
            // cout<<node1<<" "<<node2<<" "<<w<<endl;

            adj[node1].push_back({node2, w});
            // adj[node2].push_back({node1, w});
        }

        lli root, dest;
        cin >> root >> dest;

        bellmanford(adj, n, root, dest,out);
        cout<<"\n";
        dijkstra(adj, n, root, dest,out);
    }
}