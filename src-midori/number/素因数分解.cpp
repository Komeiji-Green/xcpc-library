// 素因数分解 
int p[maxn], l[maxn], cnt2 = 0;
void Fact(int x) {
    cnt2 = 0;
    for (int i = 2; 1ll * i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt2] = i; l[cnt2] = 0;
            while(x % i == 0) {
                x /= i; ++l[cnt2];
            }
        }
    }
    if (x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt2] = x; l[cnt2] = 1;
    }
}

// vector ver. 无次数
void Fact(ll x, vector<int>& fact) {
    for (ll i = 2; 1ll * i * i <= x; ++i) {
        if(x % i == 0) {
            fact.push_back(i);
            while(x % i == 0) x /= i; 
        }
    }
    if (x != 1) fact.push_back(x);
}