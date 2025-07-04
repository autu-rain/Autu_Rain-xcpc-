struct Point {
    i64 x;
    i64 y;
    Point() : x{0}, y{0} {}
    Point(i64 x_, i64 y_) : x{x_}, y{y_} {}
};

i64 dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

i64 cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point operator+(Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator-(Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

auto getHull(std::vector<Point> p) {
    std::sort(p.begin(), p.end(),
    [&](auto a, auto b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    std::vector<Point> hi, lo;
    for (auto p : p) {
        while (hi.size() > 1 && cross(hi.back() - hi[hi.size() - 2], p - hi.back()) >= 0) {
            hi.pop_back();
        }
        while (!hi.empty() && hi.back().x == p.x) {
            hi.pop_back();
        }
        hi.push_back(p);
        while (lo.size() > 1 && cross(lo.back() - lo[lo.size() - 2], p - lo.back()) <= 0) {
            lo.pop_back();
        }
        if (lo.empty() || lo.back().x < p.x) {
            lo.push_back(p);
        }
    }

    std::vector<Point> hull;
    int n = p.size();
    for (int i = 0; i < n; i ++ ) {
        while (hull.size() > 1 && cross(hull.back() - hull[hull.size() - 2], p[i] - hull.back()) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    int m = hull.size();
    for (int i = n - 2; i; i -- ) {
        while (hull.size() > m && cross(hull.back() - hull[hull.size() - 2], p[i] - hull.back()) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }
    return std::make_pair(hi, lo);
}

const double inf = INFINITY;