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
        info.assign(4 << std::__lg(n), Info());
    }
    template<class T>
    void modify(int p, int l, int r, int x, int y, const T &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            info[p].apply(v);
            return;
        }
        int m = (l + r) / 2;
        modify(2 * p, l, m, x, y, v);
        modify(2 * p + 1, m, r, x, y, v);
    }
    template<class T>
    void modify(int x, int y, const T &v) {
        modify(1, 0, n, x, y, v);
    }
    template<class T>
    void rangeQuery(int p, int l, int r, int x, int y, T &d) {
        if (r - l == 1) {

            return;
        }
        int m = (l + r) / 2;
        rangeQuery(2 * p, l, m, x, y, d);
        rangeQuery(2 * p + 1, m, r, x, y, d);
    }
    template<class T>
    void rangeQuery(int l, int r, T &d) {
        rangeQuery(1, 0, n, l, r, d);
    }
};
template<class T>
struct Info {
    vector<T> ch;
    void apply(const T &v) {
        ch.push_back(v);
    }
};