#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

int N1, N2, K, uf[MAXN], sz[MAXN], R1, R2, num_leaf[2*MAXN], leaf[2*MAXN];
vector<int> g[2*MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    sz[x] += sz[y];
    uf[y] = x;
}

void dfs(int u)
{
    for(auto v : g[u]) {
        dfs(v);
        if(!leaf[u]) leaf[u] = leaf[v];
        num_leaf[u] += num_leaf[v];
    }
}

int main()
{
    cin >> N1 >> N2 >> K;
    for(int i = 1; i <= N1; i++) {
        int par; cin >> par;
        if(par) g[par].push_back(i);
        else R1 = i;
    }
    for(int i = 1; i <= N2; i++) {
        int par; cin >> par;
        if(par) g[par+N1].push_back(i+N1);
        else R2 = i+N1;
    }

    for(int i = 1; i <= K; i++) {
        uf[i] = i;
        sz[i] = 1;
        leaf[i] = leaf[i+N1] = i;
        num_leaf[i] = num_leaf[i+N1] = 1;
    }

    dfs(R1);
    dfs(R2);

    vector<pair<int, int>> order;
    for(int i = 1; i <= N1; i++) order.push_back({num_leaf[i], i});
    for(int i = 1; i <= N2; i++) order.push_back({num_leaf[i+N1], i+N1});
    sort(order.begin(), order.end());

    bool ans = true;
    for(auto [num, u] : order) {
        for(int i = 1; i < g[u].size(); i++) {
            int x = leaf[g[u][i]];
            int y = leaf[g[u][i-1]];
            merge(x, y);
        }
        if(num < sz[find(leaf[u])]) ans = false;
    }

    if(ans) cout << "YES\n";
    else cout << "NO\n";
}
