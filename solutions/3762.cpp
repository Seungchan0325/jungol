#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 50505;

bool used[MAXN];
ll N, K, M, P[MAXN], C[MAXN];

int main()
{
    cin >> N >> K >> M;
    for(int i = 0; i < N; i++) cin >> P[i] >> C[i];
    priority_queue<pair<ll, int>> a, b, c;
    for(int i = 0; i < N; i++) {
        a.push({-P[i], i});
        b.push({-C[i], i});
    }
    int num = 0;
    ll cost = 0;
    for(int i = 0; i < K; i++) {
        auto [_, j] = b.top(); b.pop();
        c.push({C[j]-P[j], j});
        cost += C[j];
        if(cost > M) break;
        num++;
        used[j] = true;
    }
    while(cost < M && num < N) {
        while(a.size() && used[a.top().second]) a.pop();
        while(b.size() && used[b.top().second]) b.pop();
        auto [aa, i] = a.top(); aa = -aa;
        auto [bb, j] = b.top(); bb = -bb;
        auto [cc, k] = c.top(); cc = -cc;
        if(aa < bb+cc) {
            used[i] = true;
            cost += aa;
            a.pop();
        } else {
            used[j] = true;
            cost += bb+cc;
            b.pop();
            c.pop();
            c.push({C[j]-P[j], j});
        }

        if(cost > M) break;
        num++;
    }

    cout << num << "\n";
}
