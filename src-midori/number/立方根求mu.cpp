int getmu(int x) {
    int pr, cur = 0;
    for (int i = 1; i <= cnt; ++i) {
        cur = 0;
        while (x % prime[i] == 0) {
            ++cur; x /= prime[i];
        }
        if (cur > 1) return 0;
    }
    if (x == 1) return 1;
    int sq = sqrt(x) + 0.5;
    if (1ll * sq * sq == x) return 0;
    return 1;
}