/**
 * cur: 起始位置
 * initT: 初始温度
 * c: 退火速率
 */
db SA(point origin, db initT, db eps=1e-6, db c=0.9999, int times=50000000) {
    point cur = origin;

	db t = initT;
    db ans = calc(cur), fx = ans;
    int steps = 0;
    for (int cnt = 0; cnt < 10; cnt++) {
        int i = 0;
        cur = origin;
        t = initT;
        for (i = 1; i <= times && fabs(t) > eps; i++) {
            point nex = cur.move(t);
            db fy = calc(nex);
            ans = min(ans, fy);
            db delta = fy - fx;
            if (exp(-delta / t) > Rand()) 
                cur = nex, fx = fy;
            t *= c;
        }
        steps = i;
    }

    cout << "times = " << steps << endl;
	return ans;
}