// Q given graph and values assigned to each node 
// find score for the each node 
// score is defined as (no of nodes in ancestors which have val greater than curr node )*value of curr node +
// sum of values of nodes in ancestor nodes which have vaue less than val of curr node 


#include <bits/stdc++.h>
using namespace std;
#define fo(i, s, e) for (int i = s; i < e; i++)
typedef long long ll;
#define ff first
#define ss second
#define in insert
#define all(x) x.begin(), x.end()
#define pb push_back
using vi = vector<int>;
using vvi = vector<vector<int>>;

int mod = 998244353;
int mxn = 10001;
int value[100001],in[100001] , out[100001] , dfsvis[200002] , nodeF[100001];

int timer = 1;

void dfs(int node, int par, vvi &adj)
{   
    dfsvis[timer] = node ;
    in[node] = timer++;
    for (auto child : adj[node])
    {
        if (child != par)
        {
            dfs(child, node, adj);
        }
    }
    dfsvis[timer] = node ;
    out[node] = timer++;
}

struct Query{
    int s , e , idx , node ;
};

bool comp(Query a, Query b){
    int  x = a.s/555 ;
    int  y = b.s/555 ;

    if(x!=y){
        return x<y ;
    }

    return a.e<b.e ;
}

Query q[100001] ;

ll sum[100001] , cnt[100001] , ans[100001]  ;
ll bucket1[10001] ;
ll bucket2[10001] ;

int getblock(int n ){
    return n/555 ;
}

void add(int n){
    int node  = dfsvis[n] ;
    nodeF[node]++ ;
                   
    if(nodeF[node]==1){
        int val = value[node] ;
        sum[val]+=val ;
        bucket1[getblock(val)]+=val ;
        cnt[val]+=1 ;
        bucket2[getblock(val)]+=1 ;
    }

    if(nodeF[node]==2){
        int val = value[node] ;
        sum[val]-=val ;
        bucket1[getblock(val)]-=val ;
        cnt[val]-=1 ;
        bucket2[getblock(val)]-=1 ;
    }
}

void remove(int n){
    int node  = dfsvis[n] ;
    nodeF[node]-- ;

    if(nodeF[node]==0){
        int val = value[node] ;
        sum[val]-=val ;
        bucket1[getblock(val)]+=val ;
        cnt[val]-=1 ;
        bucket2[getblock(val)]-=1 ;
    }
 
}
ll getans(int node , int maxN){
    int lim = value[node] ;
    ll x = 0 ;
    // for(int i=0;i<lim;i++){
    //     x+=sum[i] ;
    // }
    for(int i=0;i<getblock(lim);i++){
        x+=bucket1[i] ;
    }
    for(int i= getblock(lim)*555;i<lim;i++){
        x+=sum[i] ;
    }
    ll c = 0 ;
    // for(int i=lim+1;i<=maxN;i++){
    //     c+=cnt[i];
    // }
    for(int i=lim+1;i<(getblock(lim)+1)*555; i++){
        c+=cnt[i] ;                                          
    }
    for(int i= (getblock(lim)+1)*555 ; i<getblock(maxN);i++){
        c+=bucket2[i] ;
    }

    x+=(c*value[node]) ;

    return x ;
}

int solve()
{
    int n ;
    cin>>n ;
    vvi adj(n+1) ;
    fo(i,1,n+1){
        cin>>value[i] ;
    }

    fo(i,0,n-1){
        int a , b ;
        cin>>a>>b ;
        adj[a].pb(b) ;
        adj[b].pb(a) ;
    }
    dfs(1,-1,adj) ;

    fo(i,1,timer){
        cout<<dfsvis[i]<<" ";
    }
    cout<<"\n" ;

    for(int i=0;i<n;i++){
        q[i].s = in[1] ;
        q[i].e = in[i+1] ;
        q[i].idx = i ;
        q[i].node = i+1 ;
    }

    sort(q,q+n,comp) ;
    int ML = 0 , MR =-1 ;

    fo(i,0,n){
        int L = q[i].s ;
        int R = q[i].e ;
        int node = q[i].node ;
        int idx = q[i].idx ;

        cout<<"node "<<node<<" val "<<value[node]<<"\n" ;
        cout<<"l "<<L<<" r "<<R<<"\n" ;
        while(MR<R){
            MR++ , add(MR); 
        }
        while(ML>L){
            ML-- , add(ML) ;
        }
        while(MR>R){
            remove(MR) , MR-- ;
        }
        while(ML<L){
            remove(ML) , ML++ ;
        }

        cout<<"sum ->\n";
        for(int i=1;i<=5;i++){
            cout<<sum[i]<<" ";
        }
        cout<<"\n" ;

        cout<<"cnt ->\n";
        for(int i=1;i<=5;i++){
            cout<<cnt[i]<<" ";
        }
        cout<<"\n\n" ;

        ll dm = getans(node , n) ;
        ans[idx] = dm ;
    }

    fo(i,0,n){
        cout<<ans[i]<<" " ;
    }
    cout<<"\n" ;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 1;
    // cin >> tt;
    while (tt--)
    {
        solve();
    }
    return 0;
}
