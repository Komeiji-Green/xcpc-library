using ll = long long;

// 边界从 (s, x) 移动到 (s + 1, nx)
ll move(int x, int nx, int s, ll sum) {
    assert(x >= -1);
    ll res = (2 * sum + mod - C(s, x)) % mod;
    while (x + 1 <= nx) {
        x++;
        res = (res + C(s + 1, x)) % mod;
    }
    while (x > nx) {
        res = (res + mod - C(s + 1, x)) % mod;
        x--;
    }
    return res;
};

void proc(int k) {
    // 第 s 行的 左右边界
    auto le = [&](int s) -> int {
        // ...
    };
    auto ri = [&](int s) -> int {
        // ...
    };
    // 这里应该暴力计算首行和，当首行为 0 时也可以这样写
    ll lsum = move(-1, le(0), -1, 0);
    ll rsum = move(-1, ri(0), -1, 0);

    for (int s = 0; s <= k; s++) {
        if (le(s) < ri(s)) {
            // ... 第 s 行对答案的贡献
        }
        lsum = move(le(s), le(s + 1), s, lsum);
        rsum = move(ri(s), ri(s + 1), s, rsum);
    }
}
