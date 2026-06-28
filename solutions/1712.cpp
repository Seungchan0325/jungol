#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5050;

int N, M, group[MAXN], groups, num[MAXN];
bitset<MAXN> G[MAXN];
vector<int> ch[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        G[u][v] = G[v][u] = true;
    }
    for(int i = 1; i <= N; i++) G[i][i] = true;

    for(int i = 1; i <= N; i++) {
        if(group[i]) continue;
        group[i] = i;
        groups++;
        for(int j = 1; j <= N; j++) {
            if(G[i] == G[j]) group[j] = i;
        }
    }

    for(int i = 1; i <= N; i++) {
        if(i != group[i]) continue;
        for(int j = 1; j <= N; j++) {
            if(G[i][j] && group[j] > i) {
                ch[i].push_back(group[j]);
            }
        }
        sort(ch[i].begin(), ch[i].end());
        ch[i].erase(unique(ch[i].begin(), ch[i].end()), ch[i].end());
    }

    int S = N;
    int pv = N;
    S += groups-1;
    cout << S << "\n";
    for(int i = 1; i <= N; i++) {
        if(group[i] != i) continue;
        num[i] = ++pv;
        for(int j = 1; j <= N; j++) {
            if(group[j] == i) {
                cout << num[i] << " " << j << "\n";
            }
        }
    }
    for(int i = 1; i <= N; i++) {
        if(group[i] != i) continue;
        for(auto c : ch[i]) {
            cout << num[i] << " " << num[c] << "\n";
        }
    }
}
