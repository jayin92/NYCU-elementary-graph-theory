#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    vector<vector<ll>> d(n, vector<ll>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> d[i][j];
        }
    }

    vector<ll> ans(n, 0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i == j) continue;
            if(d[i][j] == 0){
                ans[i] += b;
            } else if(d[i][j] == 1){
                ans[i] += a;
            } else if(d[i][j] == 2) {
                ans[i] += c;
            }
        }
    }

    for(int i=0;i<n;i++){
        cout << ans[i] << (i != n-1 ? " " : "\n");
    }
}

