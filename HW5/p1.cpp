// :80 <enter>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef jayinnn
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<", ";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool check_k5(vector<vector<int>>& adj, vector<int>& idx){
    if(idx.size() != 5) return false;
    sort(ALL(idx));
    do{
        bool flag = true;
        for(int i=0;i<5;i++){
            for(int j=i+1;j<5;j++){
                if(adj[idx[i]][idx[j]] == 0){
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }
        if(flag) return true;
    }while(next_permutation(ALL(idx)));

    return false;
}


bool check_k33(vector<vector<int>>& adj, vector<int>& idx){
    // check bipartite
    if(idx.size() != 6) return false;
    debug("k33");
    sort(ALL(idx));
    do{
        bool flag = true;
        for(int i=0;i<3;i++){
            for(int j=i+1;j<3;j++){
                if(adj[idx[i]][idx[j]] == 1){
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }
        if(!flag) continue;
        for(int i=3;i<6;i++){
            for(int j=i+1;j<6;j++){
                if(adj[idx[i]][idx[j]] == 1){
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }
        if(!flag) continue;
        for(int i=0;i<3;i++){
            for(int j=3;j<6;j++){
                if(adj[idx[i]][idx[j]] == 0){
                    flag = false;
                    break;
                }
            }
            if(!flag) break;
        }
        if(flag) return true;
    }while(next_permutation(ALL(idx)));

    return false;
}

void solve(){
    int n, m;
    cin >> n >> m;

    int u, v;
    vector<pii> edges(m);
    for(int i=0;i<m;i++){
        cin >> u >> v;
        edges[i].X = u;
        edges[i].Y = v;
    }
    int sum = (1 << m);
    vector<int> idx;
    for(int ii=0;ii<sum;ii++){
        bool flag;
        vector<vector<int>> adj(n+1, vector<int>(n+1, 0));
        vector<int> deg(n+1, 0);
        int tmp = ii;
        for(int j=0;j<m;j++){
            if(tmp & 1){
                adj[edges[j].X][edges[j].Y] = adj[edges[j].Y][edges[j].X] = 1;
            } else {
                adj[edges[j].X][edges[j].Y] = adj[edges[j].Y][edges[j].X] = 0;
            }
            tmp >>= 1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(adj[i][j] == 1){
                    deg[i]++;
                }
            }
        }
        while(true){
            flag = true;
            for(int i=1;i<=n;i++){
                if(deg[i] == 2){
                    u = v = -1;
                    for(int j=1;j<=n;j++){
                        if(adj[i][j] == 1){
                            if(u == -1) u = j;
                            else v = j;
                        }
                    }
                    if(adj[u][v] == 1){
                        deg[u] --;
                        deg[v] --;
                    }
                    adj[u][v] = 1;
                    adj[v][u] = 1;
                    adj[i][v] = adj[v][i] = 0;
                    adj[i][u] = adj[u][i] = 0;
                    deg[i] = 0;
                    flag = false;
                    break;
                }
            }
            if(flag) break;
        }
    
        // check K5
        idx.clear();
        for(int i=1;i<=n;i++){
            if(deg[i] == 4){
                idx.push_back(i);
            }
        }
        if(check_k5(adj, idx)){
            debug("has k5");
            cout << "No" << endl;
            return;
        }
        idx.clear();
        for(int i=1;i<=n;i++){
            if(deg[i] == 3){
                idx.push_back(i);
            }
        }
        if(check_k33(adj, idx)){
            debug("has k33");
            cout << "No" << endl;
            return;
        }
    }
    
    cout << "Yes" << endl;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}

