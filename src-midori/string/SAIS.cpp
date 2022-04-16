const int BUFFER_SIZE = 1u << 26 | 1;
char buf[BUFFER_SIZE], *buf_ptr = buf;

#define alloc(x, type, len)     \
    type *x = (type *)buf_ptr;  \
    buf_ptr += (len) * sizeof(type);

#define clear_buf() \
    memset(buf, 0, buf_ptr - buf), buf_ptr = buf;

template <int MAXN> class SuffixArray {
#define ltype true
#define stype false

public:
    int sa[MAXN], rk[MAXN], hei[MAXN];

    void compute(int n, int m, int *s) {
        sais(n, m, s, sa);
        for (int i = 0; i < n; ++i) rk[sa[i]] = i;
        for (int i = 0, h = 0; i < n; i++) {
            if (rk[i]) {
                int j = sa[rk[i] - 1];
                while (s[i + h] == s[j + h]) ++h;
                hei[rk[i]] = h;
            } else {
                h = 0;
            }
            if (h) --h;
        }
    }

private:
    int lbuc[MAXN], sbuc[MAXN];

    void induce(int n, int m, int *s, bool *type, int *sa, int *buc, 
                int *lbuc, int *sbuc) 
    {
        memcpy(lbuc + 1, buc, m * sizeof(int));
        memcpy(sbuc + 1, buc + 1, m * sizeof(int));

        sa[lbuc[s[n - 1]]++] = n - 1;
        
        for (int i = 0; i < n; i++) {
            int t = sa[i] - 1;
            if (t >= 0 && type[t] == ltype) 
                sa[lbuc[s[t]]++] = t;
        }

        for (int i = n - 1; i >= 0; i--) {
            int t = sa[i] - 1;
            if (t >= 0 && type[t] == stype) 
                sa[--sbuc[s[t]]] = t;
        }
    }

    void sais(int n, int m, int *s, int *sa) {
        alloc(type, bool, n + 1);
        alloc(buc, int , m + 1);

        type[n] = false;

        for (int i = n - 1; i >= 0; i--) {
            ++buc[s[i]];
            type[i] = s[i] > s[i + 1] || (s[i] == s[i + 1] && type[i + 1] == ltype);
        }
        for (int i = 1; i <= m; i++) {
            buc[i] += buc[i - 1];
            sbuc[i] = buc[i];
        }
        memset(rk, -1, n * sizeof(int));

        alloc(lms, int, n + 1);

        int n1 = 0;
        for (int i = 0; i < n; i++) {
            if (!type[i] && (i == 0 || type[i - 1]))
                lms[rk[i] = n1++] = i;
        }

        lms[n1] = n;
        memset(sa, -1, n * sizeof(int));

        for (int i = 0; i < n1; i++) sa[--sbuc[s[lms[i]]]] = lms[i];
        induce(n, m, s, type, sa, buc, lbuc, sbuc);

        int m1 = 0;
        alloc(s1, int, n + 1);

        for (int i = 0, t = -1; i < n; i++) {
            int r = rk[sa[i]];
            if (r != -1) {
                int len = lms[r + 1] - sa[i] + 1;
                m1 += t == -1 || len != lms[rk[t] + 1] - t + 1 ||
                    memcmp(s + t, s + sa[i], len * sizeof(int)) != 0;
                s1[r] = m1;
                t = sa[i];
            }
        }

        alloc(sa1, int, n + 1);

        if (n1 == m1) {
            for (int i = 0; i < n1; i++)
                sa1[s1[i] - 1] = i;
        } else {
            sais(n1, m1, s1, sa1);
        }
        
        memset(sa, -1, n * sizeof(int));
        memcpy(sbuc + 1, buc + 1, m * sizeof(int));
        
        for (int i = n1 - 1; i >= 0; i--) {
            int t = lms[sa1[i]];
            sa[--sbuc[s[t]]] = t;
        }
        induce(n, m, s, type, sa, buc, lbuc, sbuc);
    }
#undef stype
#undef rtype
};