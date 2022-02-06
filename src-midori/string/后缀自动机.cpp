// 在字符集比较小的时候可以直接开go数组, 否则需要用map或者哈希表替换
// 注意!!!结点数要开成串长的两倍

// 全局变量与数组定义
int last, len[maxn], fa[maxn], go[maxn][26], sam_cnt;
int c[maxn], q[maxn]; // 用来桶排序

// 在主函数开头加上这句初始化
last = sam_cnt = 1;

// 以下是按val进行桶排序的代码
for (int i = 1; i <= sam_cnt; i++)
	c[len[i] + 1]++;
for (int i = 1; i <= n; i++)
	c[i] += c[i - 1]; // 这里n是串长
for (int i = 1; i <= sam_cnt; i++)
	q[++c[len[i]]] = i;

//加入一个字符 均摊O(1)
void extend(int c) {
	int p = last, np = ++sam_cnt;
	len[np] = len[p] + 1;

	while (p && !go[p][c]) {
		go[p][c] = np;
		p = fa[p];
	}

	if (!p)
		fa[np] = 1;
	else {
		int q = go[p][c];

		if (len[q] == len[p] + 1)
			fa[np] = q;
		else {
			int nq = ++sam_cnt;
			len[nq] = len[p] + 1;
			memcpy(go[nq], go[q], sizeof(go[q]));

			fa[nq] = fa[q];
			fa[np] = fa[q] = nq;

			while (p && go[p][c] == q){
				go[p][c] = nq;
				p = fa[p];
			}
		}
	}
	
	last = np;
}