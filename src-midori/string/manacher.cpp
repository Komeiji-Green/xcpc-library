/* manacher */
const int maxn = 300007;
// s[0]: 特殊值，s[1, 3 .. tot]: 分隔值 
int s[maxn], p[maxn]; // p 为半径
//int L[maxn], R[maxn]; // 包含点i的回文串，回文中心最左、右
int n, tot;

void manacher() {
    int right = 0, idx = 0;
    for(int i = 1; i <= tot; i++) {
        if(i < right)
            p[i] = min(p[2 * idx - i], right - i);
        else
            p[i] = 1;

        while(i + p[i] <= tot && s[i + p[i]] == s[i - p[i]])
            p[i]++;

        p[i]--;

        if(i + p[i] > right) {
            right = i + p[i];
            idx = i;
        }
    }
}