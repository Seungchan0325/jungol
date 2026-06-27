#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const int MAXM = 303030;
const int inf = 1e9 + 1;

struct Edge {
    int u, v, w, id;
};

bool chk[MAXM];
int n, m, uf[MAXN], dep[MAXN];
ll ans[MAXM];
Edge par[MAXN];
vector<Edge> g[MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void Union(int x, int y)
{
    x = find(x);
    y = find(y);
    uf[y] = x;
}

void dfs(int u, int p)
{
    for(auto e : g[u]) {
        if(e.v == p) continue;
        dep[e.v] = dep[u] + 1;
        par[e.v] = {e.v, e.u, e.w, e.id};
        dfs(e.v, u);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<Edge> edges;
    for(int i = 0; i < m; i++) {
        Edge e{};
        cin >> e.u >> e.v >> e.w;
        e.id = i;
        edges.push_back(e);
    }

    sort(edges.begin(), edges.end(), [](Edge e1, Edge e2) { return e1.w < e2.w; });
    iota(uf, uf+n+1, 0);

    ll cost = 0;
    vector<Edge> nmst;
    for(auto e : edges) {
        if(find(e.u) != find(e.v)) {
            chk[e.id] = true;
            cost += e.w;
            Union(e.u, e.v);
            g[e.u].push_back({e.u, e.v, e.w, e.id});
            g[e.v].push_back({e.v, e.u, e.w, e.id});
        } else {
            nmst.push_back(e);
        }
    }

    for(int i = 0; i < m; i++) {
        if(chk[i]) ans[i] = -1;
        else ans[i] = cost;
    }

    dfs(1, -1);
    sort(nmst.begin(), nmst.end(), [](Edge e1, Edge e2) { return e1.w < e2.w; });
    iota(uf, uf+n+1, 0);

    for(auto e : nmst) {
        int u = find(e.u);
        int v = find(e.v);
        while(u != v) {
            if(dep[u] < dep[v]) swap(u, v);
            ans[par[u].id] = cost - par[u].w + e.w;
            Union(par[u].v, u);
            u = find(par[u].v);
        }
    }

    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}
