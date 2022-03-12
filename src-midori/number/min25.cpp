using ll = long long;
using i128 = __int128;
//using i128 = int64_t;

const ll mod = 998244353;

namespace min25 {
	const int N = 1e6 + 10;
    ll po[40][N];
    inline ll fpow(ll e, ll k) {
        return po[e][k];
    }
    void precalc() {
        for(int e = 0; e < 40; ++e) {
            po[e][0] = 1;
            for(int i = 1; i < N; i++)
                po[e][i] = e * po[e][i - 1] % mod; 
        }
    }
	ll n;
	int B;
	int _id[N * 2];
    inline int id(ll x) {
		return x <= B ? x : n / x + B;
	}
	inline int Id(ll x) {
		return _id[id(x)];
	}
	// f(p) = p - 1 = fh(p) - fg(p);
	inline ll fg(ll x) {
        // assert(x <= sqrt(n));
		return 1;
	}
	inline ll fh(ll x) {
        // assert(x <= sqrt(n));
		return x;
	}
	// \sum_{i=2}^n fg(i)
	inline ll sg(ll x) {
		return (x - 1) % mod;
	}
	// \sum_{i=2}^n fh(i)
	inline ll sh(ll x) {
		return ((i128) x * (x + 1) / 2 + mod - 1) % mod;
	}
	// f(p^e)
	inline ll f(ll p, ll e) {
		//return (pe - pe / p) % mod;
        return (p + (mod - 2) * fpow(e, p)) % mod;
	}
	bitset<N> np;
    ll p[N>>2], pn;
	ll pg[N>>2], ph[N>>2];
	void sieve(ll sz) {
		for(int i = 2; i <= sz; i++) {
			if(!np[i]) {
				p[++pn] = i;
				pg[pn] = (pg[pn - 1] + fg(i)) % mod;
				ph[pn] = (ph[pn - 1] + fh(i)) % mod;
			}
			for(int j = 1; j <= pn && i * p[j] <= sz; j++) {
				np[i * p[j]] = 1;
				if(i % p[j] == 0) {
					break;
				}
			}
		}
	}
	ll m;
	ll g[N * 2], h[N * 2];
	ll w[N * 2];

	void compress() {
		for (int i = 1; i <= m; i++) {
			g[i] = (h[i] + mod - g[i] + mod - g[i]) % mod;
		}
		for (int i = 1; i <= pn; i++) {
			pg[i] = (ph[i] + mod - pg[i] + mod - pg[i]) % mod;
		}
	}

    ll dfs_F(int k, ll n) {
        if (n < p[k] || n <= 1) return 0;
        ll res = g[Id(n)] + mod - pg[k - 1], pw2;
        for (int i = k; i <= pn && (pw2 = (ll) p[i] * p[i]) <= n; ++i) {
            ll pw = p[i];
            for (int c = 1; pw2 <= n; ++c, pw = pw2, pw2 *= p[i])
                res = (res + ((ll) f(p[i], c) * dfs_F(i + 1, n / pw) + f(p[i], c + 1))) % mod;
        }
        return res;
    }

	void init(ll _n) {
		n = _n;
		B = sqrt(n) + 100;
        pn = 0;
		sieve(B);
		m = 0;
		for(ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			ll t = n / i;
			_id[id(t)] = ++m;
			w[m] = t;
			g[m] = sg(t);
			h[m] = sh(t);
            //printf("id: %lld, w: %lld, g: %lld, h: %lld\n", m, t, g[m], h[m]);
		}
		for (int j = 1; j <= pn; j++) {
			ll z = (ll) p[j] * p[j];
			for(int i = 1; i <= m && z <= w[i]; i++) {
				int k = Id(w[i] / p[j]);
				g[i] = (g[i] + (ll) (mod - fg(p[j])) * (g[k] - pg[j - 1] + mod)) % mod;
				h[i] = (h[i] + (ll) (mod - fh(p[j])) * (h[k] - ph[j - 1] + mod)) % mod;
			}
		}
		compress();

        /* 递推 min25
		for(int j = pn; j > 0; j--) {
			ll z = (ll) p[j] * p[j];
			for(int i = 1; i <= m && z <= w[i]; i++) {
				ll pe = p[j];
				for(int e = 1; pe * p[j] <= w[i]; e++, pe *= p[j]) {
					g[i] = (g[i] + (ll) f(p[j], e) * (g[Id(w[i] / pe)] - pg[j] + mod) + f(p[j], e + 1)) % mod;
				}
			}
		} */
	}
	ll get(ll x) { // x == n / i
		if(x < 1) return 0;
        return (dfs_F(1, x) + 1) % mod;
	}
	ll get(ll l, ll r) {
		return get(r) - get(l - 1);
	}
}

void Solve() {
    long long n;
    scanf("%lld", &n);
    min25::init(n);
    long long res = min25::get(n);
    printf("%lld\n", res);
}

int main() {
    min25::precalc();
    int T;
    scanf("%d", &T);
    while(T--) {
        Solve();
    }
}