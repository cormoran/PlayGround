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

    vector<Deck> decks(N);
    int max_num = N / 2 + (N % 2);
    int now = 0;

    auto calc_props = [&]() {
        vector<double> probs(N);
        int ap = decks[now].top;
        rep(i, N) {
            if (decks[i].removed.count(ap)) {
                probs[i] = 0;
            } else if(decks[i].top != -1) {
                probs[i] = decks[i].top == ap;
            } else {
                probs[i] = (double)(max_num - decks[i].removed.size()) / max_num;
            }
        }
        return probs;
    };
    auto isort_probs = [&] (vector<double> probs) {
        vector<int> indices(N);
        rep(i, N) indices[i] = i;
        sort(all(indices), [&](int i, int j) {
                if(probs[i] == probs[j])
                    return abs(i - now) < abs(j - now);
                return probs[i] > probs[j];
            });
        return indices;
    };
    cout << 0 << endl; cout.flush();
    int x;
    cin >> x;
    decks[0].top = x;
    now = 0;

    int point = 0;
    while(T > 0) {
        auto probs = calc_props();
        auto indices = isort_probs(probs);
        int prev = now;
        now = -1;
        for(int nxt: indices) {
            if(prev != nxt and abs(prev - nxt) <= T) {
                now = nxt;
                T -= abs(prev -nxt);
                break;
            }
        }
        if(now == -1) break;

        cout << now << endl; cout.flush();
        int x;
        cin >> x;
        decks[now].top = x;
        if(decks[prev].top == decks[now].top) {
            decks[prev].remove();
            decks[now].remove();
            point++;
            if(T > 0) {
                cout << now << endl; cout.flush();
                int x; cin >> x;
                decks[now].top = x;
            }
        }
    }
    cout << -1 << endl;
    cout.flush();
    cerr << "point : " << point << endl;

    return 0;
}

