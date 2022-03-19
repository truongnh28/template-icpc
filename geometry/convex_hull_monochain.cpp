#include <bits/stdc++.h>
#include <iomanip>
#include <ios>
#include <ratio>

using namespace std;

#define ll long long
#define ldb long double
#define x first
#define y second
#define p pair<ldb, ldb>
#define vt vector<ll> 
#define pb push_back
#define all(x) x.begin(), x.end()
#define tp pair<ll, pair<ll, ll>>
#define fi first
#define se second.first
#define th second.second

const long long MOD = 1000000007;
const long double PI = 3.141592653589793238462643383279502884;
const long long INF = 1e18;
bool cmp(p a, p b) {
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
// a -> b -> c đi cùng chiều kim đồng hồ
bool cw(p a, p b, p c) {
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) <= 0;
}
// a -> b -> c đi ngược chiều kim đồng hồ
bool ccw(p a, p b, p c) {
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) >= 0;
}
void convex_hull(vector<p> &points) {
	int n = points.size();
	if(n <= 2) {
		points.clear();
	}
	sort(all(points), cmp);
	p p1 = points[0], p2 = points[n - 1];
	vector<p> up, down;
	up.pb(p1);
	down.pb(p1);
	for(int i = 1; i < n; i++) {
		// thêm chuỗi trên
		if(i == n - 1 || cw(p1, points[i], p2)) {
			while(up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], points[i])) {
				up.pop_back();
			}
			up.push_back(points[i]);
		}
		// thêm chuỗi dưới 
		if(i == n - 1 || ccw(p1, points[i], p2)) {
			while(down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], points[i])) {
				down.pop_back();
			}
			down.push_back(points[i]);
		}
	}
	points.clear();
	set<p> s;
	for(int i = 0; i < (int)up.size(); i++) {
		s.insert(up[i]);
	}
	for(int i = down.size() - 2; i > 0; i--) {
		s.insert(down[i]);
	}
	for(auto it:s) points.pb(it);
}
double compute_signed_area(const vector<p> &points) {
    double area = 0;
    for(int i = 0; i < (int)points.size(); i++) {
        int j = (i+1) % points.size();
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return fabs(area / 2.0);
}
void solve(){
    int n;
    cin >> n;
    vector<p> points(n);
    for(auto &it:points) cin >> it.x >> it.y;
    convex_hull(points);
	cout << points.size() << ' ';
	if(points.size() > 2) {
		cout << setprecision(2) << fixed << compute_signed_area(points);
	} else {
		cout << "0.00";
	}
	cout << '\n';
	for(auto it:points) {
		cout << it.x << ' ' << it.y << '\n';
	}
}
int main (){
	#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\nguye\\Documents\\Code\\input.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int q = 1;
    cin >> q;
    while(q--){
        solve();
    }
	return 0;	
}