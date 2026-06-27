#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;

bool fail;
int n, m, sign[MAXN];
vector<pair<int, int>> g[MAXN];

int dfs(int u, int side)
{
    sign[u] = side;
    int res = side;
    for(auto [v, w] : g[u]) {
        if(sign[v]) {
            if(sign[v] != side * w) fail = true;
            continue;
        }
        res += dfs(v, side * w);
    }
    return res;
}

int main()
{
    int tc = 5;
    while(tc--) {
        cin >> n >> m;

        fail = false;
        for(int i = 1; i <= n; i++) {
            sign[i] = 0;
            g[i].clear();
        }
        for(int i = 0; i < m; i++) {
            int w, x, y;
            cin >> w >> x >> y;
            g[x].push_back({y, w});
            g[y].push_back({x, w});
        }

        vector<int> v;
        for(int i = 1; i <= n; i++) {
            if(!sign[i]) v.push_back(abs(dfs(i, 1)));
        }
        if(fail) {
            cout << "-1\n";
            continue;
        }

        bitset<2*MAXN> dp;
        dp[n] = true;
        for(auto x : v) {
            dp = (dp << x) | (dp >> x);
        }
        int ans = 1e9;
        for(int i = 0; i <= 2*n; i++) {
            if(dp[i]) ans = min(ans, abs(n-i));
        }
        cout << ans << "\n";
    }
}
