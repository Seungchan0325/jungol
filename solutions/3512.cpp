#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 5050;
const ll inf = 1e18;

ll N, B, S, R, A[MAXN], D1[MAXN], D2[MAXN], DP[MAXN][MAXN];
vector<pair<int, ll>> g[MAXN], rg[MAXN];

void Dijkstra(int N, int S, ll D[], vector<pair<int, ll>> g[])
{
    for(int i = 1; i <= N; i++) D[i] = inf;
    D[S] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({-D[S], S});
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > D[u]) continue;
        for(auto [v, w] : g[u]) {
            if(D[v] > d+w) {
                D[v] = d+w;
                pq.push({-D[v], v});
            }
        }
    }
}

void DnC(int s, int l, int r, int optL, int optR)
{
    if(l > r) return;
    int m = (l+r)/2;
    int optM = -1;
    ll mn = inf;
    for(int i = optL; i <= optR && i < m; i++) {
        if(DP[s-1][i] + (m-i-1)*(A[m]-A[i]) < mn) {
            optM = i;
            mn = DP[s-1][i] + (m-i-1)*(A[m]-A[i]);
        }
    }

    DP[s][m] = mn;
    DnC(s, l, m-1, optL, optM);
    DnC(s, m+1, r, optM, optR);
}

int main()
{
    cin >> N >> B >> S >> R;
    for(int i = 0; i < R; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        g[u].push_back({v, l});
        rg[v].push_back({u, l});
    }

    Dijkstra(N, B+1, D1, g);
    Dijkstra(N, B+1, D2, rg);

    // for(int i = 1; i <= N; i++) cout << D1[i] << " ";
    // cout << "\n";
    // for(int i = 1; i <= N; i++) cout << D2[i] << " ";
    // cout << "\n";

    for(int i = 1; i <= B; i++) A[i] = D1[i] + D2[i];
    sort(A+1, A+B+1);
    for(int i = 1; i <= B; i++) A[i] += A[i-1];
    for(int i = 1; i <= B; i++) DP[0][i] = inf;
    for(int i = 1; i <= S; i++) DnC(i, 1, B, 0, B);

    // for(int i = 1; i <= S; i++) {
    //     for(int j = 1; j <= B; j++) {
    //         cout << DP[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    cout << DP[S][B];
}
