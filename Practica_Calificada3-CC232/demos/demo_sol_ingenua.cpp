#include <bits/stdc++.h>
using namespace std;

void solu(vector<int>& S, int T, int X) {
    if (T == 1) {
        S.push_back(X);
    } else {
        sort(S.begin(), S.end());
        cout << S[X - 1] << "\n";
        S.erase(S.begin() + X - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> S;
    int Q;
    cin >> Q;

    while (Q--) {
        int T, X;
        cin >> T >> X;
        solu(S, T, X);
    }

    return 0;
}