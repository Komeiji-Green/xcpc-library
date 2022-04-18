// 记忆化搜索
struct cmp {
    bool operator()(const state& a, const state& b) const {
        // ...
    }
};

struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.cnt[0];
        for(int i = 1; i < 10; ++i) {
            res *= 19260817;
            res += st.cnt[i];
        }
        return res;
    }
};
unordered_map <state, ll, _hash, cmp> dp[20][20];

// -pos: 搜到的位置
// -st: 当前状态
// -lead: 是否有前导 0
// -limit: 是否有最高位限制
ll dfs(int pos, state st, int lead, int limit){
    // 边界情况
    if(pos < 0 /* && ... */) return 0;
    // 记忆化搜索
    int wd = st.w[st.d];
    if((!limit) && (!lead) && dp[pos][wd].count(st)) return dp[pos][wd][st];

    ll res = 0;
    // 最高位最大值
    int cur = limit ? a[pos] : 9;
    for(int i = 0; i <= cur; ++i) {
        // 有前导0且当前位也是0
        if((!i) && lead) res += dfs(pos-1, st, 1, limit&&(i==cur));
        // 有前导0且当前位非0 (出现最高位)
        else if(i && lead) res += dfs(pos-1, st.add(i), 0, limit&&(i==cur));
        else res += dfs(pos-1, st.add(i), 0, limit&&(i==cur));
    } 
    // 没有前导0和最高限制时可以直接记录当前dp值以便下次搜到同样的情况可以直接使用
    if(!limit&&!lead) dp[pos][wd][st] = res;
    return res;
}

ll gao(ll x) {
    memset(a, 0, sizeof(a));
    int len=0;
    while(x) a[len++]=x%10,x/=10;
    // init st
    return dfs(len-1, st, 1, 1);
}

int main()
{
    int T;
    ll l, r; int d;
    cin >> T;
    while(T--) {
        scanf("%lld %lld %d", &l, &r, &d);
        ll ans = gao(r, d) - gao(l - 1, d);
        printf("%lld\n", ans);
    }
}