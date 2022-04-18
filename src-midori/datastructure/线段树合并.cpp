// merge v to u

void merge(int &u, int v, int l, int r) {
	if (!v) return;
	else if (!u) u = v;
	else if (l == r) {
		// merge at leaf
	} else {
		int mid = ((l + r) >> 1);
		merge(tr[u].l, tr[v].l, l, mid);
		merge(tr[u].r, tr[v].r, mid + 1, r);
		up(u);
	}
}