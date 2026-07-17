#include <bits/stdc++.h>
#include <iterator>

using namespace std;

using ll = long long;

const int MAXN = 303030;

int N, K, P[MAXN], W[MAXN];
ll ans[MAXN], sum[MAXN], dp[MAXN], d[MAXN], p[MAXN];
multiset<ll> s[MAXN];

void mrg(multiset<ll>& a, multiset<ll>& b, ll& sa, ll& sb)
{
    // cout << "--- mrg ---\n";
    // cout << sa << " : ";
    // for(auto x : std::views::reverse(a)) cout << x << " ";
    // cout << "\n";
    // cout << sb << " : ";
    // for(auto x : std::views::reverse(b)) cout << x << " ";
    // cout << "\n";
    if(a.size() < b.size()) {
        swap(a, b);
        swap(sa, sb);
    }
    int n = a.size();
    int m = b.size();
    if(m == 0) return;
    if(2*m >= K) {
        sa = 0;
        for(int i = 1; i <= n; i++) {
            d[i] = d[i-1] + *a.rbegin();
            a.erase(prev(a.end()));
        }
        for(int i = 1; i <= m; i++) {
            p[i] = p[i-1] + *b.rbegin();
            b.erase(prev(b.end()));
        }
        for(int i = n+1; i <= K; i++) d[i] = d[i-1];
        for(int i = m+1; i <= K; i++) p[i] = p[i-1];
        for(int i = 1; i <= (K+1)/2; i++) dp[i] = d[i] + p[i];
        for(int i = (K+1)/2; i <= n; i++) dp[i] = max(d[i] + p[K-i], d[K-i] + p[i]);
        for(int i = (K+1)/2; i <= n; i++) dp[i] = max(dp[i], dp[i-1]);
        sa = dp[n];
        for(int i = 1; i <= n; i++) a.insert(dp[i] - dp[i-1]);
    } else {
        vector<ll> t;
        if(m > 0) {
            auto it = prev(a.end());
            auto jt = prev(b.end());
            for(int i = 1; i <= m; i++) {
                t.push_back(*it + *jt);
                it--; jt--;
            }
        }
        if(n+m > K) {
            auto it = a.begin(); advance(it, n+m-K);
            auto jt = b.begin();
            for(int i = K-m+1; i <= n; i++) {
                it--;
                t.push_back(max(*it - *jt, 0ll));
                jt++;
            }
        }
        for(int i = 1; i <= m; i++) sa -= *prev(a.end()), a.erase(prev(a.end()));
        for(int i = K-m+1; i <= n; i++) sa -= *a.begin(), a.erase(a.begin());
        for(auto x : t) a.insert(x), sa += x;
    }
    // cout << sa << " : ";
    // for(auto x: std::views::reverse(a)) cout << x << " ";
    // cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    for(int i = 2; i <= N; i++) cin >> P[i] >> W[i];
    for(int v = N; v >= 1; v--) {
        ans[v] = sum[v];
        s[v].insert(W[v]);
        sum[v] += W[v];
        while(s[v].size() > K) {
            sum[v] -= *s[v].begin();
            s[v].erase(s[v].begin());
        }
        if(P[v]) mrg(s[P[v]], s[v], sum[P[v]], sum[v]);
    }
    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
}
