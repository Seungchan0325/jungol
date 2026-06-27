#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

bool inStack[MAXN], G[MAXN][MAXN];
int n, m, num[MAXN], low[MAXN], scc[MAXN], pv, t;
vector<int> g[MAXN];
stack<int> s;

void dfs(int u, int p)
{
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);
    for(auto v : g[u]) {
        if(v == p) continue;
        if(!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], low[v]);
        }
    }
    if(low[u] == num[u]) {
        t++;
        while(true) {
            auto v = s.top(); s.pop();
            inStack[v] = false;
            scc[v] = t;
            if(v == u) break;
        }
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int comp = 0;
    for(int i = 1; i <= n; i++) {
        if(!num[i]) {
            dfs(i, -1);
            comp++;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(auto j : g[i]) G[scc[i]][scc[j]] = G[scc[j]][scc[i]] = true;
    }

    int leafs = 0;
    int sole = 0;
    for(int i = 1; i <= t; i++) {
        int cnt = 0;
        for(int j = 1; j <= t; j++) {
            if(i == j) continue;
            cnt += G[i][j];
        }
        if(cnt == 1) leafs++;
    }

    assert(comp == 1);
    int ans = comp - 1 + (leafs + 1) / 2;
    cout << ans << "\n";
}
