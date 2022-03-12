using i128 = __int128;

// ax + by = c
// 有解当且仅当 gcd(a, b) | c
// 要求 a, b 不全为 0
// 无合法性检查
void exgcd(i128 a, i128 b, i128 &x, i128 &y, i128 c = 1) {
    if (b == 0) {
        x = c / a;
        y = 0;
    } else {
        exgcd(b, a % b, x, y, c);
        i128 tmp = x;
        x = y;
        y = tmp - (a / b) * y;
    }
}