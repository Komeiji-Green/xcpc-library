mt19937 eng(time(0));
int randInt(int a, int b) {
    uniform_int_distribution<int> dis(a, b);
    return dis(eng);
}