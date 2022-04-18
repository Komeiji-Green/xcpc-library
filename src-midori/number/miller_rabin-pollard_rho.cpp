typedef long long ll;

// 注意在 MR 里的 fpow 模数超过 int 范围，需要开 __int128

ll mul(ll a, ll b, ll p) {
    return __int128(a) * b % p;
}

ll fpow(ll a, ll k, ll p) {
    ll res = 1; a %= p;
    for (; k; k >>= 1, a = mul(a, a, p)) {
        if (k & 1)
            res = mul(res, a, p);
    }
    return res;
}


ll randint(ll l, ll r) {
    static mt19937 eng(time(0));
    uniform_int_distribution<ll> dis(l, r);
    return dis(eng);
}

bool is_prime(ll x) {
    int s = 0; ll t = x - 1;
    if (x == 2) return true;
    if (x < 2 || !(x & 1)) return false; 
    while (!(t & 1)) {   //将x分解成(2^s)*t的样子
        s++; t >>= 1;
    }
    ll lst[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for(ll a : lst) { //随便选一个素数进行测试
        if(a >= x) break;
        ll b = fpow(a, t, x); //先算出a^t
        for (int j = 1; j <= s; ++j) { //然后进行s次平方
            ll k = mul(b, b, x);        //求b的平方
            if (k == 1 && b != 1 && b != x - 1) //用二次探测判断
                return false;
            b = k;
        }
        if (b != 1)
            return false; //用费马小定律判断
    }
    return true; //如果进行多次测试都是对的，那么x就很有可能是素数
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

// @author: Pecco
ll Pollard_Rho(ll n) {
    if (n == 4) return 2;
    if (is_prime(n)) return n;
    while (1) {
        ll c = randint(1, n - 1); // 生成随机的c
        auto f = [=](ll x) { return ((__int128)x * x + c) % n; }; // lll表示__int128，防溢出
        ll t = f(0), r = f(f(0));
        while (t != r) {
            ll d = __gcd(abs(t - r), n);
            if (d > 1)
                return d;
            t = f(t), r = f(f(r));
        }
    }
}


// 优化掉一个log
ll Pollard_Rho(ll n) {
    if (n == 4) return 2;
    if (is_prime(n)) return n;
    while (1) {
        ll c = randint(1, n - 1);
        auto f = [=](ll x) { return ((__int128)x * x + c) % n; };
        ll t = 0, r = 0, p = 1, q;
        do {
            for (int i = 0; i < 128; ++i) { // 令固定距离C=128
                t = f(t), r = f(f(r));
                if (t == r || (q = (lll)p * abs(t - r) % n) == 0) // 如果发现环，或者积即将为0，退出
                    break;
                p = q;
            }
            ll d = gcd(p, n);
            if (d > 1)
                return d;
        } while (t != r);
    }
}

vector<ll> factors;

// 将 n 进行素因子分解，factors: 存放 n 的所有不去重素因子
void getfactors(ll n) {
    if (n == 1) return;
    if (is_prime(n)) { factors.push_back(n); return; } // 如果是质因子
    ll p = n;
    while (p == n)
        p = Pollard_Rho(n);
    getfactors(n / p), getfactors(p); //递归处理
}
