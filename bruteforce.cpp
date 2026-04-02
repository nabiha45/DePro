#include <bits/stdc++.h>
using namespace std;

// For each test case, we do a TSP-like DP over subsets of required points.
// State: dp[mask][last] = minimum distance to start at s and visit the set "mask",
// ending at point "last" (last is an index in 0..n-1; we keep s as a separate start).
// Transition: add any unvisited point j and pay |x[last] - x[j]| (or |s - x[j]| if starting).

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T))
        return 0;
    while (T--)
    {
        int n, s;
        cin >> n >> s;
        vector<int> x(n);
        for (int i = 0; i < n; ++i)
            cin >> x[i];

        // Bitmask DP: 2^n states, n endpoints
        const long long INF = (1LL << 60);
        int Nmask = 1 << n;
        vector<vector<long long>> dp(Nmask, vector<long long>(n, INF));

        // Initialize: first move goes from s to any single required point i
        for (int i = 0; i < n; ++i)
        {
            int m = 1 << i;
            dp[m][i] = llabs((long long)s - x[i]);
        }

        // Transitions
        for (int mask = 0; mask < Nmask; ++mask)
        {
            for (int last = 0; last < n; ++last)
            {
                if (dp[mask][last] == INF)
                    continue;
                for (int nxt = 0; nxt < n; ++nxt)
                {
                    if (mask & (1 << nxt))
                        continue;
                    int nmask = mask | (1 << nxt);
                    long long cost = dp[mask][last] + llabs((long long)x[last] - x[nxt]);
                    if (cost < dp[nmask][nxt])
                        dp[nmask][nxt] = cost;
                }
            }
        }

        // Answer: any tour that visits all points (no need to return anywhere)
        long long ans = INF;
        int full = Nmask - 1;
        for (int last = 0; last < n; ++last)
            ans = min(ans, dp[full][last]);

        cout << ans << "\n";
    }
    return 0;
}
