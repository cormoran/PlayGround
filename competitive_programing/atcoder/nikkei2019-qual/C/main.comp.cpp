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


class Solver {
  public:
    bool solve() {
        int N; cin >> N;
        vector<ll> A(N), B(N);
        rep(i, N) cin >> A[i] >> B[i];
        vector<int> ia(N), ib(N);
        rep(i, N) {
            ia[i] = i;
            ib[i] = i;
        }

        sort(all(ia), [&] (int i, int j) {
                return A[i] + B[i] > A[j] + B[j];
                // return A[i] - B[i] > A[j] - B[j];
            });

        sort(all(ib), [&] (int i, int j) {
                return A[i] + B[i] > A[j] + B[j];
                //return B[i] - A[i] > B[j] - A[j];
            });
        // cerr << ia << endl;
        //cerr << ib << endl;

        vector<int> used(N, 0);
        ll suma = 0, sumb = 0;
        auto a = begin(ia), b = begin(ib);
        rep(i, N) {
            if(i % 2 == 0) {
                while(used[*a]) a++;
                suma += A[*a];
                used[*a] = true;
                a++;
            } else {
                while(used[*b]) b++;
                sumb += B[*b];
                used[*b] = true;
                b++;
            }
        }
        // cerr << suma << " " << sumb << endl;
        cout << suma - sumb << endl;
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
