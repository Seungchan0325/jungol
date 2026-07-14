#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

const int MAXX = 250505;

struct Point {
    int x, y, k;
    auto operator <=> (const Point& rhs) const {
        return tie(x, y, k) <=> tie(rhs.x, rhs.y, rhs.k);
    }
};

int N, K, tree[4*MAXX], lazy[4*MAXX];

void push(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = MAXX, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += v;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

bool run(int R, const vector<Point>& ps)
{
    vector<multiset<pair<int, int>>> lines(K);
    auto add = [&](int l, int r, int k) {
        auto& line = lines[k];
        auto it = line.insert({l, r});
        if(it != line.begin()) {
            l = max(l, prev(it)->second+1);
        }
        if(next(it) != line.end()) {
            r = min(r, next(it)->first-1);
        }
        update(l, r, 1);
    };
    auto sub = [&](int l, int r, int k) {
        auto& line = lines[k];
        auto it = line.lower_bound({l, r});
        if(it != line.begin()) {
            l = max(l, prev(it)->second+1);
        }
        if(next(it) != line.end()) {
            r = min(r, next(it)->first-1);
        }
        line.erase(it);
        update(l, r, -1);
    };
    bool ok = false;
    int i, j;
    for(i = 0, j = 0; i < ps.size(); i++) {
        while(j < ps.size() && ps[i].x - ps[j].x > R) {
            sub(ps[j].y, ps[j].y+R, ps[j].k);
            j++;
        }
        add(ps[i].y, ps[i].y+R, ps[i].k);
        if(tree[1] >= K) ok = true;
    }
    while(j < ps.size()) {
        sub(ps[j].y, ps[j].y+R, ps[j].k);
        j++;
    }
    return ok;
}

int main()
{
    cin >> N >> K;
    vector<Point> ps(N);
    for(auto& [x, y, k] : ps) cin >> x >> y >> k, k--;
    sort(ps.begin(), ps.end());
    int lo = -1;
    int hi = 250505;
    while(lo+1 < hi) {
        int mid = (lo+hi) / 2;
        if(run(mid, ps)) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";
}
