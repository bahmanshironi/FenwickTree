//Bahman Shironi
//1D fenwick tree with range update and range query

const int MX1 = 2e5 + 10;

int bit1[MX1];
int bit2[MX1];

void add_point(int id, int val) {
    int distance = 0;
    while (id < MX1) {
        bit1[id] += val * distance;
        bit2[id] += val;
        distance += id & -id;
        id += id & -id;
    }
}

void add_range(int l, int r, int val) {
    add_point(l, val);
    add_point(r + 1, -val);
}

int ask_point(int id) {
    int sum = 0;
    int distance = 0;
    while (id > 0) {
        sum += bit1[id];
        sum += bit2[id] * distance;
        distance += id & -id;
        id -= id & -id;
    }
    return sum;
}

int ask_range(int l, int r) {
    return ask_point(r) - ask_point(l - 1);
}

int main() {

    return 0;
}