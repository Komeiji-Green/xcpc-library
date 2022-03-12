// 预处理组合数
const int N = 2e5 + 7;
const ll mod = 998244353;

ll fac[N], ifac[N];
void init() {
    fac[0] = 1;
    for (int i = 1; i < N; ++i) fac[i] = i * fac[i-1] % mod;
    ifac[N - 1] = fpow(fac[N - 1], mod - 2);
    for (int i = N - 1; i; --i) ifac[i - 1] = i * ifac[i] % mod;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (fac[n] * ifac[k] % mod) * ifac[n - k] % mod;
} 

// 线性求逆元，注意有效的 i < mod
ll inv[maxn];
void init() { 
    inv[0] = 0, inv[1] = 1;
    for (int i = 2; i < N; ++i) 
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}

// 快速幂
ll fpow(ll a, ll k = mod - 2, ll p = mod) {
    ll res = 1; a %= p;
    for (; k; k >>= 1, a = a * a % p) {
        if (k & 1) 
            res = res * a % p;
    }
    return res;
}

