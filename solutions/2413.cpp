#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    auto operator <=> (const Point& rhs) const {
        return tie(x, y) <=> tie(rhs.x, rhs.y);
    }
};

ll ccw(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main()
{
    int Q;
    cin >> Q;

    set<Point> lupper, rupper, llower, rlower;
    auto insert = [](set<Point>& upper, Point p) {
        auto it = upper.lower_bound(p);
        if(it != upper.begin() && it != upper.end() && ccw(*prev(it), p, *it) > 0) return;
        it = upper.insert(p).first;
        while(true) {
            if(next(it) == upper.end() || next(next(it)) == upper.end()) break;
            if(ccw(*it, *next(it), *next(next(it))) >= 0) upper.erase(next(it));
            else break;
        }
        while(true) {
            if(it == upper.begin() || prev(it) == upper.begin()) break;
            if(ccw(*prev(prev(it)), *prev(it), *it) >= 0) upper.erase(prev(it));
            else break;
        }
    };
    auto query = [](set<Point>& upper, Point p) {
        auto it = upper.lower_bound(p);
        if(it == upper.begin() || it == upper.end()) return false;
        return ccw(*prev(it), p, *it) >= 0;
    };
    while(Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if(t == 1) {
            insert(lupper, {x, y});
            insert(rupper, {-x, y});
            insert(llower, {x, -y});
            insert(rlower, {-x, -y});

            // cout << "--- lupper ---\n";
            // for(auto p : lupper) cout << p.x << " " << p.y << "\n";
            // cout << "--- rupper ---\n";
            // for(auto p : rupper) cout << -p.x << " " << p.y << "\n";
            // cout << "--- llower ---\n";
            // for(auto p : llower) cout << p.x << " " << -p.y << "\n";
            // cout << "--- rlower ---\n";
            // for(auto p : rlower) cout << -p.x << " " << -p.y << "\n";
        } else {
            bool ok = query(lupper, {x, y});
            ok &= query(rupper, {-x, y});
            ok &= query(llower, {x, -y});
            ok &= query(rlower, {-x, -y});
            if(ok) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}
