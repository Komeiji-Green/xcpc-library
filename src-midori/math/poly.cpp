#include <bits/stdc++.h>

using ll = unsigned long long;
using Int = unsigned;

namespace Polynomial {

using Poly = std::vector<Int>;
constexpr Int P(998244353), G(3);
inline void inc(Int &x, Int y, Int mod = P) { 
    (x += y) >= mod ? x -= mod : 0; 
}

inline Int fpow(Int x, Int k = P - 2, Int mod = P) {
    Int r = 1;
    for (; k; k >>= 1, x = (ll) x * x % mod)
        if (k & 1) r = (ll) r * x % mod;
    return r;
}

const int MAXW = 1 << 22;
Int w[MAXW];
struct omegaGen {
    omegaGen() {
        Int x = fpow(G, (P - 1) / MAXW);
        for(int i = MAXW >> 1; i; i >>= 1) {
            w[i] = 1;
            for(int j = 1; j < i; ++j)
                w[i + j] = (ll) w[i + j - 1] * x % P; 
            x = (ll) x * x % P;
        }
    }
} gen;

Poly &operator *= (Poly &a, Int b) { 
    for(auto &x : a) 
        x = (ll) x * b % P; 
    return a; 
}
Poly operator * (Poly a, Int b) { return a *= b; }
Poly operator * (Int a, Poly b) { return b * a; }
Poly &operator /= (Poly &a, Int b) { return a *= fpow(b); }
Poly operator / (Poly a, Int b) { return a /= b; }
Poly &operator += (Poly &a, Poly b) {
    a.resize(std::max(a.size(), b.size()));
    for(size_t i = 0; i < b.size(); i++) 
        inc(a[i], b[i]);
    return a;
}
Poly operator + (Poly a, Poly b) { return a += b; }
Poly &operator -= (Poly &a, Poly b) {
    a.resize(std::max(a.size(), b.size()));
    for(size_t i = 0; i < b.size(); i++) 
        inc(a[i], P - b[i]);
    return a;
}
Poly operator - (Poly a, Poly b) { return a - b; }
Poly operator - (Poly a) { 
    for(auto &x : a) 
        if(x) x = P - x; 
    return a; 
}
Poly &operator >>= (Poly &a, Int x) {
    if (x >= (Int)a.size()) {
        a.clear();
    } else {
        a.erase(a.begin(), a.begin() + x);
    }
    return a;
}
Poly &operator <<= (Poly &a, Int x) {
    a.insert(a.begin(), x, 0);
    return a;
}
Poly operator >> (Poly a, Int x) { return a >>= x; }
Poly operator << (Poly a, Int x) { return a <<= x; }

Poly &cdot(Poly &a, Poly b) {
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); i++) 
        a[i] = (ll) a[i] * b[i] % P;
    return a;
}
Poly dot(Poly a, Poly b) { return cdot(a, b); }
void norm(Poly &a) {
    if (!a.empty()) {
        a.resize(1 << std::__lg(a.size() * 2 - 1));
    }
}

void dft(Int *a, int n) {
    //assert((n & n - 1) == 0);
    for(int k = n >> 1; k; k >>= 1) {
        for(int i = 0; i < n; i += k << 1) {
            for(int j = 0; j < k; j++) {
                Int x = a[i + j], y = a[i + j + k], ww = w[k + j];
                a[i + j] = x + y >= P ? x + y - P : x + y;
                a[i + j + k] = (ll) (x - y + P) * ww % P;
            }
        }
    }
}

void idft(Int *a, int n) {
    //assert((n & n - 1) == 0);
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; i += k << 1) {
            for(int j = 0; j < k; j++) {
                Int x = a[i + j], y = (ll) a[i + j + k] * w[k + j] % P;
                if(x >= P) x -= P;
                a[i + j + k] = x - y + P;
                a[i + j] = x + y;
            }
        }
    }
    for (Int i = 0, inv = P - (P - 1) / n; i < n; i++)
        a[i] = (ll) a[i] * inv % P;
    std::reverse(a + 1, a + n);
}


void dft(Poly &a) { dft(a.data(), a.size()); }
void idft(Poly &a) { idft(a.data(), a.size()); }

Poly operator* (Poly a, Poly b) {
    if(a.empty() || b.empty()) return {};
    int len = a.size() + b.size() - 1;
    if(a.size() <= 16 || b.size() <= 16) {
        Poly c(len);
        for(size_t i = 0; i < a.size(); i++)
            for(size_t j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + ll(a[i]) * b[j]) % P;
        return c;
    }
    int n = 1 << std::__lg(len - 1) + 1;
    if (a != b) {
        a.resize(n), b.resize(n);
        dft(a), dft(b);
        cdot(a, b);
    } else {
        a.resize(n), dft(a);
        cdot(a, a);
    }
    idft(a);
    a.resize(len);
    return a;
}

// return: inv(a) mod x ^ n, n = a.size()
// require n = 2 ^ k
// resize: n' = 1 << lg(2 * n - 1) (n >= 1)
Poly inverse(Poly a) {  
    int n = a.size();
    assert((n & n - 1) == 0);
    if (n == 1) return {fpow(a[0])};
    int m = n >> 1;
    Poly b = inverse(Poly(a.begin(), a.begin() + m)), c = b;
    b.resize(n);
    dft(a), dft(b), cdot(a, b), idft(a);
    for (int i = 0; i < m; i++) a[i] = 0;
    for (int i = m; i < n; i++) a[i] = P - a[i];
    dft(a), cdot(a, b), idft(a);
    for (int i = 0; i < m; i++) a[i] = c[i];
    return a;
}

// return: q(len = n - m + 1), a = b * q + r
Poly operator/ (Poly a, Poly b) {  
    int n = a.size(), m = b.size();
    if (n < m) return {0};
    int k = 1 << std::__lg(n - m << 1 | 1);
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    a.resize(k), b.resize(k), b = inverse(b);
    a = a * b;
    a.resize(n - m + 1);
    std::reverse(a.begin(), a.end());
    return a;
}

// return: {q(len = n - m + 1), r(len = m - 1)}
// require: b.size() > 0
std::pair<Poly, Poly> operator% (Poly a, Poly b) {
    int m = b.size();
    Poly q = a / b;
    b = b * q;
    a.resize(m - 1);
    for (int i = 0; i < m - 1; i++) inc(a[i], P - b[i]);
    return {q, a};
}

Poly der(Poly a) {
    int sz = a.size();
    for(int i = 0; i + 1 < sz; i++) 
        a[i] = (ll) (i + 1) * a[i + 1] % P;
    a.pop_back();
    return a;
}

std::vector<Int> inv = {1, 1};
void updateInv(Int n) {
    if (inv.size() <= n) {
        Int p = inv.size();
        inv.resize(n + 1);
        for (Int i = p; i <= n; i++) 
            inv[i] = (ll) (P - P / i) * inv[P % i] % P;
    }
}

Poly integ(Poly a, Int c = 0) {
    int n = a.size();
    updateInv(n);
    a.resize(n + 1);
    for (int i = n - 1; i >= 0; i--) 
        a[i + 1] = (ll) inv[i + 1] * a[i] % P;
    a[0] = c;
    return a;
}

// return: ln(a) mod x ^ n, n = a.size()
Poly ln(Poly a) {
    int n = a.size();
    norm(a);
    assert(a[0] == 1);
    a = inverse(a) * der(a);
    a.resize(n - 1);
    return integ(a);
}

// un-checked
Poly exp(Poly a) {
    int n = a.size();
    assert((n & n - 1) == 0);
    assert(a[0] == 0);
    if (n == 1) return {1};
    int m = n >> 1;
    Poly b = exp(Poly(a.begin(), a.begin() + m)), c;
    b.resize(n), c = ln(b);
    a.resize(n << 1), b.resize(n << 1), c.resize(n << 1);
    dft(a), dft(b), dft(c);
    for (int i = 0; i < n << 1; i++) a[i] = (ll(1) + P + a[i] - c[i]) * b[i] % P;
    idft(a);
    a.resize(n);
    return a;
}

// checked
Poly power(Poly a, Int k, Int kreal) {
    int n = a.size();
    long long d = 0;
    while (d < n && !a[d]) d++;
    if (d == n) return a;
    a >>= d;
    Int b = fpow(a[0]);
    norm(a *= b);
    a = exp(ln(a) * k) * fpow(b, P - 1 - k % (P - 1));
    a.resize(n);
    d *= kreal;
    for (int i = n - 1; i >= d; i--) a[i] = a[i - d];
    d = std::min(d, (long long) n);
    for(int i = d - 1; i >= 0; --i) a[i] = 0;
    return a;
}

// k1 = k % (P - 1), k2 = k % P
// kreal = min(k, P) 
Poly power(Poly a, Int k1, Int k2, Int kreal) {
    int n = a.size();
    long long d = 0;
    while (d < n && !a[d]) d++;
    if (d == n) return a;
    a >>= d;
    Int b = fpow(a[0]);
    norm(a *= b);
    a = exp(ln(a) * k2) * fpow(b, P - 1 - k1 % (P - 1));
    a.resize(n);
    d *= kreal;
    for (int i = n - 1; i >= d; i--) a[i] = a[i - d];
    d = std::min(d, (long long) n);
    for(int i = d - 1; i >= 0; --i) a[i] = 0;
    return a;
}

// [x^n] f / g
Int divAt(Poly f, Poly g, ll n) {
    int len = std::max(f.size(), g.size());
    assert(len > 0);
    int m = 1 << std::__lg(2 * len - 1);
    len = m << 1;
    f.resize(len);
    for (; n; n >>= 1) {
        g.resize(len);
        dft(f), dft(g);
        for (int i = 0; i < len; ++i) 
            f[i] = (ll) f[i] * g[i ^ 1] % P;
        for (int i = 0; i < m; ++i)
            g[i] = (ll) g[i << 1] * g[i << 1 | 1] % P;
        g.resize(m);
        idft(f), idft(g);
        for (int i = 0; i < m; ++i) f[i] = f[i * 2 + (n & 1)];
        fill(f.begin() + m, f.end(), 0);
    }
    return (ll) f[0] * fpow(g[0]) % P;
}

}  // namespace Polynomial

using namespace Polynomial;
using namespace std;

/*
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    Int k2 = 0, k1 = 0, kreal = 0;
    for(int i = 0, w = s.size(); i < s.size(); i++) {
        --w;
        inc(k2, (ll) (s[i] - '0') * fpow(10, w) % P);
        inc(k1, (ll) (s[i] - '0') * fpow(10, w, P - 1) % (P - 1), P - 1);
        if(kreal * 10 + (s[i] - '0') <= P) kreal = kreal * 10 + (s[i] - '0');
    }
    Poly a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    Poly b = power(a, k1, k2, kreal);
    for(int i = 0; i < n; ++i) cout << b[i] << " \n"[i == n - 1];
} */

Int read() {
    int x;
    cin >> x;
    x %= 998244353;
    x += 998244353;
    x %= 998244353;
    return x;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll n;
    int k;
    cin >> n >> k;
    Poly f(k + 1), a(k);
    f[0] = 1;
    for(int i = 1; i <= k; ++i) {
        f[i] = read();
        if(f[i]) f[i] = P - f[i];
    }
    for(auto &x : a) {
        x = read();
    }
    Poly b = a * f;
    b.resize(k);
    Int ans = divAt(b, f, n);
    cout << ans << endl;
}
