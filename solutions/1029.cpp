#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5 * 101010;

bool fail;
int n, l[MAXN], r[MAXN], dep[MAXN], ans, haslow[MAXN], isAllLow[MAXN], mx, mn;

void dfs(int now)
{
    if(l[now] != -1) {
        dep[l[now]] = dep[now] + 1;
        dfs(l[now]);
    }
    if(r[now] != -1) {
        dep[r[now]] = dep[now] + 1;
        dfs(r[now]);
    }
}

void balancing(int now)
{
    isAllLow[now] = true;
    for(auto ch : {l[now], r[now]}) {
        if(ch != -1) {
            balancing(ch);
            haslow[now] |= haslow[ch];
            if(!isAllLow[ch]) isAllLow[now] = false;
        }
    }
    if(l[now] == -1 && r[now] == -1) {
        if(dep[now] == mn) {
            isAllLow[now] = haslow[now] = true;
        } else {
            isAllLow[now] = haslow[now] = false;
        }
    }
    if(l[now] != -1 && r[now] != -1) {
        if(haslow[l[now]] && haslow[r[now]] && !isAllLow[l[now]] && !isAllLow[r[now]]) {
            fail = true;
        }
        if(haslow[l[now]]) {
            if(!isAllLow[r[now]]) {
                ans++;
            }
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> l[i] >> r[i];
    int m = n;
    for(int i = 1; i <= n; i++) {
        if(l[i] == -1) l[i] = ++m;
        if(r[i] == -1) r[i] = ++m;
    }
    for(int i = n+1; i <= m; i++) {
        l[i] = r[i] = -1;
    }
    dfs(1);
    mn = 1e9;
    mx = -1e9;
    for(int i = n+1; i <= m; i++) {
        mn = min(mn, dep[i]);
        mx = max(mx, dep[i]);
    }

    if(mx - mn > 1) {
        cout << "-1\n";
        return 0;
    }

    balancing(1);
    if(fail) cout << "-1\n";
    else cout << ans << "\n";
}
