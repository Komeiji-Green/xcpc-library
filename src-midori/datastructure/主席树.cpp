const int N = 100010;
const int M = N * 40;

struct node {
    int l, r; 
    ll val;
} tr[M];

int rt[N], tot;

int clone(int k) {
    ++tot;
    tr[tot] = tr[k];
    return tot;
}

void up(int k) {
    tr[k].val = tr[tr[k].l].val ^ tr[tr[k].r].val;
}

void upd(int &k, int x, int l, int r, ll val) {
    k = clone(k);
    if(l == r) {
        tr[k].val ^= val;
    } else {
        int m = ((l + r) >> 1);
        if (x <= m) upd(tr[k].l, x, l, m, val);
        else upd(tr[k].r, x, m + 1, r, val);
        up(k);
    }
}

/* 树形建主席树 */
void dfs(int x, int dad) {
    rt[x] = rt[dad];
    upd(rt[x], a[x], 1, n, val);
    for (auto y : ch[x]) {
        if(y == dad) continue;
        dfs(y, x);
    }
}