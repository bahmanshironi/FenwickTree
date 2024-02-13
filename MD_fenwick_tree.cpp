// Bahman Shironi
#include <bits/stdc++.h>

using namespace std;

struct fenwick_MD {
    vector<vector<long long>> bit;
    int D;
    int N;
    vector<int> point2;
    int index;
    vector<int> point1;
    long long val;

    void get_D_N(int d, int n) {
        D = d;
        N = n;
        int npowd = 1;
        for (int i = 0; i < D; i++) {
            npowd *= N;
            point1.push_back(0);
            point2.push_back(0);
        }
        for (int i = 0; i < (1 << D); i++) {
            vector<long long> tmp;
            bit.push_back(tmp);
            for (int j = 0; j <= npowd; j++)
                bit[i].push_back(0);
        }
    }

    void which_index() {
        index = 0;
        int tmp = 1;
        for (int i = 0; i < D; i++) {
            index += point2[i] * tmp;
            tmp *= N + 1;
        }
    }

    void add_point(int d) {
        for (point2[d] = point1[d]; point2[d] <= N; point2[d] += (point2[d] & (-point2[d]))) {
            if (d < D - 1)
                add_point(d + 1);
            else {
                which_index();
                long long tmp = val;
                for (int msk = 0; msk < (1 << D); msk++) {
                    for (int i = 0; i < D && msk; i++)
                        if (msk & (1 << i)) {
                            tmp *= point2[i] - point1[i] + 1;
                            break;
                        } else
                            tmp /= point2[i] - point1[i] + 1;

                    bit[msk][index] += tmp;
                }
            }
        }
    }

    void add(vector<int> pointx, vector<int> pointy, long long VAL) {
        for (int msk = 0; msk < (1 << D); msk++) {
            for (int i = 0; i < D; i++)
                if (msk & (1 << i)) {
                    point1[i] = pointy[i] + 1;
                    break;
                } else
                    point1[i] = pointx[i];

            val = __builtin_parity(msk) ? -VAL : VAL;
            add_point(0);
        }
    }

    void ask_point(int d) {
        for (point2[d] = point1[d]; point2[d]; point2[d] -= (point2[d] & (-point2[d]))) {
            if (d < D - 1)
                ask_point(d + 1);
            else {
                which_index();
                for (int msk = 0; msk < (1 << D); msk++) {
                    long long tmp = 1;
                    for (int i = 0; i < D; i++)
                        if (!(msk & (1 << i)))
                            tmp *= point1[i] - point2[i];

                    val += bit[msk][index] * tmp;
                }
            }
        }
    }

    long long ask(vector<int> pointx, vector<int> pointy) {
        long long res = 0;
        for (int msk = 0; msk < (1 << D); msk++) {
            for (int i = 0; i < D; i++)
                if (msk & (1 << i)) {
                    point1[i] = pointx[i] - 1;
                    break;
                } else
                    point1[i] = pointy[i];

            val = 0;
            ask_point(0);
            val *= __builtin_parity(msk) ? -1 : 1;
            res += val;
        }
        return res;
    }
} bit, bit2, bit3;

const int MX = 1e5 + 1, MX2 = 1e3 + 1, MX3 = 1e2 + 1;

long long arr[MX], ar2[MX2][MX2], ar3[MX3][MX3][MX3];

int main() {
    srand(chrono::steady_clock::now().time_since_epoch().count());

    bit.get_D_N(1, MX - 1);
    bit2.get_D_N(2, MX2 - 1);
    bit3.get_D_N(3, MX3 - 1);

    for (int q = 100000; q; q--) {
        int typ = rand() % 2;
        int x1 = rand() % (MX - 1) + 1;
        int x2 = rand() % (MX - 1) + 1;
        int val = rand() % 1000000 - (500000);

        if (x1 > x2)
            swap(x1, x2);

        vector<int> px = {x1}, py = {x2};

        if (typ) {
            for (int i = x1; i <= x2; i++)
                arr[i] += val;

            bit.add(px, py, val);
        } else {
            long long sum = 0;
            for (int i = x1; i <= x2; i++)
                sum += arr[i];

            if (sum != bit.ask(px, py)) {
                cout << "1D Not Successful" << endl;
                goto failed1;
            }
        }
    }
    cout << "1D Successful" << endl;
failed1:;
    for (int q = 10000; q; q--) {
        int typ = rand() % 2;
        int x1 = rand() % (MX2 - 1) + 1, y1 = rand() % (MX2 - 1) + 1;
        int x2 = rand() % (MX2 - 1) + 1, y2 = rand() % (MX3 - 1) + 1;
        int val = (rand() % 1000000) - 500000;

        if (x2 < x1)
            swap(x1, x2);
        if (y2 < y1)
            swap(y1, y2);

        vector<int> px = {x1, y1}, py = {x2, y2};

        if (typ) {
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++)
                    ar2[i][j] += val;

            bit2.add(px, py, val);
        } else {
            long long sum = 0;
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++)
                    sum += ar2[i][j];

            if (sum != bit2.ask(px, py)) {
                cout << "2D Not Successful" << endl;
                goto failed2;
            }
        }
    }
    cout << "2D Successful" << endl;
failed2:;
    for (int q = 10000; q; q--) {
        int typ = rand() % 2;
        int x1 = rand() % (MX3 - 1) + 1, y1 = rand() % (MX3 - 1) + 1, z1 = rand() % (MX3 - 1) + 1;
        int x2 = rand() % (MX3 - 1) + 1, y2 = rand() % (MX3 - 1) + 1, z2 = rand() % (MX3 - 1) + 1;
        int val = (rand() % 1000000) - 500000;

        if (x2 < x1)
            swap(x1, x2);
        if (y2 < y1)
            swap(y1, y2);
        if (z2 < z1)
            swap(z1, z2);

        vector<int> px = {x1, y1, z1}, py = {x2, y2, z2};

        if (typ) {
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++)
                    for (int t = z1; t <= z2; t++)
                        ar3[i][j][t] += val;

            bit3.add(px, py, val);
        } else {
            long long sum = 0;
            for (int i = x1; i <= x2; i++)
                for (int j = y1; j <= y2; j++)
                    for (int t = z1; t <= z2; t++)
                        sum += ar3[i][j][t];

            if (sum != bit3.ask(px, py)) {
                cout << "3D Not Successful" << endl;
                goto failed3;
            }
        }
    }
    cout << "3D Successful" << endl;
failed3:;
    return 0;
}
