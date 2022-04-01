typedef long long ll;

ll k;

// 约瑟夫环
int main() {
    int T;
    cin >> T;
    ll n, m;
    for (int cas = 1; cas <= T; ++cas) {
        scanf("%lld %lld %lld", &n, &m, &k);
        ll res = (k-1) % (n-m+1);
        if (k == 1) res = (m - 1) % n;
        else for (ll i = n - m + 1, j, t; i < n; i = j) {
            if (i < k) {
                j = i + 1;
                res = (res + k) % j;
            } else {
                j = i + i / (k - 1);
                if (j > n) j = n;
                t = j - i;
                res -= j - t * k;
                if (res < 0) res += j;
                else res += res / (k - 1);
            }
        }
        printf("Case #%d: %lld\n", cas, res + 1);
    }
}