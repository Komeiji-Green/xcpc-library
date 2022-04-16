#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// -p: 素因子
// -l: 次数
// return: 本质不同素因子个数
// 1-base
int Fact(int x, int *p, int *l);

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

void exgcd(ll a, ll b, ll &x, ll &y, ll c = 1);

// x === a1 (mod b1), x === a2 (mod b2)
// 合法性检查: 返回 -1 则为无解
pair<ll, ll> excrt(ll a1, ll b1, ll a2, ll b2);


// --------------------------


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

const int N = 107;

int ps[N], l[N];

ll exlucas(ll n, ll m, ll P) {
    int num = Fact(P, ps, l); // 素因子分解，见素因子分解.cpp

    ll res = 0, mo = 1;
    for (int i = 1; i <= num; ++i) {
        ll pk = 1;
        for (int j = 0; j < l[i]; ++j) {
            pk *= ps[i];
        }

        ll x = C_pk(n, m, ps[i], pk);
        pair<ll, ll> pr = excrt(x, pk, res, mo);

        mo = pr.second;
        res = pr.first;
    }

    return res % P;
}

int main() {
    ll n, m, p; cin >> n >> m >> p;
    ll ans = exlucas(n, m, p);

    cout << ans << endl;
}