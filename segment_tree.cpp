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

ll t[2*(int)1e5];
ll n, q;
void modify(ll l, ll r, ll value){
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) t[l++] += value;
		if(r&1) t[--r] += value;
	}
}
ll query(ll pos){
	ll res = 0;
	for(pos += n; pos > 0; pos >>= 1){
		res += t[pos];
	}
	return res;
}
void push(){
	for(int i=1; i < n; i++){
		t[i<<1] += t[i];
		t[i<<1|1] += t[i];
		t[i] = 0;
	}
}
/*
void buildTree(){
	for(int i = n-1; i > 0; i--){
		t[i] = t[i<<1] + t[i<<1|1];
	}
}
void modify(ll pos, ll value){
	for(t[pos += n] = value; pos > 1; pos >>= 1){
		t[pos >> 1] = t[pos] + t[pos^1];
	}
}
ll query(ll l, ll r){
	ll res = 0;
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) res += t[l++];
		if(r&1) res += t[--r];
	}
	return res;
}
*/
void solve(){
    
}
int main (){
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
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