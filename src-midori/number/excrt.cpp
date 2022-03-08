using ll = long long;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// x === a1 (mod b1), x === a2 (mod b2)
// 合法性检查：返回 -1 则为无解
pair<ll, ll> excrt(ll a1, ll b1, ll a2, ll b2) {
    ll g = gcd(b1, b2);
    ll lcm = (b1 / g) * b2;

    if ((a1 - a2) % g) return {-1, -1};

    i128 x, y;
    exgcd(b1, b2, x, y, a1 - a2);
    ll res = (a1 - b1 * x) % lcm;
    if (res < 0) res += lcm;
    return {res, lcm};
}