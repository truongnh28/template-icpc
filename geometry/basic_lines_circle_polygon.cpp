// #pragma once
#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
#define pb push_back
#define cl(x,v) memset((x), (v), sizeof(x))
#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#define _ << ", " <<

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<int, pii> piii;
typedef pair<ll,ll> pll;
typedef pair<ll, pll> plll;
typedef vector<int> vi;
typedef vector <vi> vii;

const ld EPS = 1e-9, PI = acos(-1.);
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f, MOD = 1e9+7;
const int N = 1e5+5;

typedef long double type;
//for big coordinates change to long long

//lớn hơn
bool ge(type x, type y) { return x + EPS > y; }
//nhỏ hơn
bool le(type x, type y) { return x - EPS < y; }
//bằng
bool eq(type x, type y) { return ge(x, y) and le(x, y); }

struct point {
    type x, y;

    point() : x(0), y(0) {}
    point(type x, type y) : x(x), y(y) {}

    point operator -() { return point(-x, -y); }
    point operator +(point p) { return point(x + p.x, y + p.y); }
    point operator -(point p) { return point(x - p.x, y - p.y); }

    point operator *(type k) { return point(k*x, k*y); }
    point operator /(type k) { return point(x/k, y/k); }

    //inner product
    type operator *(point p) { return x*p.x + y*p.y; }
    //cross product
    type operator %(point p) { return x*p.y - y*p.x; }

    bool operator ==(const point &p) const{ return x == p.x and y == p.y; }
    bool operator !=(const point &p) const{ return x != p.x  or y != p.y; }
    bool operator <(const point &p) const { return (x < p.x) or (x == p.x and y < p.y); }

    // 0 => cùng hướng
    // 1 => p ở bên trái
    // - 1 => p ở bên phải
    int dir(point o, point p) {
        type x = (*this - o) % (p - o);
        return ge(x,0) - le(x,0);
    }

    bool on_seg(point p, point q) {
        if (this->dir(p, q)) return 0;
        return ge(x, min(p.x, q.x)) and le(x, max(p.x, q.x)) and ge(y, min(p.y, q.y)) and le(y, max(p.y, q.y));
    }
    //ĐỘ DÀI
    ld abs() { return sqrt(x*x + y*y); }
    type abs2() { return x*x + y*y; }
    //KHOẢNG CÁCH GIỮA 2 ĐIỂM
    ld dist(point q) { return (*this - q).abs(); }
    type dist2(point q) { return (*this - q).abs2(); }

    ld arg() { return atan2l(y, x); }

    //Hình chiếu của 1 điểm lên vectơ y
    point project(point y) { return y * ((*this * y) / (y * y)); }

    //Hình chiếu của 1 điểm lên đường thẳng được tạo bởi 2 điểm x, y
    point project(point x, point y) { return x + (*this - x).project(y-x); }
    //Khoảng cách của 1 điểm đến 1 ĐƯỜNG thẳng được tạo bởi 2 điểm x, y
    ld dist_line(point x, point y) { return dist(project(x, y)); }
    //Khoảng cách của 1 điểm đến 1 ĐOẠN thẳng được tạo bởi 2 điểm x, y
    ld dist_seg(point x, point y) {
        return project(x, y).on_seg(x, y) ? dist_line(x, y) :  min(dist(x), dist(y));
    }

    point rotate(ld sin, ld cos) { return point(cos*x - sin*y, sin*x + cos*y); }
    point rotate(ld a) { return rotate(sin(a), cos(a)); }

    // xoay xung quanh đối số của vectơ p
    point rotate(point p) { return rotate(p.x / p.abs(), p.y / p.abs()); }

};
//HƯỚNG
int direction(point o, point p, point q) { return p.dir(o, q); }
//QUAY ngược CHIỀU KIM ĐỒNG HỒ
point rotate_ccw90(point p)   { return point(-p.y,p.x); }
//QUAY cùng CHIỀU KIM ĐỒNG HỒ
point rotate_cw90(point p)    { return point(p.y,-p.x); }

//for reading purposes avoid using * and % operators, use the functions below:
type dot(point p, point q)     { return p.x*q.x + p.y*q.y; }
type cross(point p, point q)   { return p.x*q.y - p.y*q.x; }

//diện tích tam giác * 2
type area_2(point a, point b, point c) { return fabs(cross(a,b) + cross(b,c) + cross(c,a)); }

int angle_less(const point& a1, const point& b1, const point& a2, const point& b2) {
    // góc giữa (a1 và b1) so với góc giữa (a2 và b2)
    // 1: lớn hơn
    // - 1: nhỏ hơn
    // 0: bằng nhau
    point p1(dot(   a1, b1), abs(cross(   a1, b1)));
    point p2(dot(   a2, b2), abs(cross(   a2, b2)));
    if(cross(p1, p2) < 0) return 1;
    if(cross(p1, p2) > 0) return -1;
    return 0;
}

ostream &operator<<(ostream &os, const point &p) {
    os << "(" << p.x << "," << p.y << ")"; 
    return os;
}

//lines
//hình chiếu của điểm lên đường thẳng AB
point project_point_line(point c, point a, point b) {
    ld r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    return a + (b - a)*dot(c - a, b - a)/dot(b - a, b - a);
}
//hình chiếu của điểm lên tia AB
point project_point_ray(point c, point a, point b) {
    ld r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (le(r, 0)) return a;
    return a + (b - a)*r;
}
//hình chiếu của điểm lên đoạn thẳng
point project_point_segment(point c, point a, point b) {
    ld r = dot(b - a, b - a);
    if (fabs(r) < EPS) return a;
    r = dot(c - a, b - a) / r;
    if (le(r, 0)) return a;
    if (ge(r, 1)) return b;
    return a + (b - a)*r;
}
//bắt đầu độ dài của hình chiếu
ld distance_point_line(point c, point a, point b) {
    return c.dist2(project_point_line(c, a, b));
}

ld distance_point_ray(point c, point a, point b) {
    return c.dist2(project_point_ray(c, a, b));
}

ld distance_point_segment(point c, point a, point b) {
    return c.dist2(project_point_segment(c, a, b));
}
//kết thúc độ dài của hình chiếu
ld distance_point_plane(ld x, ld y, ld z, ld a, ld b, ld c, ld d){
    return fabs(a*x + b*y + c*z - d)/sqrt(a*a + b*b + c*c);
}
//kiểm tra ab // cd
bool lines_parallel(point a, point b, point c, point d) { 
    return fabs(cross(b - a, d - c)) < EPS; 
}
//kiểm tra 4 điểm thẳng hàng
bool lines_collinear(point a, point b, point c, point d) {
  return lines_parallel(a, b, c, d) && fabs(cross(a-b, a-c)) < EPS && fabs(cross(c-d, c-a)) < EPS; 
}
//giao điểm của 2 đường thẳng
point lines_intersect(point p, point q, point a, point b) {
    point r = q - p, s = b - a, c(p % q, a % b);
    if (eq(r % s, 0)) return point(LINF, LINF);
    return point(point(r.x, s.x) % c, point(r.y, s.y) % c) / (r % s);
}

//kiểm tra 2 tia trùng nhau (LineLineIntersection) trước khi sử dụng hàm này
//giao điểm của 2 đường thẳng
point compute_line_intersection(point a, point b, point c, point d) {
    b = b - a; d = c - d; c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);
}
//kiểm tra 2 đường thẳng trùng nhau
bool line_line_intersect(point a, point b, point c, point d) {
    if(!lines_parallel(a, b, c, d)) return true;
    if(lines_collinear(a, b, c, d)) return true; 
    return false;
}


//hướng a -> b, c -> d
//kiểm tra 2 tia giao nhau
bool ray_ray_intersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (lines_collinear(a, b, c, d)) {
        if(ge(dot(b - a, d - c), 0)) return true;
        if(ge(dot(a - c, d - c), 0)) return true;
        return false;
    }
    if(!line_line_intersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(ge(dot(inters - c, d - c), 0) && ge(dot(inters - a, b - a), 0)) return true;
    return false;
}
//kiểm tra đoạn thẳng giao nhau
bool segment_segment_intersect(point a, point b, point c, point d) {
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    int d1, d2, d3, d4;
    d1 = direction(a, b, c);
    d2 = direction(a, b, d);
    d3 = direction(c, d, a);
    d4 = direction(c, d, b);
    if (d1*d2 < 0 and d3*d4 < 0) return 1;
    return a.on_seg(c, d) or b.on_seg(c, d) or
            c.on_seg(a, b) or d.on_seg(a, b);
}
//kiểm tra đoạn thẳng giao với đường thẳng
bool segment_line_intersect(point a, point b, point c, point d){
    if(!line_line_intersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(inters.on_seg(a, b)) return true;
    return false;
}

//hướng tia c -> d
//đoạn thẳng giao với tia
bool segment_ray_intersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (lines_collinear(a, b, c, d)) {
        if(c.on_seg(a, b)) return true;
        if(ge(dot(d - c, a - c), 0)) return true;
        return false;
    }
    if(!line_line_intersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(!inters.on_seg(a, b)) return false;
    if(ge(dot(inters - c, d - c), 0)) return true;
    return false; 
}

//hướng tia a -> b
//kiểm tra tia giao với đường thẳng
bool ray_line_intersect(point a, point b, point c, point d){
    if (a.dist2(c) < EPS || a.dist2(d) < EPS ||
        b.dist2(c) < EPS || b.dist2(d) < EPS) return true;
    if (!line_line_intersect(a, b, c, d)) return false;
    point inters = lines_intersect(a, b, c, d);
    if(!line_line_intersect(a, b, c, d)) return false;
    if(ge(dot(inters - a, b - a), 0)) return true;
    return false;
}
//khoảng cách giữa đoạn thẳng với đường thẳng
ld distance_segment_line(point a, point b, point c, point d){
    if(segment_line_intersect(a, b, c, d)) return 0;
    return min(distance_point_line(a, c, d), distance_point_line(b, c, d));
}
//khoảng cách giữa đoạn thẳng với tia
ld distance_segment_ray(point a, point b, point c, point d){
    if(segment_ray_intersect(a, b, c, d)) return 0;
    ld min1 = distance_point_segment(c, a, b);
    ld min2 = min(distance_point_ray(a, c, d), distance_point_ray(b, c, d));
    return min(min1, min2);
}
//khoảng cách giữa đoạn thẳng với đoạn thẳng
ld distance_segment_segment(point a, point b, point c, point d){
    if(segment_segment_intersect(a, b, c, d)) return 0;
    ld min1 = min(distance_point_segment(c, a, b), distance_point_segment(d, a, b));
    ld min2 = min(distance_point_segment(a, c, d), distance_point_segment(b, c, d));
    return min(min1, min2);
}
//khoảng cách giữa tia với đường thẳng
ld DistanceRayLine(point a, point b, point c, point d){
    if(ray_line_intersect(a, b, c, d)) return 0;
    ld min1 = distance_point_line(a, c, d);
    return min1;
}
//khoảng cách giữa tia với tia
ld DistanceRayRay(point a, point b, point c, point d){
    if(ray_ray_intersect(a, b, c, d)) return 0;
    ld min1 = min(distance_point_ray(c, a, b), distance_point_ray(a, c, d));
    return min1;
}
//khoảng cách giữa đường thẳng với đường thẳng
ld DistanceLineLine(point a, point b, point c, point d){
    if(line_line_intersect(a, b, c, d)) return 0;
    return distance_point_line(a, c, d);
}


//circle
struct circle {
    point c;
    ld r;
    circle() { c = point(); r = 0; }
    circle(point _c, ld _r) : c(_c), r(_r) {}
    //tính diện tích
    ld area() { return acos(-1.0)*r*r; }
    //tính độ dài cung tròn ứng với góc rad nào đó
    ld chord(ld rad) { return  2*r*sin(rad/2.0); }
    //diện tích hình quạt ứng với góc rad nào đó
    ld sector(ld rad) { return 0.5*rad*area()/acos(-1.0); }
    //2 đường tròn giao nhau
    bool intersects(circle other) {
        return le(c.dist(other.c), r + other.r);
    }
    //điểm nằm trong đường tròn
    bool contains(point p) { return le(c.dist(p), r); }
    //lấy điểm tiếp tuyến từ 1 điểm p đến đường tròn
    pair<point, point> getTangentPoint(point p) {
        ld d1 = c.dist(p), theta = asin(r/d1);
        point p1 = (c - p).rotate(-theta);
        point p2 = (c - p).rotate(theta);
        p1 = p1*(sqrt(d1*d1 - r*r)/d1) + p;
        p2 = p2*(sqrt(d1*d1 - r*r)/d1) + p;
        return make_pair(p1,p2);
    }
};
//đường tròn ngoại tiếp tam giác
circle circumcircle(point a, point b, point c) {
    circle ans;
    point u = point((b - a).y, -(b - a).x);
    point v = point((c - a).y, -(c - a).x);
    point n = (c - b)*0.5;
    ld t = cross(u,n)/cross(v,u);
    ans.c = ((a + c)*0.5) + (v*t);
    ans.r = ans.c.dist(a);
    return ans;
}
//tìm tâm của đường tròn ngoại tiếp tam giác
point compute_circle_center(point a, point b, point c) {
    //circumcenter
    b = (a + b)/2;
    c = (a + c)/2;
    return compute_line_intersection(b, b + rotate_cw90(a - b), c, c + rotate_cw90(a - c));
}
//kiểm tra điểm nằm bên trong đường tròn
// 0 bên trong
// 1 nằm trên đường tròn
// 2 bên ngoài
int inside_circle(point p, circle c) {
    if (fabs(p.dist(c.c) - c.r)<EPS) return 1;
    else if (p.dist(c.c) < c.r) return 0;
    else return 2;
}
//đường tròn nội tiếp tam giác
circle incircle( point p1, point p2, point p3 ) {
    ld m1 = p2.dist(p3);
    ld m2 = p1.dist(p3);
    ld m3 = p1.dist(p2);
    point c = (p1*m1 + p2*m2 + p3*m3)*(1/(m1 + m2 + m3));
    ld s = 0.5*(m1 + m2 + m3);
    ld r = sqrt(s*(s - m1)*(s - m2)*(s - m3))/s;
    return circle(c, r);
}
//tìm kiếm đường tròn có bán kính bao quanh các điểm
circle minimum_circle(vector<point> p) {
    random_shuffle(p.begin(), p.end());
    circle C = circle(p[0], 0.0);
    for(int i = 0; i < (int)p.size(); i++) {
        if (C.contains(p[i])) continue;
        C = circle(p[i], 0.0);
        for(int j = 0; j < i; j++) {
            if (C.contains(p[j])) continue;
            C = circle((p[j] + p[i])*0.5, 0.5*p[j].dist(p[i]));
            for(int k = 0; k < j; k++) {
                if (C.contains(p[k])) continue;
                C = circumcircle(p[j], p[i], p[k]);
            }
        }
    }
    return C;
}
//Với tọa độ của tâm một vòng tròn và bán kính của nó, và phương trình của một đường thẳng
// tìm các giao điểm của đường thẳng với đường tròn 
vector<point> circle_line_intersection(point a, point b, point c, ld r) {
    vector<point> ret;
    b = b - a;
    a = a - c;
    ld A = dot(b, b);
    ld B = dot(a, b);
    ld C = dot(a, a) - r*r;
    ld D = B*B - A*C;
    if (D < -EPS) return ret;
    ret.push_back(c + a + b*(sqrt(D + EPS) - B)/A);
    if (D > EPS)
        ret.push_back(c + a + b*(-B - sqrt(D))/A);
    return ret;
}
//tìm tập giao điểm của 2 đường tròn với nhau
vector<point> circle_circle_intersection(point a, point b, ld r, ld R) {
    vector<point> ret;
    ld d = sqrt(a.dist2(b));
    if (d > r + R || d + min(r, R) < max(r, R)) return ret;
    ld x = (d*d - R*R + r*r)/(2*d);
    ld y = sqrt(r*r - x*x);
    point v = (b - a)/d;
    ret.push_back(a + v*x + rotate_ccw90(v)*y);
    if (y > 0)
        ret.push_back(a + v*x - rotate_ccw90(v)*y);
    return ret;
}

//polygon
//Graham scan with bugs, not safe, prefer monotone chain!
point origin;

//radial function for graham scan, for a generic radial sort see radial_sort.cpp
bool radial(point p, point q) {
    int dir = p.dir(origin, q);
    return dir > 0 or (!dir and p.on_seg(origin, q));
}

// Graham Scan O(nlog(n))
vector<point> graham_hull(vector<point> pts) {
    vector<point> ch(pts.size());
    point mn = pts[0];

    for(point p : pts) if (p.y < mn.y or (p.y == mn.y and p.x < p.y)) mn = p;

    origin = mn;
    sort(pts.begin(), pts.end(), radial);

    int n = 0;

    // IF: Convex hull without collinear points
    for(point p : pts) {
        while (n > 1 and ch[n-1].dir(ch[n-2], p) < 1) n--;
        ch[n++] = p;
    }

    /* ELSE IF: Convex hull with collinear points
    for(point p : pts) {
    while (n > 1 and ch[n-1].dir(ch[n-2], p) < 0) n--;
    ch[n++] = p;
    }
    for(int i=pts.size()-1; i >=1; --i)
    if (pts[i] != ch[n-1] and !pts[i].dir(pts[0], ch[n-1]))
        ch[n++] = pts[i];
    // END IF */

    ch.resize(n);
    return ch;
}

//Monotone chain O(nlog(n))
#define REMOVE_REDUNDANT
#ifdef REMOVE_REDUNDANT
bool between(const point &a, const point &b, const point &c) {
    return (fabs(area_2(a,b,c)) < EPS && (a.x-b.x)*(c.x-b.x) <= 0 && (a.y-b.y)*(c.y-b.y) <= 0);
}
#endif

void monotone_hull(vector<point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<point> up, dn;
    for (int i = 0; i < (int)pts.size(); i++) {
        while (up.size() > 1 && area_2(up[up.size()-2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area_2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

    #ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2) return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < (int)pts.size(); i++) {
        if (between(dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
    #endif
}

//avoid using long double for comparisons, change type and remove division by 2
// tính diện tích đa giác
ld compute_signed_area(const vector<point> &p) {
    ld area = 0;
    for(int i = 0; i < (int)p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

ld compute_area(const vector<point> &p) {
    return fabs(compute_signed_area(p));
}
//tính chu vi
ld compute_perimeter(vector<point> &p) {
    ld per = 0;
    for(int i = 0; i < (int)p.size(); i++) {
        int j = (i+1) % p.size();
        per += p[i].dist(p[j]);
    }
    return per;
}

//not tested
//tìm trọng tâm của đa giác
point compute_centroid(vector<point> &p) {
    point c(0,0);
    ld scale = 6.0 * compute_signed_area(p);
    for (int i = 0; i < (int)p.size(); i++){
        int j = (i+1) % p.size();
        c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
}

//O(n^2)
bool is_simple(const vector<point> &p) {
    for (int i = 0; i < (int)p.size(); i++) {
        for (int k = i+1; k < (int)p.size(); k++) {
            int j = (i+1) % p.size();
            int l = (k+1) % p.size();
            if (i == l || j == k) continue;
            if (segment_segment_intersect(p[i], p[j], p[k], p[l])) 
                return false;
        }
    }
    return true;
}
//điểm trong tam giác
bool point_in_triangle(point a, point b, point c, point cur){
    ll s1 = abs(cross(b - a, c - a));
    ll s2 = abs(cross(a - cur, b - cur)) + abs(cross(b - cur, c - cur)) + abs(cross(c - cur, a - cur));
    return s1 == s2;
}

void sort_lex_hull(vector<point> &hull){
    int n = hull.size();

    //Sort hull by x
    int pos = 0;
    for(int i = 1; i < n; i++) if(hull[i] <  hull[pos]) pos = i;
    rotate(hull.begin(), hull.begin() + pos, hull.end());
}

// xác định xem điểm nằm trong hay nằm trên ranh giới của đa giác (O (logn))
// điểm nằm trong đa giác
bool point_in_convex_polygon(vector<point> &hull, point cur){
    int n = hull.size();
    // Trường hợp góc: trỏ ra ngoài hầu hết các nêm bên trái và bên phải
    if(cur.dir(hull[0], hull[1]) != 0 && cur.dir(hull[0], hull[1]) != hull[n - 1].dir(hull[0], hull[1]))
        return false;
    if(cur.dir(hull[0], hull[n - 1]) != 0 && cur.dir(hull[0], hull[n - 1]) != hull[1].dir(hull[0], hull[n - 1]))
        return false;

    // Tìm kiếm nhị phân để tìm xem nó nằm giữa
    int l = 1, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        if(cur.dir(hull[0], hull[mid]) <= 0)l = mid;
        else r = mid;
    }
    return point_in_triangle(hull[l], hull[l + 1], hull[0], cur);
}

// xác định xem điểm có nằm trên ranh giới của đa giác hay không (O (N))
bool point_on_polygon(vector<point> &p, point q) {
    for (int i = 0; i < (int)p.size(); i++)
    if (q.dist2(project_point_segment(p[i], p[(i+1)%p.size()], q)) < EPS) return true;
    return false;
}

//Shamos - Hoey for test polygon simple in O(nlog(n))
inline bool adj(int a, int b, int n) {return (b == (a + 1)%n or a == (b + 1)%n);}

struct edge{
    point ini, fim;
    edge(point ini = point(0,0), point fim = point(0,0)) : ini(ini), fim(fim) {}
};

//< here means the edge on the top will be at the begin
bool operator < (const edge& a, const edge& b) {
    if (a.ini == b.ini) return direction(a.ini, a.fim, b.fim) < 0;
    if (a.ini.x < b.ini.x) return direction(a.ini, a.fim, b.ini) < 0;
    return direction(a.ini, b.fim, b.ini) < 0;
}

bool is_simple_polygon(const vector<point> &pts){
    vector <pair<point, pii>> eve;
    vector <pair<edge, int>> edgs;
    set <pair<edge, int>> sweep;
    int n = (int)pts.size();
    for(int i = 0; i < n; i++){
        point l = min(pts[i], pts[(i + 1)%n]);
        point r = max(pts[i], pts[(i + 1)%n]);
        eve.pb({l, {0, i}});
        eve.pb({r, {1, i}});
        edgs.pb(make_pair(edge(l, r), i));
    }
    sort(eve.begin(), eve.end());
    for(auto e : eve){
        if(!e.nd.st){
            auto cur = sweep.lower_bound(edgs[e.nd.nd]);
            pair<edge, int> above, below;
            if(cur != sweep.end()){
                below = *cur;
                if(!adj(below.nd, e.nd.nd, n) and segment_segment_intersect(pts[below.nd], pts[(below.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
                    return false;
            }
            if(cur != sweep.begin()){
                above = *(--cur);
                if(!adj(above.nd, e.nd.nd, n) and segment_segment_intersect(pts[above.nd], pts[(above.nd + 1)%n], pts[e.nd.nd], pts[(e.nd.nd + 1)%n]))
                    return false;
            }
            sweep.insert(edgs[e.nd.nd]);
        }
        else{
            auto below = sweep.upper_bound(edgs[e.nd.nd]);
            auto cur = below, above = --cur;
            if(below != sweep.end() and above != sweep.begin()){
                --above;
                if(!adj(below->nd, above->nd, n) and segment_segment_intersect(pts[below->nd], pts[(below->nd + 1)%n], pts[above->nd], pts[(above->nd + 1)%n]))
                    return false;
            }
            sweep.erase(cur);
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<point> a(n);
    for(auto &it:a) cin >> it.x >> it.y;
    // for(auto it:a) cout << it.x << ' ' << it.y << '\n';
    cout << graham_hull(a).size();
    // for(auto it:) cout << it << '\n';
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