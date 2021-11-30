#include <algorithm>
#include <bits/stdc++.h>
#include <complex>
#include <new>
#include <utility>

using namespace std;

#define ll long long
#define ldb long double
#define fx first
#define sy second
#define pi pair<ll, ll>
#define vt vector<ll> 
#define pb push_back
#define all(x) x.begin(), x.end()
#define tp pair<ll, pair<ll, ll>>
#define fi first
#define se second.first
#define th second.second
#define T double
#define x real()
#define y imag()
#define pt complex<double>

const long long MOD = 1000000007;
const long double PI = 3.141592653589793238462643383279502884;
const long long INF = 1e18;

T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}
//Translation
pt translate(pt v, pt p) {
    return p + v;
}
//Scaling
pt scale(pt c, double factor, pt p) {
    return c + (p - c) * factor;
}
//Rotation
pt rotate(pt p, double a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}
//tich vo huong
T dot(pt v, pt w) {
    return v.x*w.x + v.y*w.y;
}
pt perp(pt p) {
    return {-p.y, p.x};
}
// check two vector are perpendicular
bool isPerp(pt v, pt w) { 
    return dot(v,w) == 0;
}
double angle(pt v, pt w) {
    double cosTheta = dot(v,w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}
T cross(pt v, pt w) {
    return v.x*w.y - v.y*w.x;
}
// left > 0 | rigth < 0 | collinear = 0
T orient(pt a, pt b, pt c) {
    return cross(b-a,c-a);
}
bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a,b,c) != 0);
    if (orient(a,b,c) < 0) swap(b,c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}
// calculate remaining angle
double orientedAngle(pt a, pt b, pt c) {
    if(orient(a,b,c) >= 0) return angle(b-a, c-a);
    else return 2*PI - angle(b-a, c-a);
}
// check convex with an ordered set of points
bool isConvex(vector<pt> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}
//Lines
struct line {
    pt v; T c;
    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // From equation ax+by=c
    line(T a, T b, T _c) {
        pt tmp{b, -a};
        v = tmp;
        c = _c;
    }
    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v,p)) {}
    // Will be defined later:
    // - these work with T = int

    // Side and distance
    // check if p is on the positive or negative side of the line
    T side(pt p){
        return cross(v, p)-c;
    }
    // distance from point to line
    double dist(pt p){
        return abs(side(p)) / abs(v);
    }
    // dist(pt p) ^ 2
    double sqDist(pt p) {
        return side(p)*side(p) / (double)sq(v);
    }
    // find the line perpendicular to the point p
    line perpThrough(pt p) {
        return {p, p + perp(v)};
    }

    bool cmpProj(pt p, pt q) {
        return dot(v,p) < dot(v,q);
    }
    // translate the line along the vector t
    line translate(pt t) {
        return {v, c + cross(v,t)};
    }
    // - these require T = double
    // shifting line l to the left by a certain distance dist (right is -dist)
    line shiftLeft(double dist) {
        return {v, c + dist*abs(v)};
    }
    // hình chiếu của điểm p trên đường thẳng
    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }
    // điểm đối xứng của điểm p qua đường thẳng
    pt refl(pt p) {
        return abs(p - perp(v) * side(p) / sq(v)) * 2;
    }
};
// Line intersection
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
    return true;
}
//Segments
bool inDisk(pt a, pt b, pt p) {
    return dot(a-p, b-p) <= 0;
}
//check point p is in segment ab 
bool onSegment(pt a, pt b, pt p) {
    return orient(a,b,p) == 0 && inDisk(a,b,p);
}
// segment intersection
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    double  oa = orient(c,d,a),
            ob = orient(c,d,b),
            oc = orient(a,b,c),
            od = orient(a,b,d);
    // Proper intersection exists iff opposite signs
    if (oa*ob < 0 && oc*od < 0) {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}
// To create sets of points we need a comparison function
struct cmpX {
    bool operator()(pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};
set<pt,cmpX> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (properInter(a,b,c,d,out)) return {out};
    set<pt,cmpX> s;
    if (onSegment(c,d,a)) s.insert(a);
    if (onSegment(c,d,b)) s.insert(b);
    if (onSegment(a,b,c)) s.insert(c);
    if (onSegment(a,b,d)) s.insert(d);
    return s;
}
// find distance from point p to segment ab
double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}
// find distance from segment cd to segment ab
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a,b,c,d,dummy)) return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d), segPoint(c,d,a), segPoint(c,d,b)});
}
//polygon
double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b-a, c-a)) / 2.0;
}
double areaPolygon(vector<pt> p) {
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n-1
    }
    return abs(area) / 2.0;
}
// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
    return p.y >= a.y;
}
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
    return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}
// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
void solve(){
    
}
int main (){
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int q = 1;
    // cin >> q;
    while(q--){
        solve();
    }
	return 0;	
}