// 矩形面积并, 标记永久化, 注意要开八倍空间

typedef long long ll;

const int maxn = 100050;

struct node {
    int sum, lazy;
    void clear() {
        sum = 0; lazy = 0;
    }
} tr[maxn << 3];

void up(int k, int l, int r) {
    if (tr[k].lazy) {
        tr[k].sum = r - l + 1;
    } else {
        tr[k].sum = tr[k<<1].sum + tr[k<<1|1].sum;
    }
}

void build(int k, int l, int r) {
    tr[k].clear();

    if (l == r) {
        tr[k<<1].clear();
        tr[k<<1|1].clear();
        return;
    }

    int mid = ((l + r) >> 1);
    build(k<<1, l, mid);
    build(k<<1|1, mid + 1, r);
    up(k, l, r);
}

void upd(int k, int cl, int cr, int tag, int l, int r) {
    if (cl <= l && r <= cr) {
        tr[k].lazy += tag;
        up(k, l, r);
    } else {
        int mid = ((l + r) >> 1);
        if(cl <= mid) upd(k<<1, cl, cr, tag, l, mid);
        if(cr > mid) upd(k<<1|1, cl, cr, tag, mid + 1, r);
        up(k, l, r);
    }
}

// 查询的时候记一下祖先结点是否有 lazy > 0