#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> cnt(1e5+10, 0);
    int tmp;
    for(int i=0;i<n;i++){
        cin >> tmp;
        cnt[tmp]++;
    }
    int m = 0;
    int ans = -1;
    for(int i=0;i<n;i++){
        if(cnt[i] >= m){
            m = cnt[i];
            ans = i;
        }
    }
    cout << ans << " " << m << endl;
}
