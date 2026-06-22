#include <bits/stdc++.h>

using namespace std;

const int MAXS = 1050;

int S;
int tree[MAXS][MAXS];

void update(int x, int y, int v)
{
    for(int i = x; i <= S; i += i & -i) {
        for(int j = y; j <= S; j += j & -j) {
            tree[i][j] += v;
        }
    }
}

int query(int x, int y)
{
    int res = 0;
    for(int i = x; i > 0; i -= i & -i) {
        for(int j = y; j > 0; j -= j & -j) {
            res += tree[i][j];
        }
    }
    return res;
}

int main()
{
    while(true) {
        int op; cin >> op;

        if(op == 0) {
            cin >> S;
        } else if(op == 1) {
            int x, y, a;
            cin >> x >> y >> a;
            x++; y++;
            update(x, y, a);
        } else if(op == 2) {
            int l, b, r, t;
            cin >> l >> b >> r >> t;
            l++; b++; r++; t++;
            int ans = query(r, t) - query(l-1, t) - query(r, b-1) + query(l-1, b-1);
            cout << ans << "\n";
        } else if(op == 3) {
            break;
        }
    }
}
