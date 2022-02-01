#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using ll = long long;
using namespace std;
typedef pair<ll, ll> P;

const int N = 5e3 + 7, M = 1e6 + 7;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct edge { 
    int to, pre;
    ll w, c; // w: 流量 weight，c: 费用 cost
} e[M * 2];
int head[N], ecnt = 1; // 加入的第一条边编号为 2
void ine(int u, int v, ll w, ll c) {
    e[++ecnt] = {v, head[u], w, c};
    head[u] = ecnt;
}
void add(int u, int v, ll w, ll c) {
    ine(u, v, w, c); ine(v, u, 0, -c);
}
void init(int n) {
    fill(head + 1, head + 1 + n, 0);
    ecnt = 1;
}

ll h[N], dis[N]; // bool vis[N];
int pe[N]; // 父边

// spfa 只用来预处理 h，不跑流
// h 在 flow_dij 调用时清空
void spfa(int s, int n) {
    static bool inq[N];

    fill(dis + 1, dis + 1 + n, inf);
    fill(inq + 1, inq + 1 + n, false);
    
    queue<int> q;

    q.push(s);
    dis[s] = 0;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        inq[x] = false;

        for (int i = head[x]; i; i = e[i].pre)
            if (e[i].w > 0) {
                int y = e[i].to;

                if (dis[y] < dis[x] + e[i].c) {
                    // pe[y] = i; 若要跑流，则加上这一行
                    dis[y] = dis[x] + e[i].c;
                    if (!inq[y]) {
                        q.push(y);
                        inq[y] = true;
                    }
                }
            }
    }
}

void dij(int s, int n) {
    fill(dis + 1, dis + 1 + n, inf);
    dis[s] = 0;
    // fill(vis + 1, vis + 1 + n, false);

    using pq_t = __gnu_pbds::priority_queue<P, greater<P>, __gnu_pbds::thin_heap_tag>;
    pq_t q;
    static pq_t::point_iterator it[N];

    for (int i = 1; i <= n; i++)
        it[i] = q.push({dis[i], i});

    while(!q.empty()) {
        auto tp = q.top();
        int x = tp.second;
        ll w = tp.first;
        q.pop();
        
        if(w != dis[x]) continue;
        // if(vis[x]) continue;
        // vis[x] = true;

        for(int i = head[x]; i; i = e[i].pre) {
            int y = e[i].to;
            if(e[i].w > 0 && dis[y] > dis[x] + h[x] - h[y] + e[i].c) {
                pe[y] = i;
                dis[y] = dis[x] + h[x] - h[y] + e[i].c;
                q.modify(it[y], {dis[y], y});
            }
        }
    }
}

P flow_dij(int s, int t, int n) {
    fill(h + 1, h + 1 + n, 0);
    /*
    spfa(s, n);
    for(int i = 1; i <= n; i++)
        h[i] = dis[i];
    // 如果初始有负权就像这样跑一遍 SPFA 预处理 h 数组
    */

    ll cost = 0, flow = 0;

    while (1) {
        dij(s, n);
        if(dis[t] >= inf) break;

        for (int i = 1; i <= n; i++) // 先更新 h 数组
            h[i] += dis[i];

        ll nowflow = inf;
        for (int x = t; x != s; x = e[pe[x] ^ 1].to)
            nowflow = min(nowflow, e[pe[x]].w);
        
        flow += nowflow;
        cost += nowflow * h[t]; // 计算流量和费用

        for (int x = t; x != s; x = e[pe[x] ^ 1].to) {
            e[pe[x]].w -= nowflow;
            e[pe[x] ^ 1].w += nowflow;
        }  // 更新边容量
    }
    return {flow, cost};
}

// https://ac.nowcoder.com/acm/problem/222408
int main() {
    ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vector<int> z(n + 1), v(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int x, y; cin >> x >> y >> z[i] >> v[i];
        ans += x * x;
        ans += y * y;
        ans += z[i] * z[i];
    }
    int num = n * 2 + 2, s = num - 1, t = num;
    init(num);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) 
            add(i, j + n, 1, 1ll * v[i] * v[i] * (j - 1) * (j - 1) + 2ll * v[i] * z[i] * (j - 1));
    for(int i = 1; i <= n; i++)
        add(s, i, 1, 0);
    for(int i = 1; i <= n; i++)
        add(n + i, t, 1, 0);
    ans += flow_dij(s, t, num).second;
    cout << ans << '\n';
    return 0;
}