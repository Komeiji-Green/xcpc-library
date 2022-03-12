// pku

char buf[1 << 20], *p1 = buf, *p2 = buf;

#ifdef ONLINE_JUDGE
char get() {
    if (p1 == p2) {
        p1 = buf;
        p2 = buf + std::fread(buf, 1, 1 << 20, stdin);
    }
    if (p1 == p2) {
        return EOF;
    }
    return *p1++;
}
#else
char get() { return std::getchar(); }
#endif

ll readLong() {
    ll x = 0;
    char c = get();
    while (!std::isdigit(c)) {
        c = get();
    }
    while (std::isdigit(c)) {
        x = x * 10 + c - '0';
        c = get();
    }
    return x;
}

int readInt() {
    int x = 0;
    char c = get();
    while (!std::isdigit(c)) {
        c = get();
    }
    while (std::isdigit(c)) {
        x = x * 10 + c - '0';
        c = get();
    }
    return x;
}

// pku
char gc() {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 &&
            (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

inline ll read() {
    ll x = 0;
    char ch = gc();
    bool positive = 1;
    for (; !isdigit(ch); ch = gc())
        if (ch == '-')
            positive = 0;
    for (; isdigit(ch); ch = gc())
        x = x * 10 + ch - '0';
    return positive ? x : -x;
}