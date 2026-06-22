#include <bits/stdc++.h>
#include <ios>

using namespace std;

using ll = long long;

const int MAXN = 303030;
const int MAXV = 1000000;
const int inf = 1e9;

int N, A[MAXN];
int tree[4*MAXV], lazy[4*MAXV];

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

void update(int l, int r, int x, int s = 1, int e = MAXV, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += x;
        push(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, x, s, m, 2*idx);
    update(l, r, x, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = MAXV, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return inf;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    ll sum = 0;
    for(int i = N; i >= 1; i--) {
        sum += query(A[i], A[i]);
        update(A[i]+1, MAXV, 1);
    }
    for(int i = 1; i <= N; i++) {
        update(A[i]+1, MAXV, -1);
        ll ans = sum - query(A[i], A[i]) + query(1, MAXV);
        update(1, A[i]-1, 1);
        cout << ans << " ";
    }
}
