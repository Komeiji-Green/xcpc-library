// 得到 p 的原根
ll generator(ll p) {
    static ll rec, ans;
    if (p == rec)
        return ans;
    rec = p;
    vector<ll> fact;
    ll phi = p - 1, n = phi;
    for (ll i = 2; 1ll * i * i <= n; ++i) {
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back(n);
    for (ll res = 2; res <= p; ++res) {
        bool ok = 1;
        for (ll factor : fact) {
            if (fpow(res, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok)
            return ans = res;
    }
    return ans = -1;
}