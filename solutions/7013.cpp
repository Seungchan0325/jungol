#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int MAXN = 2020;
const int MAXQ = 101010;

struct Rect {
    int t, b, w;
};

struct Query {
    int x, y, id;
};

int N, M, Q, sum[MAXN][MAXN], len[MAXN][MAXN], ans[MAXQ];
char campsite[MAXN][MAXN];
vector<Rect> rects[4*MAXN];

void upd(int l, int r, Rect rect, int s, int e, int idx)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        rects[idx].push_back(rect);
        return;
    }
    int m = (s + e) / 2;
    upd(l, r, rect, s, m, 2*idx);
    upd(l, r, rect, m+1, e, 2*idx+1);
}

void dnc(int l, int r, vector<Query> pos, int idx)
{
    if(pos.empty()) return;
    int m = (l+r)/2;
    vector<Query> lef, rig;
    for(const auto& q : pos) {
        if(q.y <= m) lef.push_back(q);
        else rig.push_back(q);
    }

    if(l != r) {
        dnc(l, m, lef, 2*idx);
        dnc(m+1, r, rig, 2*idx+1);
    }

    vector<Rect> start, end;
    start = end = rects[idx];
    sort(start.begin(), start.end(), [](Rect a, Rect b) { return a.t < b.t; });
    sort(end.begin(), end.end(), [](Rect a, Rect b) { return a.b < b.b; });
    int p = 0;
    int q = 0;
    priority_queue<int> pq, epq;
    for(auto point : pos) {
        while(p < start.size() && start[p].t <= point.x) {
            pq.push(start[p].w);
            p++;
        }
        while(q < end.size() && end[q].b < point.x) {
            epq.push(end[q].w);
            q++;
        }
        while(pq.size() && epq.size() && pq.top() == epq.top()) {
            pq.pop(); epq.pop();
        }
        if(pq.size()) ans[point.id] = max(ans[point.id], pq.top());
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> campsite[i][j];
            sum[i][j] = campsite[i][j] == '#' ? 1 : 0;
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(campsite[i][j] == '#') continue;
            int lo = 1;
            int hi = min(i, j) + 1;
            while(lo + 1 < hi) {
                int mid = (lo+hi)/2;
                int num = sum[i][j] - sum[i-mid][j] - sum[i][j-mid] + sum[i-mid][j-mid];
                if(num) hi = mid;
                else lo = mid;
            }
            len[i][j] = lo;
        }
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(campsite[i][j] == '#') continue;
            if(len[i+1][j] >= len[i][j] + 1) continue;
            if(len[i][j+1] >= len[i][j] + 1) continue;
            Rect rect = {i-len[i][j]+1, i, len[i][j]};
            upd(j-len[i][j]+1, j, rect, 1, M, 1);
        }
    }

    vector<Query> qs;

    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        int x, y;
        cin >> x >> y;
        qs.push_back({x, y, i});
    }

    sort(qs.begin(), qs.end(), [](Query p, Query q) { return p.x < q.x; });
    dnc(1, M, qs, 1);

    for(int i = 1; i <= Q; i++) cout << (long long)ans[i] * ans[i] << "\n";
}
