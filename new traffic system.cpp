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
#define piii            pair< int, pii >
#define MOD             1000000007
#define MAX             10007

using namespace std;
vector<pii> G[MAX], P[MAX];
int d[MAX][11];

void dijkstra(int src, int n, int dd){
    int u, v, w, sz, cnt;
    priority_queue< piii, vector<piii>, greater<piii> > Q;
    FORAB(i, 0, n + 1){
        FORAB(j, 0, dd + 1){
            d[i][j] = INF;
        }
    }
    d[src][0] = 0;
    Q.push(piii(0, pii(src, 0)));

    while(!Q.empty()){
        u = Q.top().ss.ff;
        cnt = Q.top().ss.ss;
        Q.pop();

        sz = G[u].size();
        FORAB(i, 0, sz){
            v = G[u][i].ff;
            w = G[u][i].ss;

            if(d[v][cnt] > d[u][cnt] + w){
                d[v][cnt] = d[u][cnt] + w;
                Q.push(piii(d[v][cnt], pii(v, cnt)));
            }
        }

        sz = P[u].size();
        FORAB(i, 0, sz){
            v = P[u][i].ff;
            w = P[u][i].ss;

            //dbg(d[u][cnt]);
            //dbg(u);
            //dbg(cnt);
            if(d[v][cnt+1] > d[u][cnt] + w && cnt + 1 <= dd){
                d[v][cnt+1] = d[u][cnt] + w;
                Q.push(piii(d[v][cnt+1], pii(v, cnt+1)));
            }
        }

    }
}

void clear(int n){
    FORAB(i, 0, n + 1){
        G[i].clear();
        P[i].clear();
    }
}

int main(){
    //read(in);
    //write(out);
	int tc, cs = 1, n, m, a, b, c, k, dd;
	scan(tc);
	while(tc--){
        scanf("%d%d%d%d", &n, &m, &k, &dd);
        FORAB(i, 0, m){
            scanf("%d%d%d", &a, &b, &c);
            G[a].pb(pii(b, c));
        }
        FORAB(i, 0, k){
            scanf("%d%d%d", &a, &b, &c);
            P[a].pb(pii(b, c));
        }
        dijkstra(0, n, dd);
		printf("Case %d: ", cs++);

        int ans = INF;
        FORAB(i, 0, dd + 1){
            ans = min(ans, d[n-1][i]);
        }
        if(ans != INF) print(ans);
        else puts("Impossible");
        clear(n);
	}
    return 0;
}
