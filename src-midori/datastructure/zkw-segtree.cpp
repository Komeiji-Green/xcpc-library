// 0-base

struct SegT {
    typedef pair<int, int> T;
    T ini = {0, 0};
    T combine(T u, T v) {
        return max(u, v);
    }
    int n; vector<T> arr;
    
    // local
    SegT(int sz): n{1} { while(n < sz) n <<= 1; arr.resize(n * 2, ini); };

    // global 
    void init(int sz) {
        arr.clear(); for (n = 1; n < sz; n <<= 1); arr.resize(n * 2, ini);
    }

    void update(int i, T v) {
        for (arr[i += n] = v; i >>= 1; )
            arr[i] = combine(arr[i<<1], arr[i<<1|1]);
    }
    T query (int l, int r) {
        T resl = ini, resr = ini;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = combine(resl, arr[l++]);
            if (r & 1) resr = combine(resr, arr[--r]);
        }
        return combine(resl, resr);
    }
};