#include <cassert>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    int x, y;
    Point operator + (const Point& rhs) {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) {
        return {x - rhs.x, y - rhs.y};
    }
    auto operator <=> (const Point& rhs) const {
        return tie(x, y) <=> tie(rhs.x, rhs.y);
    }
};

ll ccw(Point a, Point b, Point c)
{
    return (ll)(b.x - a.x) * (c.y - a.y) - (ll)(c.x - a.x) * (b.y - a.y);
}

int n, ans[1111][2];
Point ps[3333];

void dnc(vector<int> ids)
{
    if(ids.empty()) return;

    sort(ids.begin(), ids.end(), [](int i, int j) { return ps[i] < ps[j]; });
    vector<int> up, dw;
    for(auto i : ids) {
        while(up.size() >= 2 && ccw(ps[up.end()[-2]], ps[up.end()[-1]], ps[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(ps[dw.end()[-2]], ps[dw.end()[-1]], ps[i]) <= 0) dw.pop_back();
        up.push_back(i);
        dw.push_back(i);
    }

    int oi = -1;
    for(auto i : up) if(i <= n) oi = i;
    for(auto i : dw) if(i <= n) oi = i;
    if(oi >= 0) {
        Point o = ps[oi];
        sort(ids.begin(), ids.end(), [&](int i, int j){
            Point p = ps[i];
            Point q = ps[j];
            if((p <=> o) == 0) return true;
            if((q <=> o) == 0) return false;
            return ccw(o, p, q) > 0;
        });

        int score = 0;
        int x = -1, y = -1;
        for(int i = 0; i < ids.size(); i++) {
            if(ids[i] <= n) score += 2;
            else {
                score -= 1;
                if(x < 0 && score == 1) x = i;
                if(y < 0 && score == 0) y = i;
            }
        }

        assert(x >= 0);
        assert(y >= 0);

        ans[ids[0]][0] = ids[x];
        ans[ids[0]][1] = ids[y];

        vector<int> p1, p2, p3;
        for(int i = 1; i < x; i++) p1.push_back(ids[i]);
        for(int i = x+1; i < y; i++) p2.push_back(ids[i]);
        for(int i = y+1; i < ids.size(); i++) p3.push_back(ids[i]);
        assert(p1.size() < ids.size());
        assert(p2.size() < ids.size());
        assert(p3.size() < ids.size());
        // cout << "--- selected ---\n";
        // cout << ids[x] << " " << ids[y] << "\n";
        // for(auto i : ids) cout << i << " ";
        // cout << "\n";
        // for(auto i : p1) cout << i << " ";
        // cout << "\n";
        // for(auto i : p2) cout << i << " ";
        // cout << "\n";
        ids = {};
        dnc(p1);
        dnc(p2);
        dnc(p3);
        return;
    }

    oi = up[0];
    Point o = ps[oi];
    sort(ids.begin(), ids.end(), [&](int i, int j){
        Point p = ps[i];
        Point q = ps[j];
        if((p <=> o) == 0) return true;
        if((q <=> o) == 0) return false;
        return ccw(o, p, q) > 0;
    });

    int x = -1;
    for(int iter = 0; iter < 2; iter++) {
        int score = 0;
        for(int i = 0; i+1 < ids.size(); i++) {
            if(ids[i] <= n) score += 2;
            else {
                score -= 1;
            }
            if(score == 0) x = i;
        }
        if(x >= 0) break;
        reverse(ids.begin()+1, ids.end());
    }

    assert(x >= 0);

    vector<int> p1, p2;
    for(int i = 0; i <= x; i++) p1.push_back(ids[i]);
    for(int i = x+1; i < ids.size(); i++) p2.push_back(ids[i]);
    assert(p1.size() < ids.size());
    assert(p2.size() < ids.size());
    // cout << "--- splitted ---\n";
    // for(auto i : ids) cout << i << " ";
    // cout << "\n";
    // for(auto i : p1) cout << i << " ";
    // cout << "\n";
    // for(auto i : p2) cout << i << " ";
    // cout << "\n";
    ids = {};
    dnc(p1);
    dnc(p2);
}

int main()
{
    cin >> n;
    for(int i = 1; i <= 3 * n; i++) {
        cin >> ps[i].x >> ps[i].y;
    }

    vector<int> ids(3*n);
    iota(ids.begin(), ids.end(), 1);
    dnc(ids);

    for(int i = 1; i <= n; i++) cout << ans[i][0] - n << " " << ans[i][1] - n << "\n";
}
