/*
    F(2 * n) = F(n) * F(n) + F(n - 1) * F(n - 1)
    F(2 * n + 1) = F(n) * F(n + 1) + F(n) * F(n - 1)
    O(4 * log(n))
 */
#include <bits/stdc++.h>
#include <cstdio>
#include <stdio.h>

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

map<ll, ll> F;
ll fibo(ll n){
    if(F.count(n)) return F[n];
    ll k = n/2;
    if(n%2 == 0){
        return F[n] = ((fibo(k) * fibo(k)) % MOD + (fibo(k - 1) * fibo(k - 1)) % MOD) % MOD;
    }
    else{
        return F[n] = ((fibo(k) * fibo(k + 1)) % MOD + (fibo(k) * fibo(k - 1)) % MOD) % MOD; 
    }
}

void solve(){
    F[0] = F[1] = 1;
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