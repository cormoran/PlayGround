#include <bits/stdc++.h>
using namespace std;

#define rep(i, j) for(int i=0; i < (int)(j); i++)
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }

int main() {
    int N; cin >> N;
    vector<string> S(N); cin >> S;
    int ans = 0;
    int a = 0, b = 0, ab = 0;
    rep(i, N) {
        assert(S[i].size() >= 2);
        a += S[i].back() == 'A';
        b += S[i].front() == 'B';
        ab += S[i].back() == 'A' and S[i].front() == 'B';
        rep(j, S[i].size() - 1) if(S[i][j] == 'A' and S[i][j + 1] == 'B') ans++;
    }
    a -= ab;
    b -= ab;
    ans += max(0, ab - 1);
    if(ab > 0 and a > 0 and b > 0) {
        ans += 2;
        a--; b--;
        ans += min(a, b);
    } else if (ab > 0 and (a > 0 or b > 0)) {
        ans += 1;
    } else {
        ans += min(a, b);
    }
    cout << ans << endl;
    return 0;
}
