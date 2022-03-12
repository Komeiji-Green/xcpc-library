// 卢卡斯定理, 要求 p 为素数
ll lucas(ll n, ll m, ll p) {
    if (!m) return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}