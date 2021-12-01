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

class FenwickTree2d{
private:
    // Matrix to store the tree
    vector<vector<int>> ft;

public:
    // Function to get least significant bit
    int LSB(int x){
        return x & (-x);
    }

    int query(int x, int y){
        int sum = 0;
        for(int x_ = x; x_ > 0; x_ = x_ - LSB(x_)){
            for(int y_ = y; y_ > 0; y_ = y_ - LSB(y_)){
                sum = sum + ft[x_][y_];
            }
        }
        return sum;
    }

    int query(int x1, int y1, int x2, int y2){
        return (query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1));
    }

    void update(int x, int y, int value){
        // also update matrix[x][y] if needed.

        for(int x_ = x; x_ < ft.size(); x_ = x_ + LSB(x_)){
            for(int y_ = y; y_ < ft[0].size(); y_ = y_ + LSB(y_)){
                ft[x_][y_] += value;
            }
        }
    }

    FenwickTree2d(vector<vector<int>> matrix){
        int n = matrix.size();
        // matrix must not be empty.
        int m = matrix[0].size();
        // Initialize matrix ft
        ft.assign(m + 1, vector<int> (n + 1, 0));
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                update(i + 1, j + 1, matrix[i][j]);
        }
    }
};

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