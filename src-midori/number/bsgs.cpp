// a ^ k == b mod p
ll BSGS(ll a, ll b, ll p) { // p <= 1e9
    static ll rec;
    static map<ll, ll> mp;
    
    ll sq = (ll)ceil(sqrt(p));
    if (rec != p) {
        rec = p;
        mp.clear();
        ll le = 1, bs = fpow(a, sq, p);
        for (ll i = 1; i <= sq; ++i) {
            le = le * bs % p;
            if (le < 0)
                le += p;
            mp[le] = i * sq;
        }
    }

    ll ri = (b % p);
    if (ri < 0)
        ri += p;
    for (ll j = 0; j <= sq; ++j) {
        if (mp.count(ri)) {
            return mp[ri] - j;
        }
        ri = ri * a % p;
        if (ri < 0)
            ri += p;
    }
    return -1;
}

// x ^ a == b mod p
ll calc(ll a, ll b, ll p) {
    ll g = generator(p); // 求原根-见原根.cpp
    ll ga = fpow(g, a, p);
    ll c = BSGS(ga, b, p);
    ll res = fpow(g, c, p);
    return res;
}
