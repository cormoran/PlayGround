#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll  = long long;
#define rep(i, j) for (int i = 0; i < (int)(j); i++)
#define repeat(i, j, k) for (int i = (j); i < (int)(k); i++)
#define all(v) v.begin(), v.end()
#define debug(x) cerr << #x << " : " << x << endl

template <class T>
bool set_min(T &a, const T &b) {
    return a > b ? a = b, true : false;
}
template <class T>
bool set_max(T &a, const T &b) {
    return a < b ? a = b, true : false;
}
// vector
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &a : v) is >> a;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &t : v) os << "\t" << t;
    return os << endl;
}
// pair
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &v) {
    return os << "<" << v.first << ", " << v.second << ">";
}

const int INF = 1 << 30;
const ll INFL = 1LL << 60;

struct Deck {
    int top;
    set<int> removed;
    Deck() : top(-1) {}
    void remove() {
        removed.insert(top);
        top = -1;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, T;
    cin >> N >> T;

    vector<int> top(N, -1);
    map<int, int> mp;
    int prev = -1;
    int now = 0;
    int point = 0;


    while(T > 0) {
        rep(i, N) {
            cout << i << endl; cout.flush();
            int x; cin >> x;
            top[i] = x;
            if(i > 0 and top[i - 1] == top[i]) {
                point += top[i];
                i -=2;
                mp[top[i]] -= 2;
            } else {
                mp[top[i]]++;
            }
            T--;
        }
        vector<int> cond;
        for(auto p : mp) if(p.second > 2) cond.push_back(p.first);
        sort(all(cond));
        if(cond.size() == 0) break;
        vector<int> indices;
        rep(i, N) if(top[i] == cond.back()) indices.push_back(i);

        int a = indices[indices.size() - 1];
        int b = indices[indices.size() - 2];
        T -= abs(N - 1 - b);
        if(T < 0) break;
        cout << b << endl; cout.flush();
        int x; cin >> x;
        T -= abs(b - a);
        if(T < 0) break;
        cout << a << endl; cout.flush();
        cin >> x;
        point += top[a];
        T -= abs(a - 0);
        if(T < 0) break;
        cout << 0 << endl; cout.flush();
        cin >> x;
        rep(i, N) top[i] = -1;
        top[0] = x;
    }
    cout << -1 << endl;
    cerr << "point : " << point << endl;

    return 0;
}
