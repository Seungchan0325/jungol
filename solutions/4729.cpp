#include <bits/stdc++.h>
#include <functional>

using namespace std;

using ll = long long;

int N, K;
ll A[4];

int main()
{
    cin >> N >> K;
    cin >> A[0] >> A[1] >> A[2] >> A[3];
    vector<ll> v[4] = {};
    for(int i = 0; i < N; i++) {
        char t; ll u;
        cin >> t >> u;
        v[t-'A'].push_back(u);
    }
    for(int i = 0; i < 4; i++) sort(v[i].begin(), v[i].end(), greater<>());
    int p[4] = {};
    for(int i = 0; i < K; i++) {
        double mx = 1e9;
        int mxi = -1;
        for(int j = 0; j < 4; j++) {
            if(p[j] < v[j].size()) {
                if(v[j][p[j]]/(double)A[j] > mx || mxi < 0){
                    mx = v[j][p[j]]/(double)A[j];
                    mxi = j;
                }
            }
        }
        cout << format("{} {}\n", (char)('A'+mxi), v[mxi][p[mxi]]);
        A[mxi] += v[mxi][p[mxi]];
        p[mxi]++;
    }
}
