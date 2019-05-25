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
    ll ret =1;
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
        ll N, M;
        ll K; cin >> N >> M >> K;


        ModInt sum = 0;
        {
            ll s = N * (N - 1) / 2; // 1 + ... + (N - 1)
            rep(i, N) {
                sum += ModInt(s) * ModInt(M) * ModInt(M);
                s -= N - 1 - i;
                s += i + 1;
            }
        }
        {
            ll s = M * (M - 1) / 2; // 1 + ... + (N - 1)
            rep(i, M) {
                sum += ModInt(s) * ModInt(N) * N;
                s -= M - 1 - i;
                s += i + 1;
            }
        }
        // ModInt sum2 = 0;
        // rep(i, N) {
        //     rep(k, N) {
        //         sum2 += ModInt(abs(i - k) * M) * M;
        //     }
        // }
        // rep(j, M) {
        //     rep(l, M) {
        //         sum2 += ModInt(abs(j - l) * N) * N;
        //     }
        // }
        // ModInt sum3 = 0;
        // rep(i, N) rep(j, M) rep(k, N) rep(l, M) sum3 += abs(i - k) + abs(j - l);
        // cerr << sum << " " << sum2 << " " << sum3 << endl;;
        // assert(sum.x == sum2.x);
        debug(sum);
        ModInt ans = sum * (ModInt(N) * ModInt(M) - (K - 1)) * ModInt(K);
        ans *= inverse(K - 2);
        // auto len = ModInt(M * N) * ModInt(M * N - 1) * inverse(2);
        // ModInt nmCk =
        //         ll ans = 0;
        cout << ans << endl;
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
