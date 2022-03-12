// 扩展卢卡斯定理

// 扩欧求逆元
ll INV(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

// 递归求解(n! / px) mod pk
ll F(ll n, ll p, ll pk) {
    if (n == 0) return 1;
    ll rou = 1; // 循环节
    ll rem = 1; // 余项
    for (ll i = 1; i <= pk; ++i) {
        if (i % p)
            rou = rou * i % pk;
    }
    rou = fpow(rou, n / pk, pk);
    for (ll i = pk * (n / pk); i <= n; ++i) {
        if (i % p)
            rem = rem * (i % pk) % pk; // 小心i炸int
    }
    return F(n / p, p, pk) * rou % pk * rem % pk;
}

// 素数p在n!中的次数
ll G(ll n, ll p) {
    if (n < p) return 0;
    return G(n / p, p) + (n / p);
}

ll C_pk(ll n, ll m, ll p, ll pk) {
    ll fz = F(n, p, pk), fm1 = INV(F(m, p, pk), pk),
       fm2 = INV(F(n - m, p, pk), pk);
    ll mi = fpow(p, G(n, p) - G(m, p) - G(n - m, p), pk);
    return fz * fm1 % pk * fm2 % pk * mi % pk;
}

ll exlucas(ll n, ll m, ll P) {
    Fact(P); // 素因子分解，见素因子分解.cpp
    for (int i = 1; i <= cnt2; ++i) {
        ll pk = 1;
        for (int j = 0; j < l[i]; ++j) {
            pk *= p[i];
        }
        bi[i] = pk, ai[i] = C_pk(n, m, p[i], pk);
    }
    return excrt(cnt2) % P;
}