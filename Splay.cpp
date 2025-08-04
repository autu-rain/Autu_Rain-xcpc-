struct Info {

};

Info operator+(const Info &a, const Info &b) {
    Info c;

    return c;
}
struct Node {
    Node *ch[2], *p;
    Info val;
    Info tot;
    Node() : ch{nullptr, nullptr}, p(nullptr) {}
};
void pull(Node *t) {
    t->tot = (t->ch[0] ? t->ch[0]->tot : Info {}) + t->val + (t->ch[1] ? t->ch[1]->tot : Info {});
}
bool isroot(Node *t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) {
    return t->p->ch[1] == t;
}
void rotate(Node *t) {
    Node *q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    pull(q);
}
void update(Node *t) {

    pull(t);
}
void splay(Node *t) {
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            } else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}
void add(Node *t, Info s) {

}
void del(Node *t, Info s) {

}
void access(Node *t, int v) {

}