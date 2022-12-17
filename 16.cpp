#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
struct NodeInfo {
	string id;
	vector<string> ady;
	ll rate;
};
NodeInfo parse(const string &line) {
	string no_commas(line);
	no_commas.erase(remove(all(no_commas), ','), end(no_commas));
	stringstream in(no_commas);
	NodeInfo info;
	in.ignore(6);
	in>>info.id;
	in.ignore(15);
	in>>info.rate;
	in.ignore(24);
	string id;
	while(in>>id) info.ady.push_back(id);
	return info;
}
ostream& operator <<(ostream& os, const NodeInfo& info) {
	os<<info.id<<" "<<info.rate<<" ";
	for(const string& to: info.ady) os<<to<<" ";
	return os;
}
using Graph = vector<vector<ll>>;
struct Backtrack {
	vector<vector<ll>> D;
	vector<ll> R,vis;
	ll ans, start, maxt = 26;
	Backtrack(const vector<vector<ll>> &_D, const vector<ll> &_R, ll _start) {
		D = _D;
		R = _R;
		vis.resize(D.size());
		ans = 0;
		start = _start;
		dfs1(start,0);
	}
	void calc() {
		ll cnt = 0;
		rep(i,0,vis.size()) if(vis[i]) cnt += R[i] * (maxt - vis[i]);
		ans = max(ans,cnt);
	}
	void dfs2(ll x, ll T) {
		vis[x] = T;
		calc();
		rep(i,0,D.size())
			if(!vis[i] && R[i] > 0 && T+D[x][i] < maxt)
				dfs2(i,T+D[x][i]);
		vis[x] = 0;
	}
	void dfs1(ll x, ll T) {
		vis[x] = T;
		calc();
		dfs2(start,0);
		rep(i,0,D.size())
			if(!vis[i] && R[i] > 0 && T+D[x][i] < maxt)
				dfs1(i,T+D[x][i]);
		vis[x] = 0;
	}
};
int main() {
	ios_base::sync_with_stdio(0);
	string line;
	vector<NodeInfo> infos;
	while(getline(cin, line)) {
		auto info = parse(line);
		infos.push_back(info);
	}
	map<string,ll> M;
	for(auto info: infos) M[info.id] = M.size();
	Graph g(M.size());
	vector<ll> R(g.size());
	for(auto info: infos) {
		R[M[info.id]] = info.rate;
		for(auto to: info.ady) {
			g[M[info.id]].push_back(M[to]);
		}
	}
	const ll inf = 31;
	vector<vector<ll>> D(g.size(), vector<ll>(g.size(),inf));
	rep(i,0,g.size()) {
		D[i][i] = 0;
		for(ll j: g[i]) D[i][j] = 1;
	}
	rep(k,0,g.size())
		rep(i,0,g.size())
			rep(j,0,g.size())
				D[i][j] = min(D[i][k] + D[k][j], D[i][j]);
	rep(i,0,g.size()) rep(j,0,g.size()) D[i][j]++;
	Backtrack backtrack(D,R,M["AA"]);
	cout<<backtrack.ans<<"\n";
}
