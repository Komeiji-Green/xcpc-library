vector<int> vec[N];
bool vis[N];

namespace DFZ {

    int sz[N], maxx[N];

    int rt, sum;
    void calcsz(int x, int dad) {
        //cerr << rt << "   " << sum << endl;
        maxx[x] = 0; sz[x] = 1;
        for (int y : vec[x]) {
            if(y == dad || vis[y]) continue;
            calcsz(y, x);
            sz[x] += sz[y];
            maxx[x] = max(sz[y], maxx[x]);
        }
        assert(sum - sz[x] >= 0);
        maxx[x] = max(maxx[x], sum - sz[x]);
        if (maxx[x] < maxx[rt]) rt = x;
    }

    void dfz(int x) {
        calcsz(x, 0); vis[rt] = 1;
        TREE::init();
        TREE::dfs(rt, 0, 0, 0, 1);
        ALL += TREE::gao();
        // calc mx, dis, build seg treedp

        int cen = rt, psum = sum;
        for (int y : vec[cen]) {
            if (vis[y]) continue;
            rt = cen;
            sum = (sz[y] > sz[cen] ? psum - sz[cen] : sz[y]);
            dfz(y);
        }
    }
}

DFZ::rt = 0; DFZ::maxx[0] = inf; DFZ::sum = n;
DFZ::dfz(1);