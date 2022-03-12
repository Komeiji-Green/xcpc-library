// mul 表示慢速乘
ll crt(ll a1, ll p, ll a2, ll q) {
    ll ip = fpow(p, q-2, q);
    ll iq = fpow(q, p-2, p);
    ll n = p * q;
    return (mul(mul(a1, q, n), iq, n) + mul(mul(a2, p, n), ip, n)) % n;
}