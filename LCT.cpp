struct LCT {
    struct Node {
        int ch[2] {};
        int p {};
        bool rev {};
    };

    vector<Node> t;

    LCT(int n) : t(n + 1) {}

    bool isRoot(int x) {
        int p = t[x].p;
        return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void applyRev(int x) {
        if (!x) {
            return;
        }
        t[x].rev ^= 1;
        swap(t[x].ch[0], t[x].ch[1]);
    }

    void push(int x) {
        if (t[x].rev) {
            applyRev(t[x].ch[0]);
            applyRev(t[x].ch[1]);
            t[x].rev = false;
        }
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p;
        int dx = (t[p].ch[1] == x);
        int w = t[x].ch[dx ^ 1];
        if (!isRoot(p)) {
            if (t[g].ch[0] == p) {
                t[g].ch[0] = x;
            } else {
                t[g].ch[1] = x;
            }
        }
        t[x].p = g;
        t[p].ch[dx] = w;
        if (w) {
            t[w].p = p;
        }
        t[x].ch[dx ^ 1] = p;
        t[p].p = x;
    }

    void pushAll(int x) {
        if (!isRoot(x)) {
            pushAll(t[x].p);
        }
        push(x);
    }

    void splay(int x) {
        pushAll(x);
        while (!isRoot(x)) {
            int p = t[x].p, g = t[p].p;
            if (!isRoot(p)) {
                bool xr = (t[g].ch[1] == p);
                bool pr = (t[p].ch[1] == x);
                if (xr == pr) {
                    rotate(p);
                } else {
                    rotate(x);
                }
            }
            rotate(x);
        }
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            last = y;
        }
        splay(x);
    }

    void change(int x) {
        access(x);
        applyRev(x);
    }

    int find(int x) {
        access(x);
        while (true) {
            push(x);
            if (!t[x].ch[0]) break;
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        return find(u) == find(v);
    }

    void link(int u, int v) {
        change(u);
        if (find(v) != u) {
            t[u].p = v;
        }
    }

    void cut(int u, int v) {
        change(u);
        access(v);
        if (t[v].ch[0] == u && t[u].ch[1] == 0) {
            t[v].ch[0] = 0;
            t[u].p = 0;
        }
    }
};