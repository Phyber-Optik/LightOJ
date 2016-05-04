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
#define MOD             1000000007
#define MAX             201

using namespace std;

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};
vector < int > G[MAX];
bool visited[MAX];
int Left[MAX], Right[MAX];

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

int main(){
    //read(in);
    //write(out);
	int tc, cs = 1, n, m, a, b, grid[21][21];
	char str[21][21];
    scan(tc);
	while(tc--){
        scanf("%d%d", &m, &n);

        int odd = 0, even = 0;
        FORAB(i, 0, m){
            scanf("%s", str[i]);
            FORAB(j, 0, n){
                if(str[i][j] == '*'){
                    if((i + j) & 1){
                        grid[i][j] = odd++;
                    }
                    else{
                        grid[i][j] = even++;
                    }
                }
            }
        }

        FORAB(i, 0, m){
            FORAB(j, 0, n){
                if(!((i + j) & 1) && str[i][j] == '*'){
                    FORAB(k, 0, 4){
                        int tx = i + dx[k];
                        int ty = j + dy[k];

                        if(tx >= 0 && tx < m && ty >= 0 && ty < n && str[tx][ty] == '*'){
                            G[grid[i][j]].pb(grid[tx][ty]);
                        }
                    }
                }
            }
        }

		printf("Case %d: %d\n", cs++, odd + even - match(even));
	    
        FORAB(i, 0, even){
            G[i].clear();
        }
    }
    return 0;
}
