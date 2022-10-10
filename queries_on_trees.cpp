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

#define maxN 100010 
#define blk 555

int col[maxN] , in[maxN] , out[maxN] , vis[2*maxN+10] , nodeF[maxN] , colF[maxN] , FF[maxN];

int timer = 1 ;
void dfs(int node , int par , vvi&adj){
    in[node] = timer ;
    vis[timer++] = node ;

    for(auto child : adj[node]){
        if(child!=par){
            dfs(child , node,adj) ;
        }
    } 
    out[node] = timer ;
    vis[timer++] = node ;
}

struct Query{
    int l, r , idx ,k ;
} ;

bool comp(Query a ,Query b){
    int x = a.l/blk  ;
    int y = b.l/blk  ;

    if(x!=y){
        return a.l<b.l ;
    }

    return a.r<b.r ;
}

Query Q[maxN] ;
int ans[maxN] ;
int bucket[555] ;

int getblock(int idx){
    return (idx/blk) ;
}
void add(int idx){
    int node = vis[idx] ;
    nodeF[node]++ ;
    int bkt = idx/blk ;
    
    if(nodeF[node]==2){
        colF[col[node]]++ ;
        FF[colF[col[node]]]++ ;
        bucket[ getblock(colF[col[node]]) ]++ ;
        FF[colF[col[node]] -1 ]-- ;
        bucket[ getblock(colF[col[node]] -1 ) ]-- ;
    }
}

void remove(int idx){
    int node = vis[idx] ;
    nodeF[node]-- ;

    if(nodeF[node]==1){
        colF[col[node]]-- ;
        FF[colF[col[node]] +1 ]-- ;
        bucket[ getblock(colF[col[node]] +1) ]-- ;
        FF[colF[col[node]]]++ ;
        bucket[ getblock(colF[col[node]]) ]++ ;
    }
}

int getans(int k , int n){
    int b1 = k/blk ;
    int b2 = n/blk ;

    int cnt = 0 ;

    if(b1==b2){
        for(int i =k;i<=n;i++){
            cnt+=FF[i] ;
        }
    }
    else{

        for(int i=k;i<(b1+1)*blk;i++){
            cnt+=FF[i] ;
        }
        for(int b=b1+1;b<b2;b++){
            cnt+=bucket[b];
        }

        for(int i=b2*blk;i<=n;i++){
            cnt+=FF[i] ;
        }
    }

    return cnt ;
}


int main()
{   
    int n  , q;
    cin>>n>>q ;
    fo(i,1,n+1){
        cin>>col[i];
    }

    vector<vector<int>>adj(n+1) ;
    fo(i,0,n-1){
        int a,b ;
        cin>>a>>b ;
        adj[a].pb(b) ;
        adj[b].pb(a) ;
    }

    dfs(1,-1,adj) ;

    fo(i,0,q){
        int node , k ;
        cin>>node>>k ;
        Q[i].l = in[node] ;
        Q[i].r = out[node] ;
        Q[i].idx = i ;
        Q[i].k = k ;
    }

    sort(Q,Q+q,comp) ;

    int MR = -1  , ML = 0 ;
    fo(i,0,q){
        int L = Q[i].l ;
        int R = Q[i].r ;
        int idx = Q[i].idx ;
        int k = Q[i].k ;

        // cout<<"L "<<L<<" R "<<R<<" idx "<<idx<<" k "<<k<<"\n";

        while(MR<R){
           MR++ , add(MR) ;
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

        // cout<<"\ncolF array after query "<<"\n";
        // fo(i,1,4){
        //     cout<<"i "<<i <<" fr "<<colF[i]<<"\n";
        // }
        // cout<<"\nFF array after query "<<"\n";
        // fo(i,1,5){
        //     cout<<"i "<<i <<" fr "<<FF[i]<<"\n";
        // }

        ans[idx] = getans(k,n) ;

        // cout<<"\nans to the query is  "<<ans[idx]<<"\n\n";
    }

    fo(i,0,q){
        cout<<ans[i]<<'\n';
    }
}
