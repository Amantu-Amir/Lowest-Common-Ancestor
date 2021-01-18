#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e6;

bool vis[N];
ll sparse[N][20],dis[N];
ll label[N], parent[N];
vector<pair<ll,ll>>G[N];

void dfs(ll root){
	vis[root]=true;
	ll sz=G[root].size();
	for(ll i=0; i<sz; i++){
		ll child = G[root][i].F;
		ll cost = G[root][i].S;
		if(vis[child]==false){
			label[child] = label[root]+1;
			dis[child] = dis[root]+cost;
			parent[child] = root;
			sparse[child][0] = root;
			dfs(child);
		}
	}
}

void pre_process(ll n){
	for(ll j=1; (1<<j)<n; j++){
		for(ll i=1; i<=n; i++){
			sparse[i][j] = sparse[sparse[i][j-1]][j-1];
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

int main(){

	//freopen("output.txt", "w", stdout);
	//freopen("input.txt", "r", stdin);
	//ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

	ll t=1;
	while(t--){
		ll n; cin>>n;
		ll u,v;
		for(ll i=0; i<(n-1); i++){
			cin>>u>>v;
			G[u].pb({v,0});
			G[v].pb({u,1});			//Reverse cost 1
		}
		label[1]=0; dis[1]=0;
		parent[1]=1;
		dfs(1);
		pre_process(n);
		ll q; cin>>q;
		while(q--){
			cin>>u>>v;
			ll lca=query(u,v);
			cout<<"Lowest Common Ancestor = "<<lca<<"\n";
			ll aa=(label[u]-dis[u])-(label[lca]-dis[lca]);
			ll bb=dis[v]-dis[lca];
			ll res=aa+bb;
			cout<<"Distance = "<<res<<"\n";
		}
	}

	return 0;
}

