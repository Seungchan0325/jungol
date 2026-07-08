#include <bits/stdc++.h>
#include <ios>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator + (const Point& p) const {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) const {
        return Point(x-p.x, y-p.y);
    }
    ll cross(const Point& p) const {
        return x * p.y - y * p.x;
    }
    ll cross(const Point& p, const Point& q) const {
        return (p - *this).cross(q - *this);
    }
    auto operator <=> (const Point& p) const {
        return tuple(x, y) <=> tuple(p.x, p.y);
    }
};

struct PolorComparator {
    Point o;
    PolorComparator(const Point& o = Point(0, 0)) : o(o){}
    bool operator () (const Point& p, const Point& q) const {
        if((p < o) != (q < o)) return p < q;
        return o.cross(p, q) > 0;
    }
};

tuple<vector<vector<int>>, vector<char>> find_faces(vector<Point>& vertices, vector<vector<int>>& adj)
{
    int n = vertices.size();
    vector<vector<char>> used(n);
    for(int i = 0; i < n; i++) {
        used[i].resize(adj[i].size());
        auto comp = PolorComparator(vertices[i]);
        sort(adj[i].begin(), adj[i].end(), [&](int i, int j) { return comp(vertices[i], vertices[j]); });
    }
    vector<vector<int>> faces;
    vector<char> isoutter;
    for(int i = 0; i < n; i++) {
        for(int edge_id = 0; edge_id < adj[i].size(); edge_id++) {
            if(used[i][edge_id]) continue;
            vector<int> face;
            int v = i;
            int e = edge_id;
            while(!used[v][e]) {
                used[v][e] = true;
                face.push_back(v);
                int u = adj[v][e];
                auto comp = PolorComparator(vertices[u]);
                int e1 = lower_bound(adj[u].begin(), adj[u].end(), v, [&](int i, int j){
                   return comp(vertices[i], vertices[j]);
                }) - adj[u].begin() + 1;
                if(e1 == adj[u].size()) e1 = 0;
                v = u;
                e = e1;
            }
            reverse(face.begin(), face.end());
            Point p1 = vertices[face[0]];
            __int128 sum = 0;
            for(int j = 0; j < face.size(); j++) {
                Point p2 = vertices[face[j]];
                Point p3 = vertices[face[(j+1)%face.size()]];
                sum += (p2-p1).cross(p3-p2);
            }
            faces.push_back(face);
            if(sum <= 0) {
                isoutter.push_back(true);
            } else {
                isoutter.push_back(false);
            }
        }
    }
    return {faces, isoutter};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<Point> vertices(n);
    for(auto& p : vertices) cin >> p.x >> p.y;
    int w;
    cin >> w;
    vector<pair<int, int>> e;
    vector<vector<int>> adj(n);
    for(int i = 0; i < w; i++) {
        int u, v; cin >> u >> v; u--; v--;
        e.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto [faces, isoutter] = find_faces(vertices, adj);
    vector<map<int, int>> id(n);
    for(int i = 0; i < faces.size(); i++) {
        int m = faces[i].size();
        for(int j = 0; j < m; j++) {
            id[faces[i][j]][faces[i][(j+1)%m]] = i;
        }
    }

    queue<int> q;
    vector<int> dist(faces.size(), -1);
    for(int i = 0; i < faces.size(); i++) {
        if(isoutter[i]) {
            q.push(i);
            dist[i] = 0;
        }
    }
    while(q.size()) {
        int now = q.front(); q.pop();
        int m = faces[now].size();
        for(int i = 0; i < m; i++) {
            int nxt = id[faces[now][(i+1)%m]][faces[now][i]];
            if(dist[nxt] < 0) {
                q.push(nxt);
                dist[nxt] = dist[now] + 1;
            }
        }
    }

    int ans = 0;
    for(auto [u, v] : e) {
        int i = id[u][v];
        int j = id[v][u];
        if(dist[i] == dist[j]) {
            ans++;
        }
    }
    cout << ans << "\n";
}
