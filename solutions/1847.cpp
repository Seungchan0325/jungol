#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
const int inf = 0x33333333;

int N, K, D[MAXN][MAXN], P[MAXN][MAXN], sz[MAXN], TD[MAXN][MAXN], TP[MAXN][MAXN], tsz[MAXN];
vector<pair<int, int>> g[MAXN];
vector<int> selects;

void dfs(int u, int p)
{
    sz[u] = 1;
    D[u][0] = 0;
    P[u][1] = 0;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        for(int i = sz[u]-1; i >= 0; i--) {
            int mn = inf;
            for(int j = 0; j < sz[v] && j <= i; j++)  mn = min(mn, D[u][i-j] + D[v][j] + w);
            for(int j = 1; j <= sz[v] && j <= i; j++) mn = min(mn, D[u][i-j] + P[v][j]);
            D[u][i] = mn;
        }
        for(int i = sz[u]; i >= 1; i--) {
            int mn = inf;
            for(int j = 0; j < sz[v] && j <= i; j++)  mn = min(mn, P[u][i-j] + D[v][j]);
            for(int j = 1; j <= sz[v] && j <= i; j++) mn = min(mn, P[u][i-j] + P[v][j] + w);
            P[u][i] = mn;
        }
    }
}

void trace(int u, int p, int k, bool selected)
{
    if(selected) selects.push_back(u);
    for(int i = 0; i < g[u].size(); i++) {
        for(int j = 0; j <= sz[u]; j++) {
            TD[i][j] = TP[i][j] = inf;
        }
    }
    tsz[u] = 1;
    TD[0][0] = 0;
    TP[0][1] = 0;
    int iter = 0;
    vector<pair<int, int>> ch;
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        ch.push_back({v, w});
        iter++;
        tsz[u] += sz[v];
        for(int i = tsz[u]-1; i >= 0; i--) {
            int mn = inf;
            for(int j = 0; j < sz[v] && j <= i; j++)  mn = min(mn, TD[iter-1][i-j] + D[v][j] + w);
            for(int j = 1; j <= sz[v] && j <= i; j++) mn = min(mn, TD[iter-1][i-j] + P[v][j]);
            TD[iter][i] = mn;
        }
        for(int i = tsz[u]; i >= 1; i--) {
            int mn = inf;
            for(int j = 0; j < sz[v] && j <= i; j++)  mn = min(mn, TP[iter-1][i-j] + D[v][j]);
            for(int j = 1; j <= sz[v] && j <= i; j++) mn = min(mn, TP[iter-1][i-j] + P[v][j] + w);
            TP[iter][i] = mn;
        }
    }

    vector<tuple<int, int, bool>> traces;
    for(int i = iter; i > 0; i--) {
        int now = selected ? TP[i][k] : TD[i][k];
        auto [v, w] = ch[i-1];
        for(int j = 0; j < sz[v] && j <= k; j++) {
            int cand = D[v][j];
            if(selected) cand += TP[i-1][k-j];
            else cand += TD[i-1][k-j] + w;
            if(now == cand) {
                traces.push_back({v, j, false});
                k -= j;
                goto ESCAPE;
            }
        }
        for(int j = 1; j <= sz[v] && j <= k; j++) {
            int cand = P[v][j];
            if(selected) cand += TP[i-1][k-j] + w;
            else cand += TD[i-1][k-j];
            if(now == cand) {
                traces.push_back({v, j, true});
                k -= j;
                goto ESCAPE;
            }
        }
ESCAPE: {}
    }
    for(auto [v, k, selected] : traces) trace(v, u, k, selected);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    memset(D, inf, sizeof(D));
    memset(P, inf, sizeof(P));
    memset(TD, inf, sizeof(D));
    memset(TP, inf, sizeof(P));

    dfs(1, -1);

    int ans = min(D[1][K], P[1][K]);

    cout << ans << "\n";

    trace(1, -1, K, P[1][K] == ans);
    sort(selects.begin(), selects.end());
    for(auto u : selects) cout << u << " ";
    cout << "\n";
}
