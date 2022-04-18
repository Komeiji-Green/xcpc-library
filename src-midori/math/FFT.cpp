#include<bits/stdc++.h>
#include<vector>
using namespace std;

using db = double;
using ll = long long;

int mod;

namespace FFT {
	const db pi = acos(-1.0);
	struct Comp {
		db x, y;
		Comp() { x = 0.0, y = 0.0; }
		Comp(db _x,db _y):x(_x),y(_y) {}
		Comp operator + (const Comp&rhs)const {
			return Comp(x+rhs.x, y+rhs.y);
		}
		Comp operator - (const Comp&rhs)const {
			return Comp(x-rhs.x, y-rhs.y);
		}
		Comp operator * (const Comp&rhs)const {
			return Comp(x*rhs.x-rhs.y*y, x*rhs.y+y*rhs.x);
		}
	};
	Comp conj(const Comp&rhs) {
		return Comp(rhs.x, -rhs.y);
	}
	Comp exp_i(const db &x) {
		return Comp(cos(x), sin(x));
	}

	const int L = 21, N = 1 << L;
	Comp roots[N];
	int rev[N];
	struct _init {
		_init() {
			for(int i = 0; i < N; i++) {
				rev[i] = (rev[i>>1]>>1)|((i&1)<<L-1);
			}
			roots[1] = {1, 0};
			for(int i = 1; i < L; i++) {
				db angle = 2*pi/(1<<i+1);
				for(int j = (1<<i-1); j < (1<<i); j++) {
					roots[j<<1] = roots[j];
					roots[j<<1|1] = exp_i((j*2+1-(1<<i))*angle);
				}
			}
		}
	} init;
	inline void trans(Comp &a, Comp &b, const Comp &c) {
		Comp d = b * c;
		b = a - d;
		a = a + d;
	}
	void fft(vector<Comp> &a, int n) {
		assert((n & (n - 1)) == 0);
		int zeros = __builtin_ctz(n), shift = L - zeros;
		for(int i = 0; i < n; i++) {
			if(i < (rev[i]>>shift)) {
				swap(a[i], a[rev[i]>>shift]);
			}
		}
		for(int i = 1; i < n; i <<= 1)
			for(int j = 0; j < n; j += i * 2)
				for(int k = 0; k < i; k++)
					trans(a[j+k], a[i+j+k], roots[i+k]);
	}
	
	vector<Comp> fa, fb;
	vector<int> multiply(const vector<int> &a, const vector<int> &b) {
		// 三次变两次
		int la = a.size(), lb = b.size();
		int need = la + lb - 1, n = 1 << (32 - __builtin_clz(need - 1));
		if(n > fa.size()) fa.resize(n);
		for(int i = 0; i < n; i++) {
			fa[i] = Comp(i < la ? a[i] : 0, i < lb ? b[i] : 0);
		}
		fft(fa, n);
		Comp r(0, -0.25/n);
		for(int i = 0, j = 0; i <= (n>>1); i++, j = n - i) {
			Comp x = fa[i] * fa[i], y = fa[j] * fa[j];
			if(i != j) fa[j] = (x - conj(y)) * r;
			fa[i] = (y - conj(x)) * r;
		}
		fft(fa, n);
		vector<int> c(need);
		for(int i = 0; i < need; i++) c[i]=fa[i].x+0.5;
		return c;
	}

	vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
		// 朴素三次
        int la = a.size(), lb = b.size();
        int need = la + lb - 1, n = 1 << (32 - __builtin_clz(need - 1));
        if(n > fa.size()) fa.resize(n), fb.resize(n);
        for(int i = 0; i < n; i++) {
            fa[i] = Comp(i < la ? a[i] : 0, 0);
            fb[i] = Comp(i < lb ? b[i] : 0, 0);
        }
        fft(fa, n);
        fft(fb, n);
        for(int i = 0; i < n; i++) {
            fa[i] = fa[i] * fb[i];
        }
        reverse(fa.begin() + 1, fa.begin() + n);
        fft(fa, n);
        Comp r(1.0 / n, 0);
        for(int i = 0; i < n; i++) fa[i] = fa[i] * r;
        vector<ll> c(need);
        for(int i = 0; i < need; i++) c[i]=ll(fa[i].x+0.5);
        return c;
    }

	const int M = (1 << 15) - 1;
	vector<int> multiply_mod(const vector<int> &a, const vector<int> &b, bool eq = 0) {
		// (a, b) * (c, d)
		int la = a.size(), lb = b.size();
		int need = la + lb - 1, n = need > 1 ? 1 << (32 - __builtin_clz(need - 1)) : 1;
		if(fa.size() < n) fa.resize(n);
		if(fb.size() < n) fb.resize(n);
		for(int i = 0; i < n; i++) {
			fa[i] = i < la ? Comp(a[i]>>15, a[i]&M) : Comp(0, 0);
		}
		fft(fa, n);
		if(eq) copy(fa.begin(),fa.begin()+n, fb.begin());
		else {
			for(int i = 0; i < n; i++) {
				fb[i] = i < lb ? Comp(b[i]>>15, b[i]&M) : Comp(0, 0);
			}
			fft(fb, n);
		}
		Comp r(0.5/n,0);
		for(int i = 0, j = 0; i <= (n>>1); i++, j = n - i) {
			Comp x = (fa[i]+conj(fa[j]))*fb[i]*r; // (a, 0)*(c, d)
			Comp y = (fa[i]-conj(fa[j]))*conj(fb[j])*r; // (0, b)*(c, d)
			if(i != j) {
				Comp _x = (fa[j]+conj(fa[i]))*fb[j]*r;
				Comp _y = (fa[j]-conj(fa[i]))*conj(fb[i])*r;
				fa[i] = _x, fb[i] = _y;
			}
			fa[j] = x, fb[j] = y;
		}
		fft(fa, n);
		fft(fb, n);
		vector<int> c(need);
		for(int i = 0; i < need; i++) {
			ll x = ll(fa[i].x + 0.5) % mod, y = ll(fa[i].y + 0.5) % mod;
			ll z = ll(fb[i].x + 0.5) % mod, w = ll(fb[i].y + 0.5) % mod;
			c[i] = ((x<<30) + z + (y + w << 15)) % mod;
		}
		return c;
	}
	vector<int> sqr_mod(const vector<int> &a) {
		return multiply_mod(a, a, 1);
	}
}
using FFT::multiply;
using FFT::multiply_mod;
using FFT::sqr_mod;


int main() {
	using namespace std;
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m >> mod;
	vector<int> f(n + 1), g(m + 1);
	for(auto &x : f) cin >> x;
	for(auto &x : g) cin >> x;
	vector<int> h = multiply_mod(f, g);
	for(auto &x : h) cout << x << " "; 
	cout << endl;
}
