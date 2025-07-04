struct ODT {
    map<int, int> odt;

    ODT() {
        odt[-1] = 0;
    }

    void split(int x) {
        auto it = prev(odt.upper_bound(x));
        odt[x] = it->second;
    }

    void assign(int l, int r, int v) {
        split(l);
        split(r);
        auto it = odt.find(l);
        while (it->first != r) {
            it = odt.erase(it);
        }
        odt[l] = x;
    }
};