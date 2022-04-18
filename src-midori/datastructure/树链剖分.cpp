vector<int> vec[N];

struct cutTree {
    int dep[N], sz[N];
    int nd[N], fn[N], gn[N], clc;
    int top[N], son[N], fa[N];

    void init(int n) {
        clc = 0;
        for(int x = 1; x <= n; x++) son[x] = 0;
        for(int x = 1; x <= n; x++) fa[x] = 0;
    }
    // dfs1(rt, 1);
    void dfs1(int x, int d) {
        dep[x] = d, sz[x] = 1;
        for(int y : vec[x]) {
            if(y == fa[x]) continue;
            fa[y] = x; dfs1(y, d + 1); sz[x] += sz[y];
            if(!son[x] || sz[y] > sz[son[x]]) son[x] = y;
        }
    }
    // dfs2(rt, rt);
    void dfs2(int x, int an) {
        top[x] = an;
        nd[fn[x] = ++clc] = x;
        if(son[x]) dfs2(son[x], an);
        for(int y : vec[x]) {
            if(y == fa[x] || y == son[x]) continue;
            dfs2(y, y);
        }
        gn[x] = clc;
    }
    int lca(int x, int y) {
        while(top[x] != top[y]) {
            if(dep[top[x]] > dep[top[y]]) 
                swap(x, y);
            y = fa[top[y]];
        }
        return dep[x] < dep[y] ? x : y;
    }
    // anc[x][0] = x, !! 默认根为 1, 若 rt 非 1, 需要传参
    int up(int x, int k, int rt = 1) {
        if(k < 0) return -1;
        if(k >= dep[x]) return 0;
        while(k) {
            if(fn[x] - fn[top[x]] < k)
                k -= fn[x] - fn[top[x]] + 1, x = fa[top[x]];
            else x = nd[fn[x] - k], k = 0;
        }
        return x;
    }
    int query(int x, int y) {
        int res = 0;
        while(top[x] != top[y]) {
            if(dep[top[x]] > dep[top[y]]) swap(x, y);
            int l = fn[top[y]], r = fn[y];
            res += bit.query(r) - bit.query(l - 1);
            y = fa[top[y]];
        }
        if(dep[x] > dep[y]) swap(x, y);
        return res + bit.query(fn[y]) - bit.query(fn[x] - 1);
    }
} CT;