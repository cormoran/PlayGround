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
        int N, A, B, C; cin >> N >> A >> B >> C;
        vector<int> L(N); cin >> L;
        vector<int> ABC = {A, B, C};
        function<int(int, vector<int>&)> dfs = [&] (int now, vector<int> &choice) {
            int res = INF;
            if(now == N) {
                res = 0;
                vector<int> abc(3);
                rep(i, choice.size()) {
                    if(choice[i] < 3) {
                        res += abc[choice[i]] > 0 ? 10 : 0;
                        abc[choice[i]] += L[i];
                    }
                }
                rep(i, 3) if(abc[i] == 0 and ABC[i] > 0) return INF;
                rep(i, 3) res += abs(abc[i] - ABC[i]);
                return res;
            }
            rep(i, 4) {
                choice.push_back(i);
                set_min(res, dfs(now + 1, choice));
                choice.pop_back();
            }
            return res;
        };
        vector<int> tmp;
        cout << dfs(0, tmp) << endl;
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
