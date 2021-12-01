#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ldb long double
#define x first
#define y second
#define p pair<ll, ll>
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
const long long MAXX = 1e7;

class Fenwick{
    public:
    ll n;
    vector<ll> fw1, fw2;
    Fenwick(ll n){
        this->n = n;
        fw1.assign(n + 1, 0);
        fw2.assign(n + 1, 0);
    }
    void updatePoint(vector<ll>& fw, ll u, ll v) {
        ll idx = u;
        while (idx <= n) {
            fw[idx] += v;
            idx += (idx & (-idx));
        }
    }

    void updateRange(ll l, ll r, ll v) {
        updatePoint(fw1, l, (n - l + 1) * v);
        updatePoint(fw1, r + 1, -(n - r) * v);
        updatePoint(fw2, l, v);
        updatePoint(fw2, r + 1, -v);
    }

    ll getSum(vector<ll>& fw, ll u) {
        ll idx = u, ans = 0;
        while (idx > 0) {
            ans += fw[idx];
            idx -= (idx & (-idx));
        }
        return ans;
    }

    ll prefixSum(ll u) {
        return getSum(fw1, u) - getSum(fw2, u) * (n - u);
    }

    ll rangeSum(ll l, ll r) {
        return prefixSum(r) - prefixSum(l - 1);
    }
    void check(){
        for(auto it:fw1) cout << it << ' ';
        cout << '\n';
        for(auto it:fw2) cout << it << ' ';
        cout << '\n';
    }
};

void solve(){
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    Fenwick fw(100001);
    for(ll i = 1; i <= n; i++){
        cin >> a[i];
        fw.updatePoint(fw.fw1, i, a[i]);
    } 

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