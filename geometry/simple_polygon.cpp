#include <bits/stdc++.h>

using namespace std;

struct Point2d {
    int x;
    int y;

    Point2d(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point2d(const Point2d& p) {
        this->x = p.x;
        this->y = p.y;
    }

    Point2d& operator = (const Point2d& p) {
        this->x = p.x;
        this->y = p.y;
        return *this;
    }

};

int direction(Point2d pi, Point2d pj, Point2d pk) {
    return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
}

bool onSegment(Point2d pi, Point2d pj, Point2d pk) {
    if (std::min(pi.x, pj.x) <= pk.x && pk.x <= std::max(pi.x, pj.x)
        && std::min(pi.y, pj.y) <= pk.y && pk.y <= std::max(pi.y, pj.y)) {
        return true;
    } else {
        return false;
    }
}

bool segmentIntersect(Point2d p1, Point2d p2, Point2d p3, Point2d p4) {
    int d1 = direction(p3, p4, p1);
    int d2 = direction(p3, p4, p2);
    int d3 = direction(p1, p2, p3);
    int d4 = direction(p1, p2, p4);

    if (((d1 >= 0 && d2 <= 0) || (d1 <= 0 && d2 >= 0)) && ((d3 >= 0 && d4 <= 0) || (d3 <= 0 && d4 >= 0))) {
        return true;
    } else if (d1 == 0 && onSegment(p3, p4, p1)) {
        return true;
    } else if (d2 == 0 && onSegment(p3, p4, p2)) {
        return true;
    } else if (d3 == 0 && onSegment(p1, p2, p3)) {
        return true;
    } else if (d4 == 0 && onSegment(p1, p2, p4)) {
        return true;
    } else {
        return false;
    }
}

struct BoundingBox {
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    
    BoundingBox(int xmin, int xmax, int ymin, int ymax) {
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
    }

    BoundingBox() {
        this->xmin = std::numeric_limits<int>::max();
        this->xmax = std::numeric_limits<int>::min();
        this->ymin = std::numeric_limits<int>::max();
        this->ymax = std::numeric_limits<int>::min();
    }
};

struct Polygon {
    std::vector<Point2d> points;
    BoundingBox bbox;

    Polygon(std::vector<Point2d>& points): points(points) {
        calcBoundingBox(points);
    }

    bool inBoundingBox(Point2d point) {
        if (point.x <= bbox.xmin || point.x >= bbox.xmax || point.y <= bbox.ymin || point.y >= bbox.ymax) {
            return false;
        } else {
            return true;
        }
    }

    bool inPolygon(Point2d point) {
        if (!inBoundingBox(point)) {
            return false;
        }

        //create a ray (segment) starting from the given point, 
        //and to the point outside of polygon.
        Point2d outside(bbox.xmin - 1, bbox.ymin);
        int intersections = 0;
        //check intersections between the ray and every side of the polygon.
        for (int i = 0; i < (int)points.size() - 1; ++i) {
            if (segmentIntersect(point, outside, points.at(i), points.at(i + 1))) {
                intersections++;
            }
        }
        //check the last line
        if (segmentIntersect(point, outside, points.at(points.size() - 1), points.at(0))) {
            intersections++;
        }
        return (intersections % 2 != 0);
    }
    
private:

    void calcBoundingBox(std::vector<Point2d> points) {
        for (auto &point : points) {
            if (point.x < bbox.xmin) {
                bbox.xmin = point.x;
            } else if (point.x > bbox.xmax) {
                bbox.xmax = point.x;
            }
            if (point.y < bbox.ymin) {
                bbox.ymin = point.y;
            } else if (point.y > bbox.ymax) {
                bbox.ymax = point.y;
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Point2d> poly;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        poly.push_back(Point2d(x, y));
    } 
    Polygon polygon = Polygon(poly);
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if(polygon.inPolygon(Point2d(x, y))) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
int main () {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int q = 1;
    // cin >> q;
    while(q--){
        solve();
    }
    return 0;    
}