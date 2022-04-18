struct state {
    int w[51];
} st;

struct cmp {
    bool operator()(const state& a, const state& b) const {
        for(int i = 1; i <= 50; ++i) {
            if(a.w[i] != b.w[i]) return false;
        }
        return true;
    }
};

struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.w[1];
        for(int i = 2; i <= 50; ++i) {
            res *= 19260817;
            res += st.w[i];
        }
        return res;
    }
};

unordered_map <state, ll, _hash, cmp> mp_st; 

// mp.reserve(1e7);