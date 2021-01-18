#include<bits/stdc++.h>
#define nl printf("\n");
#define PR pair<ll,ll>
#define sf1(n) scanf("%lld", &n)
#define sf2(n, m) scanf("%lld %lld",&n,&m)
#define sf3(n, m,k ) scanf("%lld %lld %lld",&n,&m,&k)
#define pfn(n) printf("%d\n",n)s
#define pf1(n) printf("%d ",n)
#define pfl1(n) printf("%lld ",n)
#define pfln(n) printf("%lld\n",n)
#define pfu(n) printf("%llu\n",n)
#define pfs(s) printf("%s",s)
#define YES printf("YES\n")
#define NO printf("NO\n")
#define minus1 printf("-1\n")
#define PB push_back
#define PI 3.1415926536
#define VST(v) sort(v.begin(),v.end())
#define VSTcmp(v,cmp) sort(v.begin(),v.end(),cmp)
#define fori(i,n) for(;i<n;i++)
#define fast ios_base::sync_with_stdio(0);cin.tie(0)
#define MP make_pair
#define ff first
#define ss second
#define tt third
#define mod 1000000007
#define T(n) printf("test %d\n",n)
typedef long long int ll;
typedef unsigned long long int ull;
ll dx[] = {0,0,1,-1,2,2,-2,-2,1,-1,1,-1};
ll dy[] = {1,-1,0,0,1,-1,1,-1,2,2,-2,-2};
using namespace std;
#define N 100010
vector<PR>edj[N];
bool color[N];
ll label[N];
ll dis[N];
ll sparse[N][20];
ll parent[N];
void dfs(ll node)
{
    color[node]=false;
    ll siz=edj[node].size();
    for(ll i=0; i<siz; i++)
    {
        ll tm=edj[node][i].ff;
        if(color[tm]==true)
        {
            color[tm]=false;
            label[tm]=label[node]+1;
            dis[tm]=edj[node][i].ss+dis[node];
            parent[tm]=node;
            sparse[tm][0]=node;
            dfs(tm);
        }
    }
}
void pre_process(ll n)
{
    for(ll j=1; (1<<j)<=n; j++)
    {
        for(ll i=1; i<=n; i++)
        {
            sparse[i][j]=sparse[sparse[i][j-1]][j-1];
        }
    }
}
ll query(ll u,ll v)
{
    if(label[u]<label[v])
        swap(u,v);
    ll lg=0;
    for(lg=0; (1<<lg)<=label[u]; lg++)
    {

    }
    lg--;
    if(label[u]!=label[v])
    {
        for(ll i=lg; i>=0; i--)
        {
            if(label[u]-(1<<i)>=label[v])
            {
                u=sparse[u][i];
            }
        }
    }
    if(u==v)
    {
        return u;
    }
    for(ll i=lg; i>=0; i--)
    {
        if(sparse[u][i]!=-1&&sparse[u][i]!=sparse[v][i])
        {
            u=sparse[u][i];
            v=sparse[v][i];
        }
    }
    return parent[u];

}
int main()
{
    // fast;
    //freopen("1input.txt","r",stdin);
    ///freopen("1output.txt","w",stdout);
    ll tcase=1;
    for(ll test=1; test<=tcase; test++)
    {
        ll n,k;
        cin>>n>>k;
        for(ll i=0;i<=n;i++){
            edj[i].clear();
            color[i]=true;
            memset(sparse[i],-1,sizeof(sparse[i]));
            dis[i]=0;
        }
        for(ll i=0; i<(n-1); i++)
        {
            ll u,v;
            cin>>u>>v;
            edj[u].PB({v,0});
            edj[v].PB({u,k});
        }
        label[1]=0;
        dis[1]=0;
        parent[1]=1;
        dfs(1);
        pre_process(n);
        ll qq;
        cin>>qq;
        for(ll i=0; i<qq; i++)
        {
            ll u,v;
            cin>>u>>v;
            ll lc=query(u,v);
            ll aa=((label[u]*k)-dis[u])-((label[lc]*k)-dis[lc]);
            ll bb=dis[v]-dis[lc];
            cout<<aa+bb<<"\n";
        }
        return 0;
    }
///*****************************  ALHAMDULILLAH  *****************************/
}
