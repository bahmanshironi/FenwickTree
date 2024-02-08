// Bahman Shironi
// 2D fenwick tree with range update and range query

const int MX2 = 1e3 + 5;

int bit[4][MX2][MX2];

void add_point(int x, int y, int val) {
    for (int i = x; i < MX2; i += i & -i)
        for (int j = y; j < MX2; j += j & -j)
            for (int msk = 0; msk < 4; msk++) {
                int tmp_val = val;
                if (msk & 1)
                    tmp_val *= i - x + 1;
                if (msk & 2)
                    tmp_val *= j - y + 1;
                bit[msk][i][j] += tmp_val;
            }
}

void add_range(int x1, int y1, int x2, int y2, int val) {
    for (int msk = 0; msk < 4; msk++) {
        int x3 = x1, y3 = y1, coefficient = 1;
        if (msk & 1)
            x3 = x2 + 1, coefficient *= -1;
        if (msk & 2)
            y3 = y2 + 1, coefficient *= -1;
        add_point(x3, y3, val * coefficient);
    }
}

int ask_point(int x, int y) {
    int val = 0;
    for (int i = x; i; i -= i & -i)
        for (int j = y; j; j -= j & -j)
            for (int msk = 0; msk < 4; msk++) {
                int tmp_val = bit[msk][i][j];
                if ((msk & 1) == 0)
                    tmp_val *= x - i;
                if ((msk & 2) == 0)
                    tmp_val *= y - j;
                val += tmp_val;
            }
    return val;
}

int ask_range(int x1, int y1, int x2, int y2) {
    int val = 0;
    for (int msk = 0; msk < 4; msk++) {
        int x3 = x2, y3 = y2, coefficient = 1;
        if (msk & 1)
            x3 = x1 - 1, coefficient *= -1;
        if (msk & 2)
            y3 = y1 - 1, coefficient *= -1;
        val += ask_point(x3, y3) * coefficient;
    }
    return val;
}

int main() {

    return 0;
}
