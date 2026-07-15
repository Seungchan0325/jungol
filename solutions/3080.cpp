    #include <bits/stdc++.h>

    using namespace std;

    #define int long long

    const int MAXN = 3030;

    int N, M, S, E, T, sum[MAXN][MAXN], deny[MAXN], p[MAXN];
    pair<int, int> top[MAXN][3];
    deque<pair<int, int>> dq[MAXN];
    int dp[MAXN][MAXN];

    signed main()
    {
        cin >> N >> M >> S >> E >> T;
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= M; j++)
                cin >> sum[i][j];
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= M; j++)
                sum[i][j] += sum[i][j-1];
        for(int i = 1; i <= N; i++) cin >> deny[i];

        for(int j = 1; j <= M; j++) {
            top[j][0] = top[j][1] = top[j][2] = {1e18, -1};
            for(int i = 1; i <= N; i++) {
                dp[i][j] = 1e18;
                while(p[i] <= j-S || (j == M && p[i] < M)) {
                    int cand = -sum[i][p[i]];
                    for(int x = 0; x < 3; x++) {
                        if(top[p[i]][x].second == i || top[p[i]][x].second == deny[i]) continue;
                        cand += top[p[i]][x].first;
                        break;
                    }
                    while(dq[i].size() && dq[i].back().first >= cand) {
                        dq[i].pop_back();
                    }
                    dq[i].push_back({cand, p[i]});
                    p[i]++;
                }
                while(dq[i].size() && dq[i].front().second < j-E) dq[i].pop_front();
                if(dq[i].size())
                    dp[i][j] = dq[i].front().first + T + sum[i][j];

                if(top[j][0] > pair(dp[i][j], i)) {
                    top[j][2] = top[j][1];
                    top[j][1] = top[j][0];
                    top[j][0] = pair(dp[i][j], i);
                } else if(top[j][1] > pair(dp[i][j], i)) {
                    top[j][2] = top[j][1];
                    top[j][1] = pair(dp[i][j], i);
                } else if(top[j][2] > pair(dp[i][j], i)) {
                    top[j][2] = pair(dp[i][j], i);
                }
            }
        }

        int ans = 1e18;
        for(int i = 1; i <= N; i++) ans = min(ans, dp[i][M]);
        cout << ans - T<< "\n";
    }
