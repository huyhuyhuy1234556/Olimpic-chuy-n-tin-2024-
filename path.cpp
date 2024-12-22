#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long modPow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }
    return res;
}

long long comb(int n, int k, const vector<long long>& fact, const vector<long long>& invFact) {
    if (k > n || k < 0) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

long long solve(int r, int c, vector<pair<int, int>>& lock, const vector<long long>& fact, const vector<long long>& invFact) {
    lock.emplace_back(r, c);
    sort(lock.begin(), lock.end());
    vector<long long> dp(lock.size(), 0);

    for (int i = 0; i < lock.size(); ++i) {
        int x = lock[i].first, y = lock[i].second;
        dp[i] = comb(x + y - 2, x - 1, fact, invFact);

        for (int j = 0; j < i; ++j) {
            int px = lock[j].first, py = lock[j].second;
            if (px <= x && py <= y) {
                long long sub_paths = dp[j] * comb(x - px + y - py, x - px, fact, invFact) % MOD;
                dp[i] = (dp[i] - sub_paths + MOD) % MOD;
            }
        }
    }

    return dp.back();
}

int main() {
    int r, c, m;
    cin >> r >> c >> m;

    int maxFact = r + c;
    vector<long long> fact(maxFact + 1, 1), invFact(maxFact + 1, 1);

    for (int i = 2; i <= maxFact; ++i)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[maxFact] = modPow(fact[maxFact], MOD - 2);
    for (int i = maxFact - 1; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;

    set<pair<int, int>> uniqueLocks;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        if (x <= r && y <= c)
            uniqueLocks.insert({x, y});
    }

    vector<pair<int, int>> lock(uniqueLocks.begin(), uniqueLocks.end());

    cout << solve(r, c, lock, fact, invFact) << endl;
    return 0;
}
