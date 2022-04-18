// 多串创建 sam 的方法:
// 在插入每个串前, 设置 last = 1, 然后一路 last = extend(last, c)

int extend(int p, int c) {
	int np = 0;
	
	if (!go[p][c]) {
		np = ++sam_cnt;
		len[np] = len[p] + 1;
		while (p && !go[p][c]) {
			go[p][c] = np;
			p = fa[p];
		}
	}

	if (!p)
		fa[np] = 1;
	else {
		int q = go[p][c];

		if (len[q] == len[p] + 1) {
			if (np)
				fa[np] = q;
			else
				return q;
		}
		else {
			int nq = ++sam_cnt;
			len[nq] = len[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));

			fa[nq] = fa[q];
			fa[q] = nq;
			if (np)
				fa[np] = nq;

			while (p && go[p][c] == q){
				go[p][c] = nq;
				p = fa[p];
			}

			if (!np)
				return nq;
		}
	}
	
	return np;
}