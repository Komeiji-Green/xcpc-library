// 1-base
// 主过程: 设置好 cost[N][N] 即可调用
// cost 可以为负数

using ll = long long;
#define prev prevv
 
const int N = 305;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll cost[N][N];
ll lx[N], ly[N];
int match[N];
ll slack[N];
int prev[N];
bool vy[N];
 
void augment(int root) {
    fill(vy + 1, vy + n + 1, false);
    fill(slack + 1, slack + n + 1, INF);
    int py;
    match[py = 0] = root;

    do {
        vy[py] = true;
        int x = match[py];
        ll delta = INF;
        int yy;
        for (int y = 1; y <= n; y++) {
            if (!vy[y]) {
                if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
                    slack[y] = lx[x] + ly[y] - cost[x][y];
                    prev[y] = py;
                }
                if (slack[y] < delta) {
                    delta = slack[y];
                    yy = y;
                }
            }
        }
        for (int y = 0; y <= n; y++) {
            if (vy[y]) {
                lx[match[y]] -= delta;
                ly[y] += delta;
            } else {
                slack[y] -= delta;
            }
        }
        py = yy;
    } while (match[py] != -1);

    do {
        int pre = prev[py];
        match[py] = match[pre];
        py = pre;
    } while (py);
}
 
ll KM() {
    for (int i = 1; i <= n; i++) {
        lx[i] = ly[i] = -INF;
        match[i] = -1;
        for (int j = 1; j <= n; j++) {
            lx[i] = std::max(lx[i], cost[i][j]);
        }
    }
    ll answer = 0;
    for (int root = 1; root <= n; root++) {
        augment(root);
    }
    for (int i = 1; i <= n; i++) {
        answer += lx[i];
        answer += ly[i];
        // printf("%d %d\n", match[i], i);
    }
    return answer;
}