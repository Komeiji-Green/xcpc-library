using ll = long long;

// or
void FWT(ll *a, int len, int inv) {
    for (int h = 1; h < len; h <<= 1) {
        for (int i = 0; i < len; i += (h << 1)) {
            for (int j = 0; j < h; ++j) {
                a[i + j + h] += a[i + j] * inv;
            }
        }
    }
}
// and
void FWT(ll *a, int len, int inv) {
    for (int h = 1; h < len; h <<= 1) {
        for (int i = 0; i < len; i += (h << 1)) {
            for (int j = 0; j < h; ++j) {
                a[i + j] += a[i + j + h] * inv;
            }
        }
    }
}
// xor
void FWT(ll *a, int len, int inv) {
    for (int h = 1; h < len; h <<= 1) {
        for (int i = 0; i < len; i += (h << 1)) {
            for (int j = 0; j < h; ++j) {
                ll x = a[i + j], y = a[i + j + h];
                a[i + j] = x + y, a[i + j + h] = x - y;
                if (inv == -1) 
                    a[i + j] /= 2, a[i + j + h] /= 2;
            }
        }
    }
}