#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3030;

int N, M, W, P[MAXN], L[MAXN], R[MAXN], H[MAXN], K[MAXN], DP[MAXN][MAXN<<1];
vector<int> here[MAXN<<1];

bool doesOverlap(int i, int j)
{
    if(R[j] <= L[i] || R[i] <= L[j]) return false;
    return P[i] == P[j] || H[i] + H[j] > W;
}

int main()
{
    cin >> N >> W;
    for(int i = 1; i <= N; i++) cin >> P[i] >> L[i] >> R[i] >> H[i] >> K[i];

    vector<int> xs;
    for(int i = 1; i <= N; i++) {
        xs.push_back(L[i]);
        xs.push_back(R[i]);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    M = xs.size();
    for(int i = 1; i <= N; i++) {
        L[i] = lower_bound(xs.begin(), xs.end(), L[i]) - xs.begin() + 1;
        R[i] = lower_bound(xs.begin(), xs.end(), R[i]) - xs.begin() + 1;
    }

    for(int i = N; i >= 1; i--) {
        for(int j = 1; j < i; j++) {
            if(tie(L[j], R[j], P[j]) > tie(L[j+1], R[j+1], P[j+1])) {
                swap(P[j], P[j+1]);
                swap(L[j], L[j+1]);
                swap(R[j], R[j+1]);
                swap(H[j], H[j+1]);
                swap(K[j], K[j+1]);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        here[L[i]].push_back(i);
    }

    int mx = 0;
    for(int i = 1; i <= N; i++) {
        DP[i][0] = K[i];
        for(int j = 1; j <= M; j++) {
            DP[i][j] = max(DP[i][j], DP[i][j-1]);
            for(int k : here[j]) {
                if(doesOverlap(i, k)) continue;
                if(R[k] > R[i]) DP[k][R[i]] = max(DP[k][R[i]], DP[i][j] + K[k]);
                else            DP[i][R[k]] = max(DP[i][R[k]], DP[i][j] + K[k]);
            }
            mx = max(mx, DP[i][j]);
        }
    }
    // cout << format("                      ");
    // for(int j = 0; j <= M; j++) cout << format("{:3} ", j);
    // cout << "\n";
    // for(int i = 1; i <= N; i++) {
    //     cout << format("{:3} {:3} {:3} {:3} {:3} : ", P[i], L[i], R[i], H[i], K[i]);
    //     for(int j = 0; j <= M; j++) {
    //         cout << format("{:3} ", DP[i][j]);
    //     }
    //     cout << "\n";
    // }
    cout << mx << "\n";
}
