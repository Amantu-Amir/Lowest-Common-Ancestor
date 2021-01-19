
//https://atcoder.jp/contests/abc187/tasks/abc187_e

#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2e5;

bool vis[N+5];
ll parent[N+5];
ll label[N+5];
ll ar[N+5];
ll sparse[N+5][20];
vector<ll>G[N+5];

void dfs(ll root){
	vis[root]=true;
	for(auto child:G[root]){
		if(vis[child]==false){
			label[child]=label[root]+1;
			parent[child]=root;
			sparse[child][0]=root;
			dfs(child);
		}
	}
}

void pre_precess(ll n){
	for(ll j=1; (1<<j)<=n; j++){
		for(ll i=1; i<=n; i++){
			sparse[i][j]=sparse[sparse[i][j-1]][j-1];
		}
	}
}

ll query(ll u, ll v){
	if(label[u]<label[v]){
		swap(u,v);
	}
	ll lg=0;
	while((1<<lg)<=label[u]){
		lg++;
	}
	lg--;
	if(label[u]!=label[v]){
		for(ll i=lg; i>=0; i--){
			if((label[u]-(1<<i))>=label[v]){
				u=sparse[u][i];
			}
		}
	}
	if(u==v){return u;}
	for(ll i=lg; i>=0; i--){
		if(sparse[u][i]!=-1 and sparse[u][i]!=sparse[v][i]){
			u=sparse[u][i]; v=sparse[v][i];
		}
	}
	return parent[u];
}

void propagation(ll root){
	vis[root]=true;
	for(auto child:G[root]){
		if(vis[child]==false){
			ar[child]+=ar[root];
			propagation(child);
		}
	}
}

int main(){

	//freopen("output.txt", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

	ll t=1;
	while(t--){
		ll n; cin>>n;
		ll u,v;
		vector<pair<ll,ll>>A(n+5);
		for(ll i=0; i<(n-1); i++){
			cin>>u>>v;
			G[u].pb(v);
			G[v].pb(u);
			A[i+1].F=u;
			A[i+1].S=v;
		}
		label[1]=0;
		parent[1]=0;
		dfs(1);
		pre_precess(n);
		ll q; cin>>q;
		ll type,val,idx;
		while(q--){
			cin>>type>>idx>>val;
			if(type==1){
				u=A[idx].F, v=A[idx].S;
				ll lca=query(u,v);
				if(lca==v){
					ar[u]+=val;
				}
				else{
					ar[1]+=val;
					ar[v]-=val;
				}
			}
			else{
				u=A[idx].S, v=A[idx].F;
				ll lca=query(u,v);
				if(lca==v){
					ar[u]+=val;
				}
				else{
					ar[1]+=val;
					ar[v]-=val;
				}
			}
		}
		for(ll i=0; i<=N; i++){
			vis[i]=false;
		}
		propagation(1);
		for(ll i=1; i<=n; i++){
			cout<<ar[i]<<"\n";
		}
	}

	return 0;
}

