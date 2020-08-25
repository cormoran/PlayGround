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


string to_bin(ll x) {
    string res;
    while(x) {
        res.push_back((x & 1) ? '1' : '0');
        x >>= 1;
    }
    reverse(all(res));
    return res;
}


class Solver {
  public:
    bool solve() {
        int N; cin >> N;
        vector<ll> A(N); cin>> A;

        {
            double mx=0;
            for(ll a : A) {
                set_max(mx, log2(a));
            }
            debug(mx);
        }

        ll all_xor = 0;
        for(auto a : A) all_xor ^= a;
        rep(i, N) {
            A[i] &= ~all_xor;
        }
        sort(all(A), greater<ll>());
        debug(A);
        int idx = 0;
        set<int> red_set, blue_set;
        ll red = 0, blue = 0;
        for(int i = 61; i >=0; i--) {
            if(all_xor & (1ll << i)) continue;
            int idx2 = 0;
            int idx3 = 0;
            while(idx + idx3 < N and A[idx + idx3] & (1ll << i)) idx3++;


            while(idx < N and A[idx] & (1ll << i)) {
                cerr << "use " << A[idx] << " " << to_bin(A[idx]) << endl;
                (idx2 % 2 == 0 ? red : blue) ^= A[idx];
                (idx2 % 2 == 0 ? red_set : blue_set).insert(idx);
                idx++;
                idx2++;
            }


            if(((red & blue) & (1ll << i)) == 0) {
                cerr << "need swap at " << i << endl;
                map<ll, int> a, b;
                for(auto j : red_set) {
                    ((A[j] & (1ll << i)) ? a : b)[A[j] >> (i + 1)] = j;
                }
                for(auto j : blue_set) {
                    if(A[j] & (1ll << i)) {
                        if(b.count(A[j] >> (i + 1))) {
                            int swap_a = b[A[j] >> (i + 1)];
                            int swap_b = j;
                            red_set.erase(swap_a);
                            blue_set.erase(swap_b);
                            red_set.insert(swap_b);
                            blue_set.insert(swap_a);
                            red = red ^ A[swap_a] ^ A[swap_b];
                            blue = blue ^ A[swap_a] ^ A[swap_b];
                            break;
                        }
                    } else {
                        if(a.count(A[j] >> (i + 1))) {
                            int swap_a = a[A[j] >> (i + 1)];
                            int swap_b = j;
                            red_set.erase(swap_a);
                            blue_set.erase(swap_b);
                            red_set.insert(swap_b);
                            blue_set.insert(swap_a);
                            red = red ^ A[swap_a] ^ A[swap_b];
                            blue = blue ^ A[swap_a] ^ A[swap_b];
                            break;
                        }
                    }
                }
            }
            cerr << "fail " << i << endl;
      OK:;
        }
        debug(red);
        debug(blue);
        cerr << "red ";
        for(auto i : red_set) cerr << A[i] << " ";
        cerr << endl;

        cerr << "blue ";
        for(auto i : blue_set) cerr << A[i] << " ";
        cerr << endl;

        for(int i = 61; i >=0; i--) cerr << ((all_xor & (1ll << i)) != 0) << " "; cerr << endl;
        for(int i = 61; i >=0; i--) cerr << ((red & (1ll << i)) != 0) << " "; cerr << endl;
        for(int i = 61; i >=0; i--) cerr << ((blue & (1ll << i)) != 0) << " "; cerr << endl;

        cout << red + blue + all_xor << endl;
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
