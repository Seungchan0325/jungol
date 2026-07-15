#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, m;
pair<int, int> f[MAXN<<1];
vector<pair<int, int>> lv[MAXN<<2];

int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> f[i].first, f[i].second = 0;
    for(int i = n; i < n+m; i++) cin >> f[i].first, f[i].second = 1;
    sort(f, f+n+m);
    int level = n;
    for(int i = 0; i < n+m; i++) {
        if(f[i].second == 0) lv[--level].push_back(f[i]);
        else lv[level++].push_back(f[i]);
    }

    int ans = 0;
    for(int i = 0; i < n+m; i++) {
        int t = 0;
        for(int j = 1; j < lv[i].size(); j+=2) {
            t += lv[i][j].first - lv[i][j-1].first;
        }
        int mn = t;
        if(lv[i].size()&1) {
            for(int j = ssize(lv[i])-1; j >= 2; j-=2) {
                t += lv[i][j].first - lv[i][j-1].first;
                t -= lv[i][j-1].first - lv[i][j-2].first;
                mn = min(mn, t);
            }
        }
        ans += mn;
    }
    cout << ans << "\n";
}
