#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick {
    int n;
    vector<ll> tree;
    void init(int _n)
    {
        n = _n;
        tree.resize(n+1);
    }
    void upd(int x, ll v)
    {
        while(x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }
    ll qry(int x)
    {
        ll res = 0;
        while(x) {
            res += tree[x];
            x -= x & -x;
        }
        return res;
    }
};

const int MAXN = 101010;

int N, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    vector<int> vs;
    for(int i = 1; i <= N; i++) {
        vs.push_back(A[i]-i);
        vs.push_back(A[i]+i);
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    ll ans = 1e18;
    Fenwick lcnt, rcnt, lsum, rsum;
    lcnt.init(vs.size());
    lsum.init(vs.size());
    rcnt.init(vs.size());
    rsum.init(vs.size());
    for(int i = 1; i <= N; i++) {
        int ridx = lower_bound(vs.begin(), vs.end(), A[i] + i) - vs.begin() + 1;
        rcnt.upd(ridx, 1);
        rsum.upd(ridx, A[i] + i);
    }

    for(int i = 1; i <= N; i++) {
        int lo = 0;
        int hi = 2e9;
        while(lo+1 < hi) {
            int mid = (lo+hi) / 2;
            int lef = upper_bound(vs.begin(), vs.end(), mid - i) - vs.begin();
            int rig = upper_bound(vs.begin(), vs.end(), mid + i) - vs.begin();
            if(lcnt.qry(lef) + rcnt.qry(rig) < (N+1)/2) lo = mid;
            else hi = mid;
        }
        int opt = max({hi, i, N-i+1});
        int lef = upper_bound(vs.begin(), vs.end(), opt - i) - vs.begin();
        int rig = upper_bound(vs.begin(), vs.end(), opt + i) - vs.begin();
        ll sum = 0;
        sum += (lsum.qry(vs.size()) - lsum.qry(lef)) - (opt - i) * (lcnt.qry(vs.size()) - lcnt.qry(lef));
        sum += (opt - i) * lcnt.qry(lef) - lsum.qry(lef);
        sum += (rsum.qry(vs.size()) - rsum.qry(rig)) - (opt + i) * (rcnt.qry(vs.size()) - rcnt.qry(rig));
        sum += (opt + i) * rcnt.qry(rig) - rsum.qry(rig);
        ans = min(ans, sum);

        int lidx = lower_bound(vs.begin(), vs.end(), A[i] - i) - vs.begin() + 1;
        int ridx = lower_bound(vs.begin(), vs.end(), A[i] + i) - vs.begin() + 1;
        rcnt.upd(ridx, -1);
        rsum.upd(ridx, -(A[i] + i));
        lcnt.upd(lidx, 1);
        lsum.upd(lidx, A[i] - i);
    }
    cout << ans << "\n";
}
