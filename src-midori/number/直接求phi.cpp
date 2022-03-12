// primes 为预处理的素数表
ll getPhi(ll x) {
    ll phi = x, num = x;
    for (int p : primes) {
        if (p > x / p) break;
        if (x % p == 0) 
            phi = (phi / p) * (p - 1), x /= p;
        while (x % p == 0)
            x /= p;
    }
    if (x > 1)
        phi = phi / x * (x - 1);
    return phi;
}