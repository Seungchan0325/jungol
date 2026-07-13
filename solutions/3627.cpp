#include <bits/stdc++.h>
#include <queue>

using namespace std;

const int MAXN = 1010101;

int N, A[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i], A[i] -= i;

    long long ans = 0;
    priority_queue<int> pq; pq.push(A[1]); pq.push(A[1]);
    for(int i = 2; i <= N; i++) {
        pq.pop();
        ans += max(0, pq.top()-A[i]);
        pq.push(A[i]);
        pq.push(A[i]);
    }
    cout << ans << "\n";
}
