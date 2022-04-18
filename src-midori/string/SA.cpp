// h[i] = lcp(sa[i], sa[i - 1])
// sa[i] = 排名为 i 的后缀（下标）
// rk[i] = 后缀 i 的排名
// 需要将 s[n] 设为一个比一切字符大的数，才能正确地输出 height
// 不需要清空

template<int MAXN> class SA {
    public:
    int n, sa[MAXN], rk[MAXN], h[MAXN];

    void init() {
        // 不需要 init
    }
 
    void compute(int *s, int n, int m) {
        int i, p, w, j, k;
        this->n = n;
        if (n == 1) {
            sa[0] = rk[0] = h[0] = 0; return;
        }
        memset(cnt, 0, m * sizeof(int));
        for (i = 0; i < n; ++i) ++cnt[rk[i] = s[i]];
        for (i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
        for (i = n - 1; ~i; --i) sa[--cnt[rk[i]]] = i;
        for (w = 1; w < n; w <<= 1, m = p) {
            for (p = 0, i = n - 1; i >= n - w; --i) id[p++] = i;
            for (i = 0; i < n; ++i)
                if (sa[i] >= w) id[p++] = sa[i] - w;
            memset(cnt, 0, m * sizeof(int));
            for (i = 0; i < n; ++i) ++cnt[px[i] = rk[id[i]]];
            for (i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
            for (i = n - 1; ~i; --i) sa[--cnt[px[i]]] = id[i];
            memcpy(old_rk, rk, n * sizeof(int));
            for (i = p = 1, rk[sa[0]] = 0; i < n; ++i)
                rk[sa[i]] = cmp(sa[i], sa[i-1], w) ? p - 1 : p++;
        }
        for (i = 0; i < n; ++i) rk[sa[i]] = i;
        for (i = k = h[rk[0]] = 0; i < n; h[rk[i++]] = k)
            if (rk[i])
                for (k > 0 ? --k : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k) {}
    }
    private:
    int old_rk[MAXN], id[MAXN], px[MAXN], cnt[MAXN];
    bool cmp(int x, int y, int w) {
        return old_rk[x] == old_rk[y] && old_rk[x + w] == old_rk[y + w];
    }
};