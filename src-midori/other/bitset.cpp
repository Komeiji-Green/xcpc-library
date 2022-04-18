using ull = unsigned long long;

const int Lg = 64;

// 寻找 bitset 中任意一个非 0 位
template<size_t MAXN>
int findAny(bitset<MAXN>& a) {
    ull *p = (ull *)&a;
    
    int len = MAXN / Lg;
    for (int i = 0; i < len; i++) {
        if (p[i]) {
            for (int j = 0; j < Lg; j++) {
                if ((p[i] >> j) & 1ll) {
                    return (i * Lg + j);
                }
            }
        }
    }
    
    assert(false);
    return -1;
}

// bitset: 将第 i 位设置为 0/1
// s.set(i, val);

// bitset: 清空
// s.reset();

// bitset: 取第 i 位
// s.test(i);

// _Find_first(): 寻找第一位
int x = st[i]._Find_first();

// _Find_next(int i): 寻找下一位
int y = st[i]._Find_next(x);