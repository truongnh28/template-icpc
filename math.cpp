#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

// Tính gcd (ước chung lớn nhất)
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Tính lcm (bội chung nhỏ nhất)
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// tính lg2(a)
int lg2(ll a) {
  return 63 - __builtin_clzll(a);
}

// tính số lượng bit 1
int bitcount(ll a) {
  return __builtin_popcountll(a);
}

// tính ceil(a / b)
ll ceildiv(ll a, ll b) {
  if (b < 0) return ceildiv(-a, -b);
  if (a >= 0) return  a / b;
  return -(ll)(((ull)(-a) + b - 1) / b);
}

// Calculate a * b mod c (or a ^ b mod c) for 0 <= a, b, c <= 7.2 * 10^18
// O(1) for modmul, O(logb) for modpow
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

// (a ^ b) % m in O(logb) where b is small
ll modpow(ll a, ll b, ll m) {
  ll r = 1;
  for (a %= m; b; b >>= 1, a = (a * a) % m) if (b & 1) r = (r * a) % m;
  return r;
}

// return the smallest x > 0 such that a^x === b (mod m), or -1 if no
// such x exists. modLog(a, 1, m) can be used to calculate the order of a
// Time O(sqrt(m))
ll modLog(ll a, ll b, ll m) {
  ll n = (ll) sqrt(m) + 1, e = 1, f = 1, j = 1;
  unordered_map<ll, ll> A;
  while (j <= n && (e = f = e * a % m) != b % m)
    A[e * b % m] = j++;
  if (e == b % m) return j;
  if (__gcd(m, e) == __gcd(m, b)) 
    rep(i,2,n+2) if (A.count(e = e * f % m))
      return n * i - A[e];
  return -1;
}

// Find x such that x^2 === a (mod p) (-x gives the other solution)
// Time: O(log^2 (p)) worst case, O(logp) for most p
ll sqrt(ll a, ll p) {
  // modpow using in this algorithm is for ll, not for ull
  a %= p; if (a < 0) a += p;
  if (a == 0) return 0;
  assert(modpow(a, (p-1)/2, p) == 1); // else no solution
  if (p % 4 == 3) return modpow(a, (p+1)/4, p);
  // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  ll s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0)
    ++r, s /= 2;
  /// find a non-square mod p
  while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;
  ll x = modpow(a, (s + 1) / 2, p);
  ll b = modpow(a, s, p), g = modpow(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m)
      t = t * t % p;
    if (m == 0) return x;
    ll gs = modpow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
  }
}

// find a pair (c, d) such that ac + bd = gcd(a, b)
pair<ll, ll> extended_gcd(ll a, ll b) {
  if (b == 0) return {1, 0};
  auto t = extended_gcd(b, a % b);
  return {t.second, t.first - t.second * (a / b)};
}

// find x in [0, m) such that ax === gcd(a, m) (mod m)
ll modinverse(ll a, ll m) {
  return (extended_gcd(a, m).first % m + m) % m;
}

// calculate mod inverse in range 1 ~ n
void calc_range_modinv(int n, int mod, ll ret[]) {
  ret[1] = 1LL;
  for (int i = 2; i <= n; ++i)
    ret[i] = (ll)(mod - mod / i) * ret[mod % i] % mod;
  return ret;
}

// Find fibonacci in range [0, n]
vector<ll> fibonacci(int n) {
  vector<ll>f(n);
  f[0] = 0; f[1] = 1;
  for (int i = 2; i <= n; ++i) f[i] = f[i - 1] + f[i - 2];
  return f;
}

// Find n-th fibonnacci in O(logN), call fib(n)
void multiply(int F[2][2], int M[2][2]);
void power(int F[2][2], int n);
int fib(int n) {
  int F[2][2] = {{1, 1}, {1, 0}};
  if (n == 0)
    return 0;
  power(F, n - 1);

  return F[0][0];
}
void power(int F[2][2], int n) {
  if(n == 0 || n == 1)
    return;
  int M[2][2] = {{1, 1}, {1, 0}};
   
  power(F, n / 2);
  multiply(F, F);
   
  if (n % 2 != 0)
    multiply(F, M);
}
void multiply(int F[2][2], int M[2][2]) {
  int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
  int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
  int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
  int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
   
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}

// Find nth-fibonacci in O(logN) 
map<int, ll> f;
int fib(int n) {
  if (n == 0)
    return 0;
  if (n == 1 || n == 2)
    return (f[n] = 1);
  if (f[n])
    return f[n];
  int k = (n & 1)? (n+1)/2 : n/2;
  f[n] = (n & 1)? (fib(k)*fib(k) + fib(k-1)*fib(k-1))
         : (2*fib(k-1) + fib(k))*fib(k);
  return f[n];
}
// tính số catalan
vector<ll> catalan(int n) {
  vector<ll>cat(n);
  cat[0] = 1;
  for (int i = 1; i <= n; ++i) cat[n] = (2 * (2 * n - 1) / (n + 1)) * cat[n - 1];
  return cat;
}

// Calculate A ^ B mod C when A or B very large
// support for calculate when a and b is very large
ll aModM(string s, ll mod) {
  ll res = 0;
  for (int i = 0; i < (int)s.length(); ++i) {
    res = (res * 10 + (s[i] - '0'));
    res %= mod;
  }
  return res;
}
// 'a' very large O(len(a) + log(b))
ll ApowBmodM(string &a, ll b, ll m) {
  ll ans = aModM(a, m);
  return modpow(ans, b, m);
}
// 'b' very large và 'm' is a prime O(len(b))
ll ApowBmodM(ll a, string &b, ll m) {
  ll remB = 0;
  for (int i = 0; i < (int)b.length(); ++i)
    remB = (remB * 10 + (b[i] - '0')) % (m - 1);
  return modpow(a, remB, m);
}
// both 'a' and 'b' is very large O(len(a) + len(b) + log(y))
ll ApowBmodM(string &a, string &b, ll m) {
  ll res = 1;
  ll x = aModM(a, m);
  ll y = aModM(b, m);
  res = modpow(x, y, m);
  return (res % m + m) % m;
}

// find two integers x and y such that ax + by = gcd(a, b)
void euclid(ll a, ll b, ll &x, ll &y, ll &d) {
  if (b) euclid(b, a % b, y, x, d), y -= x * (a / b);
  else x = 1, y = 0, d = a;
}
// find any solution for a * x + b * y = c
bool find_any_solution(ll a, ll b, int c, ll &x0, ll &y0, ll &g) {
  euclid(abs(a), abs(b), x0, y0, g);
  if (c % g) return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}

// All x' and y' is also a solution with any number k
// x' = x + k * b / gcd
// y' = y - k * a / gcd
void shift_solution(ll &x, ll &y, ll a, ll b, ll cnt) {
  x += cnt * b;
  y -= cnt * a;
}
// Find the number of solution in range [minx, maxx], [miny, maxy]
int find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
  int x, y, g;
  if (!find_any_solution(a, b, c, x, y, g))
    return 0;
  a /= g;
  b /= g;

  int sign_a = a > 0 ? +1 : -1;
  int sign_b = b > 0 ? +1 : -1;

  shift_solution(x, y, a, b, (minx - x) / b);
  if (x < minx)
    shift_solution(x, y, a, b, sign_b);
  if (x > maxx)
    return 0;
  int lx1 = x;

  shift_solution(x, y, a, b, (maxx - x) / b);
  if (x > maxx)
    shift_solution(x, y, a, b, -sign_b);
  int rx1 = x;

  shift_solution(x, y, a, b, -(miny - y) / a);
  if (y < miny)
    shift_solution(x, y, a, b, -sign_a);
  if (y > maxy)
    return 0;
  int lx2 = x;

  shift_solution(x, y, a, b, -(maxy - y) / a);
  if (y > maxy)
    shift_solution(x, y, a, b, sign_a);
  int rx2 = x;

  if (lx2 > rx2)
    swap(lx2, rx2);
  int lx = max(lx1, lx2);
  int rx = min(rx1, rx2);

  if (lx > rx)
    return 0;
  return (rx - lx) / abs(b) + 1;
}
// Solve: 
// t = a mod m1
// t = b mod m2
// ans = t mod lcm(m1, m2)
bool chinese_remainder(ll a, ll b, ll m1, ll m2, ll &ans, ll &lcm) {
  ll x, y, g, c = b - a;
  euclid(m1, m2, x, y, g);
  if (c % g) return false;
  lcm = m1 / g * m2;
  ans = ((a + c / g * x % (m2 / g) * m1) % lcm + lcm) % lcm;
  return true;
}

// Eratosthenes
// Prime sieve, isprime[i] is true if i is a prime
// O(n * loglogn)
const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vector<int> eratosthenesSieve(int lim) {
  isprime.set(); isprime[0] = isprime[1] = 0;
  for (int i = 4; i < lim; i += 2) isprime[i] = 0;
  for (int i = 3; i*i < lim; i += 2) if (isprime[i])
    for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
  vector<int> pr;
  for (int i = 2; i < lim; ++i) if (isprime[i]) pr.push_back(i);
  return pr;
}

// Fast Eratosthenes
const int LIM = 1e6;
bitset<LIM> isPrime;
vector<int> eratosthenes() {
  const int S = (int)round(sqrt(LIM)), R = LIM / 2;
  vector<int> pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
  vector<pair<int, int>> cp;
  for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
    cp.push_back({i, i * i / 2});
    for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
  }
  for (int L = 1; L <= R; L += S) {
    array<bool, S> block{};
    for (auto &[p, idx] : cp)
      for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
    for (int i = 0; i < min(S, R - L); ++i)
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  for (int i : pr) isPrime[i] = 1;
  return pr;
}

// Count the number of factor in range 1 ~ n
// If you want to calculate the sum of factor change ++ to += i
// O(n * logn)
void num_of_divisors(int n, ll ret[]) {
  for (ll i = 1; i <= n; ++i)
    for (ll j = i; j <= n; j += i)
      ret[j]++;
}

// euler phi of number in range 1 ~ n
// phi(n) = number of x such that 0 < x < n && gcd(n, x) = 1
// O(n * loglogn)
void euler_phi(int n, ll ret[]) {
  for (ll i = 0; i <= n; ++i) ret[i] = i & 1 ? i : i / 2;
  for (ll i = 3; i <= n; i += 2)
    if (ret[i] == i)
      for (ll j = i; j <= n; j += i)
        ret[j] -= ret[j] / i;
}

// Miller-Rabin for primality test. Guaranteed to work for numbers
// up to 7 * 10^18; for large numbers, use Python and extend A randomly.
// 7 times the complexity a^b  mod c
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
      s = __builtin_ctzll(n-1), d = n >> s;
  for (ull a : A) {   // ^ count trailing zeroes
    ull p = modpow(a%n, d, n), i = s; // modpow using ull
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n-1 && i != s) return 0;
  }
  return 1;
}
// n < 2,047 base = {2};
// n < 1,373,653 base = {2, 3};
// n < 9,080,191 base = {31, 73};
// n < 25,326,001 base = {2, 3, 5};
// n < 3,215,031,751 base = {2, 3, 5, 7};
// n < 4,759,123,141 base = {2, 3, 7, 61};
// n < 1,122,004,669,633 base = {2, 13, 23, 1662803};
// n < 2,152,302,898,747 base = {2, 3, 5, 7, 11};
// n < 3,474,749,660,383 base = {2, 3, 5, 7, 11, 13, 17}; 
// n < 3,825,123,056,413,051 base = {2, 3, 5, 7, 11, 13, 17, 19, 23};
// n < 318,665,857,834,031,151,167,461 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
// n < 3,317,044,064,679,887,385,961,981 base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

// factor of a number in O(logN)
const int MAXN = 1e6 + 1;
int spf[MAXN];
void sieve() {
  spf[1] = 1;
  for (ll i = 2; i < MAXN; ++i)
    spf[i] = i;
  for (ll i = 4; i < MAXN; i += 2)
    spf[i] = 2;
  for (ll i = 3; i * i < MAXN; ++i)
    if (spf[i] == i)
      for (ll j = i * i; j < MAXN; j += i)
        if (spf[j] == j)
          spf[j] = i;
} 
vector<ll> getFactorization(int x) {
  vector<ll>ret;
  while(x != 1) {
    ret.push_back(spf[x]);
    x = x / spf[x];
  }
  return ret;
}

// Find the prime factor in  O(sqrt(n), can factor up to 9 * 10^13
// With larger number, use Pollard Rho
vector<int> prime_factor(int n) {
  vector<int>factors;
  vector<ll>primes = sieve(n);
  int ind = 0, pf = primes[0];
  while(pf * pf <= n) {
    while(n % pf == 0) n /= pf, factors.push_back(pf);
    pf = primes[++ind];
  }
  if (n != 1) factors.push_back(n);
  return factors;
}

// Pollard-rho randomized factorization algorithm. Return prime
// factors of a number, in arbitrary order 
// time: O(n^(1/4)) use with modpow ull and miller
ull pollard(ull n) {
  auto f = [n](ull x) { return modmul(x, x, n) + 1; };
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
vector<ull> factor(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factor(x), r = factor(n / x);
  l.insert(l.end(), all(r));
  return l;
}
