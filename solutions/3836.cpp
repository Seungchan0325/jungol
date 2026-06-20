#include <bits/stdc++.h>
#include <ios>

using namespace std;

const int MAXN = 101010;
const int inf = 1e9;

bool erased[MAXN];
int N, sz[MAXN];
long long ans;
vector<pair<int, int>> g[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto [v, w] : g[u]) {
        if(erased[v] || v == p) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int u, int p, int n)
{
    for(auto [v, w] : g[u]) {
        if(erased[v] || v == p) continue;
        if(sz[v] > n/2) return get_cent(v, u, n);
    }
    return u;
}

void dfs(int u, int p, int sum, int mn, int mx, vector<tuple<int, int, int>>& path)
{
    for(auto [v, w] : g[u]) {
        if(erased[v] || v == p) continue;
        path.push_back({sum-w, mn, mx});
        dfs(v, u, sum-w, min(mn, sum-w), max(mx, sum-w), path);
    }
}

void dnc(int u)
{
    get_sz(u, -1);
    int c = get_cent(u, -1, sz[u]);

    vector<pair<int, int>> yes, no;
    for(int i = 0; i < g[c].size(); i++) {
        auto [v, w] = g[c][i];
        if(erased[v]) continue;
        vector<tuple<int, int, int>> pnow;
        pnow.push_back({-w, inf, -inf});
        dfs(v, c, -w, -w, -w, pnow);
        for(auto [s, mn, mx] : pnow) {
            if(s == 0 && (mn-s) * (mx-s) <= 0) ans++;
            mn = min(mn, 0);
            mx = max(mx, 0);
            if((mn-s) * (mx-s) <= 0) {
                yes.push_back({s, i});
            } else {
                no.push_back({s, i});
            }
        }
    }
    sort(yes.begin(), yes.end());
    sort(no.begin(), no.end());

    for(int i = 0; i < yes.size(); i++) {
        pair<int, int> up = {-yes[i].first, N};
        pair<int, int> lo = {-yes[i].first, 0};
        pair<int, int> now = {-yes[i].first, yes[i].second};
        ans += upper_bound(yes.begin(), yes.begin()+i, up) - lower_bound(yes.begin(), yes.begin()+i, lo);
        ans -= upper_bound(yes.begin(), yes.begin()+i, now) - lower_bound(yes.begin(), yes.begin()+i, now);
        ans += upper_bound(no.begin(), no.end(), up) - lower_bound(no.begin(), no.end(), lo);
        ans -= upper_bound(no.begin(), no.end(), now) - lower_bound(no.begin(), no.end(), now);
    }

    erased[c] = true;
    for(auto [v, w] : g[c]) {
        if(erased[v]) continue;
        dnc(v);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(c == 0) c = -1;
        else c = 1;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    dnc(1);

    cout << ans << "\n";
}
