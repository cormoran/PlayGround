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

vector<ll> sieve_of_eratosthenes(int upper) {
    vector<char> is_prime(upper, true);
    is_prime[0] = is_prime[1] = 0;
    vector<ll> res;
    for(int i = 2; i < upper; i++) {
        if(not is_prime[i]) continue;
        for(int j = i * 2; j < upper; j += i) is_prime[j] = false;
        res.push_back(i);
    }
    return res;
}

vector<ll> factors(ll x) {
    auto primes = sieve_of_eratosthenes(sqrt(x) + 1);
    vector<ll> res;
    for(ll p : primes) while(x % p == 0) {
            x /= p;
            res.push_back(p);
        }
    if(x > 1) res.push_back(x);
    return res;
}

double heron(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double c = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));
    double s = (a + b + c) / 2.0;
    //cerr << a << " " << b << " " << c << " " << s << endl;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    ll S; cin >> S;
    ll s;
    {
        ll l = 0, r = 1e9+1;
        while(l + 1 < r) {
            ll m = (l + r) / 2;
            (m * m < S ? l : r) = m;
        }
        s = r;
    }
    ll diff = s * s - S;
    ll a = 0, b = 0;
    if(diff > 0) {
        auto fac = factors(diff);
        if(diff == 1) {
            a = 1;
            b = 1;
        } else if(fac.size() > 1) {
            a = 1;
            b = 1;
            for(int i = 0; i < fac.size(); i += 2) {
                a *= fac[i];
                if(i + 1 < fac.size()) b *= fac[i + 1];
            }
        } else {
            assert(fac.size() == 1);
            a = 1;
            b = fac[0];
        }
    }

    cout << 0 << " " << 0 << " ";
    cout << s << " " << a << " ";
    cout << b << " " << s << endl;

    // debug(heron(0, 0, s, a, b, s)*2);

    return 0;
}
