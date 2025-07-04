#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

vector<double> ys;
int find(double y) {
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(8 * n + 10, Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            info[p] = {l, r, 0, 0};
            if (l != r) {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m + 1, r);
            }
        };
        build(1, 0, n);
    }
    void pull(int p) {
        Info &c = info[p], &a = info[2 * p], &b = info[2 * p + 1];
        if (c.cnt) c.len = ys[c.r + 1] - ys[c.l];
        else if (c.l != c.r) c.len = a.len + b.len;
        else c.len = 0;
    }
    void modify(int p, int l, int r, int x) {
        if (info[p].l >= l && info[p].r <= r) {
            info[p].cnt += x;
        } else {
            int mid = info[p].l + info[p].r >> 1;
            if (l <= mid) modify(2 * p, l, r, x);
            if (r > mid) modify(2 * p + 1, l, r, x);
        }
        pull(p);
    }
};

struct Info {
    int l, r, cnt;
    double len;
};

struct Seg {
    double x, y1, y2;
    int d;
    bool operator< (const Seg &tmp) const {
        return x < tmp.x;
    }
};

int main() {
    int t = 1, n;
    while (cin >> n, n) {
        ys.clear();
        vector<Seg> segs;
        for (int i = 0; i < n; i ++ ) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segs.push_back({x1, y1, y2, 1});
            segs.push_back({x2, y1, y2, -1});
            ys.push_back(y1), ys.push_back(y2);
        }
        sort(segs.begin(), segs.end());
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        int m = segs.size();
        SegmentTree<Info> sg((int)ys.size() - 2);
        double res = 0;
        for (int i = 0; i < m; i ++ ) {
            if (i) res += sg.info[1].len * (segs[i].x - segs[i - 1].x);
            sg.modify(1, find(segs[i].y1), find(segs[i].y2) - 1, segs[i].d);
        }
    }
    return 0;
}