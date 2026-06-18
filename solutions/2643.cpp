#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

#define int long long

const int inf = 1e18;

struct MaxLazySeg {
    int sz;
    vector<int> lazy;
    vector<pair<int, int>> tree;
    void init(int _sz)
    {
        sz = _sz;
        lazy.resize(4*sz);
        tree.resize(4*sz);
        init(0, sz-1, 1);
    }
    void update(int l, int r, int x) { update(l, r, x, 0, sz-1, 1); }
    pair<int, int> query(int l, int r) { return query(l, r, 0, sz-1, 1); }
private:
    void init(int s, int e, int idx)
    {
        if(s == e) {
            tree[idx].second = s;
            return;
        }
        int m = (s + e) / 2;
        init(s, m, 2*idx);
        init(m+1, e, 2*idx+1);
        tree[idx] = max(tree[2*idx], tree[2*idx+1]);
    }
    void propagate(int s, int e, int idx)
    {
        if(lazy[idx] != 0) {
            tree[idx].first += lazy[idx];
            if(s != e) {
                lazy[2*idx] += lazy[idx];
                lazy[2*idx+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }
    void update(int l, int r, int x, int s, int e, int idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            lazy[idx] = x;
            propagate(s, e, idx);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, x, s, m, 2*idx);
        update(l, r, x, m+1, e, 2*idx+1);
        tree[idx] = max(tree[2*idx], tree[2*idx+1]);
    }
    pair<int, int> query(int l, int r, int s, int e, int idx)
    {
        propagate(s, e, idx);
        if(e < l || r < s) return {-inf, -1};
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }
};

const int MAXN = 303030;

bool chk[MAXN];
int N, K, in[MAXN], par[MAXN], out[MAXN], t, w[MAXN];
vector<tuple<int, int, int>> v;
MaxLazySeg seg;
int remains;

pair<int, double> dnc(int l, int r, int up, int p)
{
    if(r < l) return {0, 0};
    int cnt = 0;
    double tim = 0;
    auto [dep, m] = seg.query(l, r);
    if(chk[m]) cnt++;
    dep = -dep;
    par[m] = p;
    in[m] = ++t;
    auto [cntl, mxl] = dnc(l, m-1, dep, m);
    auto [cntr, mxr] = dnc(m+1, r, dep, m);
    cnt += cntl + cntr;
    out[m] = t;
    in[m]--;
    out[m]--;
    w[m] = (dep - up) * (get<1>(v[r]) - get<0>(v[l]));
    tim = max(mxl, mxr);
    if(cnt)
        tim += (double)w[m]/cnt;
    else
        remains += w[m];
    return {cnt, tim};
}

signed main()
{
    cin >> N;
    int px, py;
    px = py = 0;
    for(int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        if(px != x) {
            v.push_back({px, x, y});
        }
        px = x;
        py = y;
    }
    cin >> K;

    for(int i = 0; i < K; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int lo = 0;
        int hi = v.size();
        while(lo+1 < hi) {
            int mid = (lo+hi) / 2;
            if(get<0>(v[mid]) <= a) lo = mid;
            else hi = mid;
        }

        chk[lo] = true;
    }

    seg.init(v.size());
    for(int i = 0; i < v.size(); i++) {
        auto [l, r, y] = v[i];
        seg.update(i, i, -y);
    }
    auto [_, tim] = dnc(0, ssize(v)-1, 0, -1);
    cout << fixed << setprecision(2);
    cout << remains << "\n";
}
