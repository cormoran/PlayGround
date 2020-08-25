#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
#define debug(x) cerr << #x << " : " << x << endl

template<class T> bool set_min(T &a, const T &b) { return a > b  ? a = b, true : false; }
template<class T> bool set_max(T &a, const T &b) { return a < b  ? a = b, true : false; }
// vector
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }
template<class T> ostream& operator << (ostream &os , const vector<T> &v) { for(const T &t : v) os << "\t" << t; return os << endl; }
// pair
template<class T, class U> ostream& operator << (ostream &os , const pair<T, U> &v) { return os << "<" << v.first << ", " << v.second << ">"; }

const int INF = 1 << 30;
const ll INFL = 1LL << 60;

class ModInt{
  public:
    static const ll MOD = 1000000007LL;
    ll x;
    ModInt():x(0){};
    ModInt(ll x){
        while(x < 0) x += MOD;
        x %= MOD;
        this->x = x;
    }
    ModInt& operator += (const ModInt &l){ x += l.x; if( x >= MOD) x -= MOD; return *this; }
    ModInt& operator -= (const ModInt &l){ x -= l.x; if( x < 0 ) x += MOD; return *this; }
    ModInt& operator *= (const ModInt &l){ x = (x * l.x) % MOD; return *this; }
    ModInt operator +(const ModInt &l) const { return ModInt( x + l.x); }
    ModInt operator -(const ModInt &l) const { return ModInt( x - l.x); }
    ModInt operator *(const ModInt &l) const { return ModInt( x * l.x); }
};

// @warning rの部分はmodとってはいけない
ModInt pow(const ModInt &n, ll r){
    if(r == 0) return ModInt(1);
    ModInt ret = pow(n, r / 2);
    ret *= ret;
    if(r % 2 != 0) ret = ret * n;
    return ret;
}

// @waring nはMODと互いに素
ModInt inverse(const ModInt &n){
    return pow(n, ModInt::MOD - 2);
}


ModInt factorial(const ModInt &n){
    ModInt ret =1;
    for(ll i=n.x; i>1; i--){
        ret*=i;
    }
    return ModInt(ret);
}

ostream& operator << (std::ostream& os,const ModInt& a){ os << a.x; return os;}
istream& operator >> (std::istream& is,ModInt& a){ is >> a.x; return is;}


class Solver {
  public:
    bool solve() {
        int N, K; cin >> N >> K;
        vector<ModInt> factorials(N * 2);
        factorials[0] = 1;
        rep(i, N * 2 - 1) factorials[i + 1] = factorials[i] * (i + 1);

        repeat(i, 1, K + 1) {
            int B = K - i, R = N - K - (i - 1);
            if(B < 0 or R < 0) cout << 0 << endl;
            else {
                ModInt r = factorials[R + i] * inverse(factorials[R] * factorials[i]);
                ModInt b = factorials[B + i - 1] * inverse(factorials[B] * factorials[i - 1]);
                cout << r * b << endl;
            }
        }
        return 0;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    Solver s;
    s.solve();
    return 0;
}
