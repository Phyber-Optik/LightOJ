/*  Towhidul Islam
    University Of Dhaka
    Problem Name :
    Algorithm Used :
*/

#include<bits/stdc++.h>

typedef long long ll;

#define SSTR(x)         dynamic_cast< ostringstream & >( \
                        (ostringstream() << dec << x )).str()
#define pb              push_back
#define mem(a, x)       memset(a, x, sizeof a)
#define PI              acos(-1)
#define all(a)          a.begin(), a.end()
#define ff              first
#define ss              second
#define read(in)        freopen("in.txt", "r", stdin)
#define write(out)      freopen("out.txt", "w", stdout)
#define INF             1<<30
#define eps             1e-9
#define FORN(i, n)      for(int i = 0; i < n; i++)
#define FORAB(i, x, n)  for(int i = x; i < n; i++)
#define FORD(i, x, n)   for(int i= n - 1; i >= x; i--)
#define scan(n)         scanf("%d", &n)
#define print(n)        printf("%d\n", n)
#define tor             vector
#define dbg(x)          cout<<#x<<" : "<<x<<endl
#define chkwhere        cout<<"LOL\n"
#define pii             pair<int, int>
#define edge            pair<pii, int>
#define MOD             1000000007
#define MAX             101

using namespace std;

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};

vector < int > G[MAX];
vector < edge > E;
bool visited[MAX];
int Left[MAX], Right[MAX];
int high, low;

bool dfs(int u) {
    if(visited[u]) return false;
    visited[u] = true;
    int len = G[u].size(), i, v;
    for(i = 0; i < len; i++) {
        v = G[u][i];
        if(Right[v] == -1) {
            Right[v] = u, Left[u] = v;
            return true;
        }
    }
    for(i = 0; i < len; i++) {
        v = G[u][i];
        if(dfs(Right[v])) {
            Right[v] = u, Left[u] = v;
            return true;
        }
    }
    return false;
}

int match(int n) {
    mem(Left, -1);
    mem(Right, -1);
    int i, ret = 0;
    bool done;
    
    do {
        done = true;
        mem(visited, false);
        for(i = 0; i < n; i++) {
            if(Left[i] == -1 && dfs(i)) {
                done = false;
            }
        }
    } while(!done);
    for(i = 0; i < n; i++) ret += (Left[i] != -1);
    return ret;
}

int bin_search(int l, int r, int gh, int hu){
    int mid;
    while(l < r){
        mid = (l + r) >> 1;
        FORAB(i, 0, gh) G[i].clear();
        FORAB(i, 0, E.size()){
            if(E[i].ss <= mid){
                G[E[i].ff.ff].pb(E[i].ff.ss);
            }
        }
        if(match(gh) == hu){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    return r;
}


int cost[26][26];
int grid[26][26], ghosts[51], humans[51];
char str[26][26];
map<int, int>tmp;

void bfs(int x, int y, int n){
    int g = grid[x][y];
    mem(cost, -1);
    cost[x][y] = 0;
    queue<pii>Q;
    Q.push(pii(x, y));
    

    pii u;
    while(!Q.empty()){
        u = Q.front();
        Q.pop();
        int v;
        
        FORAB(k, 0, 4){
            int tx = u.ff + dx[k];
            int ty = u.ss + dy[k];
            if(tx >= 0  && tx < n && ty >= 0 && ty < n && str[tx][ty] != '#' && cost[tx][ty] == -1){
                v = grid[tx][ty];
                cost[tx][ty] = cost[u.ff][u.ss] + 1;
                if(str[tx][ty] == 'H'){
                    E.push_back(edge(pii(g, v), cost[tx][ty]));
                    high = max(high, cost[tx][ty]);
                    low = min(low, cost[tx][ty]);
                }
                Q.push(pii(tx, ty));
            }
        }
    }
}

int main(){
    //read(in);
    //write(out);
    int tc, cs = 1, n, m, a, b;
    scan(tc);
    while(tc--){
        scanf("%d", &n);

        int cnt = 0, hu = 0, gh = 0;
        FORAB(i, 0, n){
            scanf("%s", str[i]);
            FORAB(j, 0, n){
                if(str[i][j] != '#'){
                    if(str[i][j] == 'H'){
                        grid[i][j] = hu++;
                    }
                    else if(str[i][j] == 'G'){
                        grid[i][j] = gh++;
                    }
                }
            }
        }

        low = INF;
        high = -1;
        FORAB(i, 0, n){
            FORAB(j, 0, n){
                if(str[i][j] == 'G'){
                    bfs(i, j, n);
                }
            }
        }
        printf("Case %d: ", cs++);

        FORAB(i, 0, gh) G[i].clear();
        FORAB(i, 0, E.size()){
            if(E[i].ss <= high){
                G[E[i].ff.ff].pb(E[i].ff.ss);
            }
        }
        if(match(gh) < hu){
            puts("Vuter Dol Kupokat");
        }
        else printf("%d\n", bin_search(low, high, gh, hu) * 2 + 2);
        
        E.clear();
    }

    return 0;
}
