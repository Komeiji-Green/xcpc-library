// 多串创建 sam 的方法:
// 在插入每个串前, 设置 last = 1, 然后一路 last = extend(last, c)

int extend(int p, int c) {
	int np = 0;
	
	if (!go[p][c]) {
		np = ++sam_cnt;
		val[np] = val[p] + 1;
		while (p && !go[p][c]) {
			go[p][c] = np;
			p = par[p];
		}
	}

	if (!p)
		par[np] = 1;
	else {
		int q = go[p][c];

		if (val[q] == val[p] + 1) {
			if (np)
				par[np] = q;
			else
				return q;
		}
		else {
			int nq = ++sam_cnt;
			val[nq] = val[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));

			par[nq] = par[q];
			par[q] = nq;
			if (np)
				par[np] = nq;

			while (p && go[p][c] == q){
				go[p][c] = nq;
				p = par[p];
			}

			if (!np)
				return nq;
		}
	}
	
	return np;
}