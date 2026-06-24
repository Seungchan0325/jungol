#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int inf = 1e9;

struct Fenwick {
    vector<int> pre;
    vector<int> tree;
    void init(vector<int>& v)
    {
        pre = v;
        tree.resize(pre.size()+1);
    }
    void upd(int x, int v)
    {
        x = lower_bound(pre.begin(), pre.end(), x) - pre.begin() + 1;
        while(x <= pre.size()) {
            tree[x] += v;
            x += x & -x;
        }
    }
    int qry(int x)
    {
        int res = 0;
        x = upper_bound(pre.begin(), pre.end(), x) - pre.begin();
        if(x < 0) return 0;
        while(x) {
            res += tree[x];
            x -= x & -x;
        }
        return res;
    }
};

int N, Q, ans[MAXN];
Fenwick tree[4*MAXN];

vector<int> init(vector<vector<int>>& v, int s, int e, int idx)
{
    if(s == e) {
        tree[idx].init(v[s]);
        return v[s];
    }
    int m = (s + e) / 2;
    auto l = init(v, s, m, 2*idx);
    auto r = init(v, m+1, e, 2*idx+1);
    vector<int> now(l.size() + r.size());
    merge(
        l.begin(), l.end(),
        r.begin(), r.end(),
        now.begin()
    );
    tree[idx].init(now);
    return now;
}

void update(int x, int y, int v, int s, int e, int idx)
{
    if(e < x || x < s) return;
    tree[idx].upd(y, v);
    if(s == e) return;
    int m = (s + e) / 2;
    update(x, y, v, s, m, 2*idx);
    update(x, y, v, m+1, e, 2*idx+1);
}

int query(int xl, int xr, int yl, int yr, int s, int e, int idx)
{
    if(e < xl || xr < s) return 0;
    if(xl <= s && e <= xr) return tree[idx].qry(yr) - tree[idx].qry(yl-1);
    int m = (s + e) / 2;
    return query(xl, xr, yl, yr, s, m, 2*idx) + query(xl, xr, yl, yr, m+1, e, 2*idx+1);
}

void print(int s, int e, int idx)
{
    if(e == s) {
        cout << s << " ";
        for(int i = 0; i < tree[idx].pre.size(); i++) {
            cout <<tree[idx].qry(tree[idx].pre[i]) << " ";
        }
        cout << "\n";
        return;
    }
    int m = (s + e) / 2;
    print(s, m, 2*idx);
    print(m+1, e, 2*idx+1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> Q;
    vector<int> as;
    vector<array<int, 2>> scores(N);
    for(auto& [a, b] : scores) {
        cin >> a >> b;
        as.push_back(a);
    }
    sort(as.begin(), as.end());
    as.erase(unique(as.begin(), as.end()), as.end());
    vector<vector<int>> v(as.size());
    for(auto [a, b] : scores) {
        a = lower_bound(as.begin(), as.end(), a) - as.begin();
        v[a].push_back(b);
    }
    for(auto& i : v) sort(i.begin(), i.end());

    init(v, 0, ssize(as)-1, 1);

    vector<array<int, 4>> qs(Q);
    int idx = 0;
    for(auto& [x, y, z, w] : qs) cin >> x >> y >> z, w = idx++;

    sort(scores.begin(), scores.end(), [](array<int, 2> a, array<int, 2> b) {
        return a[0] + a[1] > b[0] + b[1];
    });
    sort(qs.begin(), qs.end(), [](array<int, 4> a, array<int, 4> b) {
        return a[2] > b[2];
    });

    int p = 0;
    for(auto [x, y, z, w] : qs) {
        while(p < N && scores[p][0]+scores[p][1] >= z) {
            auto [a, b] = scores[p];
            a = lower_bound(as.begin(), as.end(), a) - as.begin();
            update(a, b, 1, 0, ssize(as)-1, 1);
            p++;
        }
        x = lower_bound(as.begin(), as.end(), x) - as.begin();
        ans[w] = query(x, inf, y, inf, 0, ssize(as)-1, 1);
    }

    for(int i = 0; i < Q; i++) cout << ans[i] << "\n";
}
