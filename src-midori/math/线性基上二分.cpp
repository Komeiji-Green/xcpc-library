using ll = long long;

const int N = 70;
const int Lg = 60;

ll bs[N];

// find x in S s.t. k ^ x >= low and k ^ x is minimum,
// !!! return k ^ x, not x
// if not exist, return inf
ll lower(ll k, ll low) {

    // ll x = k ^ low; // expected value in S
    // ll res = 0; // value represented in S
    ll x = 0;
    ll ex = k ^ low;
    int lb = -1;

    // 在前缀可表示的范围内的寻找:
    // 对于范围内 low[i] = 0 的位,
    // 考虑另一分支的可行性
    for (int i = Lg - 1; i >= 0; i--) {
        if (((low >> i) & 1ll) == 0) {     // another branch
            int d = ((ex ^ x) >> i) & 1ll; // cur branch
            if (d || bs[i]) {
                lb = i;
            }
        }

        if (((ex ^ x) >> i) & 1ll) {
            if (bs[i]) {
                x ^= bs[i];
            } else {
                break;
            }
        }
    }

    if ((ex ^ x) == 0) // 可表示
        return k ^ x;

    if (lb == -1) // 不可表示, 且不可更大
        return inf;

    if ((((k ^ x ^ low) >> lb) & 1ll) == 0)
        x ^= bs[lb];

    for (int i = lb - 1; i >= 0; i--) {
        if (((k ^ x) >> i) & 1ll) {
            if (bs[i]) {
                x ^= bs[i];
            }
        }
    }

    return k ^ x;
}