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

string print_bin(ll x, int n) {
    string s;
    while(x) {
        s += (x % 2 ? "1" : "0");
        x /= 2;
    }
    while(s.size() < n) s += "0";
    reverse(all(s));
    return s;
}

class Solver {
  public:
    int solve2(ll x, ll n) {
        ll X = x;
        rep(i, 1000) {
            if(x % 2) x = x / 2;
            else x = x / 2 + (1 << (n - 1));
            if(x == X) {
                return i + 1;
            }
        }
        debug("no");
        return -1;
    }
    bool solve() {
        repeat(i, 1, 30) {
            int prev = -1;
            int prev_j = -1;
            rep(j, (1 << i)) {
                int tmp = solve2(j, i);
                if(prev != tmp and prev >= 0) {
                    // cerr << i << " " << j << " " << solve2(j, i) << " diff " << j - prev_j << " " << print_bin(j - prev_j, i) << endl;
                    // cerr << print_bin(j, i) << " " << print_bin(j - prev_j, i) << endl;
                    cerr << print_bin(j - prev_j, i) << " " << i << " " << print_bin(j, i) <<  endl;
                    prev_j = j;
                }
                prev = tmp;
            }
        }
        return 0;
        ll X, n; cin >> X >> n;
        ll x = X;
        print_bin(x, n);
        rep(i, 100) {
            if(x % 2) x = x / 2;
            else x = x / 2 + (1 << (n - 1));
            print_bin(x, n);
            if(x == X) {
                cerr << "OK " << i + 1 << endl;
                break;
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
