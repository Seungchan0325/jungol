#include <bits/stdc++.h>

using namespace std;

#define int long long

using uint = unsigned;

vector<tuple<int, int, uint>> lefs;
vector<int> rigs[1<<10][200];

void rdfs(int i, int sum, int num, uint ws, uint org)
{
    if(i == 6) {
        rigs[org][sum].push_back(num);
        return;
    }

    rdfs(i+1, sum, num*10, ws, org);
    for(int w = 1; w <= 9; w++) {
        if(~ws&(1<<w)) continue;
        rdfs(i+1, sum+w*i, num*10+w, ws^(1<<w), org);
    }
}

void dfs(int i, int sum, int num, uint ws)
{
    if(i == 0) {
        lefs.push_back({num, sum, ws});
        return;
    }

    dfs(i-1, sum, num*10, ws);
    for(int w = 1; w <= 9; w++) {
        if(~ws&(1<<w)) continue;
        dfs(i-1, sum+w*i, num*10+w, ws^(1<<w));
    }
}

signed main()
{
    int n; cin >> n;
    uint ws = 0;
    for(int i = 0; i < n; i++) {
        int w; cin >> w;
        ws |= 1<<w;
    }
    int k; cin >> k;

    dfs(5, 0, 0, ws);
    sort(lefs.begin(), lefs.end());

    for(int i = 0; i < (1<<10); i++) {
        rdfs(1, 0, 0, i, i);
    }

    for(int i = 0; i < (1<<10); i++) {
        for(int j = 0; j < 200; j++) {
            sort(rigs[i][j].begin(), rigs[i][j].end());
        }
    }

    // int iter = 1;
    // for(auto [num, sum, ws] : lefs) {
    //     for(auto num2 : rigs[ws][sum]) {
    //         cout << iter << ":" << (long long)(num * 100000) + num2 << "\n";
    //         iter++;
    //     }
    // }

    long long last = 0;
    for(auto [num, sum, ws] : lefs) {
        if(rigs[ws][sum].size()) last = (long long)(num * 100000) + rigs[ws][sum].back();
        if(k < rigs[ws][sum].size()) {
            cout << (long long)(num * 100000) + rigs[ws][sum][k];
            return 0;
        } else {
            k -= rigs[ws][sum].size();
        }
    }

    cout << last;
}
