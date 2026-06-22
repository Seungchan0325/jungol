#include <bits/stdc++.h>
#include <ios>

using namespace std;

const int MAXN = 505050;

int n, m, a[MAXN];
vector<int> tree[MAXN<<1];

void init()
{
    for(int i = 0; i < n; i++) {
        tree[i+n].push_back(a[i]);
    }
    for(int i = n-1; i > 0; i--) {
        tree[i].resize(tree[i<<1].size()+tree[i<<1|1].size());
        merge(tree[i<<1].begin(), tree[i<<1].end(),
            tree[i<<1|1].begin(), tree[i<<1|1].end(),
            tree[i].begin());
    }
}

int query(int l, int r, int x)
{
    int res = 0;
    for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
        if(l&1) {
            res += upper_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
            l++;
        }
        if(~r&1) {
            res += upper_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
            r--;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    init();

    while(m--) {
        int s, e, l, r;
        cin >> s >> e >> l >> r;
        s--; e--;
        int ans = query(s, e, r) - query(s, e, l-1);
        cout << ans << "\n";
    }
}
