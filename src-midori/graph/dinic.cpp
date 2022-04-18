using ll = long long;

// 前向链表多测注意清空，tot 初值要设为 1
struct edge {
    int to, pre;
    ll w;
} e[M];
int last[N], tot = 1;

void ine(int a, int b, ll w) {
    e[++tot] = (edge){b, last[a], w};
    last[a] = tot;
}

void add(int a, int b, ll w) {
    ine(a, b, w);
    ine(b, a, 0);
}

inline int sgn(ll v) {
    if (v == 0) return 0;
    return v > 0 ? 1 : -1;
}

namespace Dinic {

    int n, s, t;
    int lv[N], cur[M];  // lv：层数，cur：当前弧

    bool bfs()  {
        fill(lv + 1, lv + 1 + n, -1);
        lv[s] = 0;
        copy(last + 1, last + 1 + n, cur + 1);
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = cur[u]; i; i = e[i].pre) {
                int to = e[i].to;
                ll vol = e[i].w;
                if(vol > 0 && lv[to] == -1)
                    lv[to] = lv[u] + 1, q.push(to);
            }
        }
        return lv[t] != -1; // 如果汇点未访问过则不可达
    }

    ll dfs(int u = s, ll f = inf) {
        if(u == t) 
            return f;
        for(int &i = cur[u]; i; i = e[i].pre) {
            int to = e[i].to;
            ll vol = e[i].w;
            if(vol > 0 && lv[to] == lv[u] + 1) {
                ll c = dfs(to, min(vol, f));
                if(sgn(c)) {
                    e[i].w -= c;
                    e[i ^ 1].w += c;    // 反向边
                    return c;
                }
            }
        }
        return 0; // 输出流量大小
    }

    ll dinic(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        ll ans = 0;
        while(bfs()) {
            ll f;
            while((f = dfs()) > 0)
                ans += f;
        }
        return ans;
    }
} // namespace Dinic

using Dinic::dinic;