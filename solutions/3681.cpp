#include <cassert>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct Frac {
    ll p, q;
    Frac(ll _p = 0, ll _q = 1) : p(_p), q(_q)
    {
        if(q < 0) {
            p = -p;
            q = -q;
        }
    }
    auto operator <=> (const Frac& rhs) const {
        return (__int128)p * rhs.q <=> (__int128)rhs.p * q;
    }
};

struct Line {
    ll a, b, sz;
    ll eval(ll x) { return a * x + b; }
};

Frac cross(Line l, Line m)
{
    return Frac(l.b-m.b, m.a-l.a);
}

ll n, m, k, r[MAXN], c[MAXN], sz[MAXN];
ll dp[MAXN];

pair<ll, int> run(ll lambda)
{
    dp[0] = 0;

    deque<Line> dq;
    for(int i = 1; i <= n; i++) {
        Line l = {};
        l.a = -2*(c[i]-1);
        l.b = dp[i-1] + (c[i]-1) * (c[i]-1);
        if(i > 1 && r[i-1]-c[i]+1 > 0)
            l.b -= (r[i-1]-c[i]+1)*(r[i-1]-c[i]+1);
        l.sz = sz[i-1];

        while(dq.size() >= 2 && cross(dq.end()[-1], l) < cross(dq.end()[-1], dq.end()[-2])) dq.pop_back();
        dq.push_back(l);

        while(dq.size() >= 2 && cross(dq[0], dq[1]) <= r[i]) dq.pop_front();
        assert(dq.size());
        dp[i] = dq.front().eval(r[i]) + r[i] * r[i] + lambda;
        sz[i] = dq.front().sz + 1;
    }
    return {dp[n], sz[n]};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    vector<pair<int, int>> rc(n);
    for(auto& [r, c] : rc) {
        cin >> r >> c;
        if(r < c) swap(r, c);
    }
    sort(rc.begin(), rc.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    vector<pair<int, int>> valid;
    for(auto [r, c] : rc) {
        while(valid.size() && valid.back().second >= c) valid.pop_back();
        valid.push_back({r, c});
    }
    n = valid.size();
    for(int i = 0; i < n; i++) {
        r[i+1] = valid[i].first;
        c[i+1] = valid[i].second;
    }

    ll lo = 0;
    ll hi = 1e15;
    while(lo+1 < hi) {
        ll mid = (lo+hi)/2;
        if(run(mid).second >= k) lo = mid;
        else hi = mid;
    }

    auto [ans, sz] = run(lo);
    ans -= k * lo;
    cout << ans << "\n";
}
