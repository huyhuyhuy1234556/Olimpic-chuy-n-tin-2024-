#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long res = 0;
    for (int i = 0; i < n; i++) {
        if (((n - 1) & i) == i) res ^= a[i];
    }
    cout << res << "\n";
    return 0;
}
