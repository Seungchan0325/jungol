#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for(auto& [a, b] : v) cin >> a >> b;
    sort(v.begin(), v.end(), [](pair<int, int> x, pair<int, int> y) {
        if(x.first == 0) return false;
        if(y.first == 0) return true;
        if(x.second == 0 && y.second == 0) return x.first < y.first;
        return y.first * x.second < x.first * y.second;
    });

    long long ans = 0;
    for(auto [a, b] : v) {
        ans += a * ans + b;
        ans %= 40000;
    }
    cout << ans << "\n";
}
