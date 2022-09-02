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

struct query{
    int l , r ,i;
} ;

int blk = 555  ;
ll power = 0 ;

bool comp(query a, query b){
    // cout<<"l1 = "<<a.l<<" , r1 = "<<a.r<<" and "<<" l2 = "<<b.l<<" , r2 = "<<b.r<<"\n";
    if(a.l/blk!=b.l/blk){
        return a.l < b.l ;
    }
    return a.r<b.r ;
}

int arr[200000+10];
int F[1000000+10] ;

void add(int i ){
    int preF = F[arr[i]] ;
    int newF = ++F[arr[i]] ;

    power-=1ll*preF*preF*arr[i] ;
    power+=1ll*newF*newF*arr[i] ;
}

void remove(int i){
    int preF = F[arr[i]] ;
    int newF = --F[arr[i]] ;

    power-=1ll*preF*preF*arr[i] ;
    power+=1ll*newF*newF*arr[i] ;
}

void solve(){
    int n ;
    cin>> n ;
    int q ;
    cin>>q ;

    fo(i,1,n+1){
        cin>>arr[i] ;
    }

    vector<query>v(q) ;
    fo(i,0,q){
        cin>>v[i].l>>v[i].r ;
        v[i].i = i ;
    }

    vector<ll>ans(q);

    sort(all(v) ,comp);
    int MR = -1 , ML = 0 ;
    fo(i,0,q){
        int l= v[i].l ,r = v[i].r, ind =v[i].i ;
        while(MR<r){
            MR++ , add(MR);
        }

        while(ML>l){
            ML-- , add(ML) ;
        }

        while(MR>r){
            remove(MR) ,MR--;
        }

        while(ML<l){
            remove(ML) ,ML++ ;
        }

        ans[ind] = power ;
    }

    fo(i,0,q){
        cout<<ans[i]<<"\n";
    }

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
