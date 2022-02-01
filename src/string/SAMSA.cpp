bool vis[maxn * 2];
char s[maxn];
int n, id[maxn * 2], ch[maxn * 2][26], height[maxn], tim = 0;

void dfs(int x) {
	if (id[x]) {
		height[tim++] = val[last];
		sa[tim] = id[x];

		last = x;
	}

	for (int c = 0; c < 26; c++)
		if (ch[x][c])
			dfs(ch[x][c]);

	last = par[x];
}

int main() {
	last = ++cnt;

	scanf("%s", s + 1);
	n = strlen(s + 1);

	for (int i = n; i; i--) {
		expand(s[i] - 'a');
		id[last] = i;
	}

	vis[1] = true;
	for (int i = 1; i <= cnt; i++)
		if (id[i])
			for (int x = i, pos = n; x && !vis[x]; x = par[x]) {
				vis[x] = true;
				pos -= val[x] - val[par[x]];
				ch[par[x]][s[pos + 1] - 'a'] = x;
			}

	dfs(1);

	for (int i = 1; i <= n; i++) {
		if (i > 1)
			printf(" ");
		printf("%d", sa[i]); // 1-based
	}
	printf("\n");

	for (int i = 1; i < n; i++) {
		if (i > 1)
			printf(" ");
		printf("%d", height[i]);
	}
	printf("\n");

	return 0;
}