#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 1555;

int N;
ll sum, fenwick[MAXN][MAXN];

void upd(int x, int y, int v)
{
    while(y <= N) {
        fenwick[x][y] += v;
        y += y & -y;
    }
}

ll getDP(int x, int y)
{
    ll res = 0;
    while(y > 0) {
        res += fenwick[x][y];
        y -= y & -y;
    }
    return res;
}

void addDP(int i, int l, int r, ll delta)
{
    sum += delta * (r - l + 1);
    upd(i, l, delta);
    upd(i, r+1, -delta);
}

bool is_right_child(int i, int j)
{
    return j < N && getDP(i, j) >= getDP(i-1, j+1);
}

bool is_down_child(int i, int j)
{
    return i < N && getDP(i, j) >= getDP(i+1, j-1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            int cost;
            cin >> cost;
            addDP(i, j, j, max(getDP(i-1, j), getDP(i, j-1)) + cost);
        }
    }

    cout << sum << "\n";

    for(int iter = 0; iter < N; iter++) {
        char UD;
        int i, j;
        cin >> UD >> i >> j;

        int l = j;
        int r = j;
        if(UD == 'U') {
            while(i <= N && l <= r) {
                while(r < N && getDP(i, r) >= getDP(i-1, r+1)) r++;
                addDP(i, l, r, 1);
                while(l <= r && !(getDP(i, l) > getDP(i+1, l-1))) l++;
                i++;
            }
        } else {
            while(i <= N && l <= r) {
                while(r < N && getDP(i, r) > getDP(i-1, r+1)) r++;
                addDP(i, l, r, -1);
                while(l <= r && !(getDP(i, l) >= getDP(i+1, l-1))) l++;
                i++;
            }
        }

        cout << sum << "\n";
    }
}
