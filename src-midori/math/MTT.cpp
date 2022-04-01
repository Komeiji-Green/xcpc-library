using db = double;
using ll = long long;

int mod;

// init!
namespace FFT {
	const db pi = acos(-1.0);
	struct Comp {
		db x, y;
		Comp() {}
		Comp(db _x, db _y): x(_x), y(_y) {}
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
	const Comp I(0, 1);
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
	void fft(Comp* a, int n, int op = 1) {
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
		Comp r(1.0 / n, 0);
		if(op == -1) {
			reverse(a + 1, a + n);
			for(int i = 0; i < n; i++)
				a[i] = a[i] * r;
		}
	}
	void dfft(Comp *a, Comp *b, int len) {
		for(int i = 0; i < len; ++i)
			a[i] = a[i] + I * b[i];
		fft(a, len, 1);
		for(int i = 0; i < len; ++i)
			b[i] = conj(a[i ? len - i : 0]);
		Comp r(0.5, 0);
		for(int i = 0; i < len; ++i) {
			Comp p = a[i], q = b[i];
			a[i] = (p + q) * r;
			b[i] = (q - p) * r * I;
		}
	} 
	const int M = (1 << 15) - 1;
	vector<int> multiply_mod(const vector<int>& a, const vector<int>& b, bool eq = 0) {
		static Comp a0[N], a1[N], b0[N], b1[N];
		// (a0, a1) * (b0, b1)
		int la = a.size(), lb = b.size();
		int need = la + lb - 1, len = need > 1 ? 1 << (32 - __builtin_clz(need - 1)) : 1;
		for(int i = 0; i < len; i++) {
			a0[i] = Comp(i < la ? (a[i] >> 15) : 0, 0);
			a1[i] = Comp(i < la ? (a[i] & M) : 0, 0);
		}
		for(int i = 0; i < len; i++) {
			b0[i] = Comp(i < lb ? (b[i] >> 15) : 0, 0);
			b1[i] = Comp(i < lb ? (b[i] & M) : 0, 0);
		}
		dfft(a0, a1, len);
		dfft(b0, b1, len);
		vector<Comp> fa(len), fb(len);
		for(int i = 0; i < len; ++i) {
			fa[i] = a0[i] * b0[i] + I * a1[i] * b0[i];
			fb[i] = a0[i] * b1[i] + I * a1[i] * b1[i];
		}
		fft(fa.data(), len, -1);
		fft(fb.data(), len, -1);

		vector<int> res(need);
		for(int i = 0; i < need; i++) {
			ll x = ll(fa[i].x + 0.5) % mod, y = ll(fa[i].y + 0.5) % mod;
			ll z = ll(fb[i].x + 0.5) % mod, w = ll(fb[i].y + 0.5) % mod;
			res[i] = ((x<<30) + (y + z << 15) + w) % mod;
		}
		return res;
	}
}
using FFT::multiply_mod;

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
