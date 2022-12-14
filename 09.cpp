#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
ll dist(const tuple<ll,ll> &A, const tuple<ll,ll> &B) {
	return max(abs(get<0>(A) - get<0>(B)), abs(get<1>(A) - get<1>(B)));
}
void operator +=(tuple<ll,ll> &lhs, const tuple<ll,ll> &rhs) {
	get<0>(lhs) += get<0>(rhs);
	get<1>(lhs) += get<1>(rhs);
}
void follow(tuple<ll,ll> &follower, const tuple<ll,ll> &followed) {
	ll dx=0,dy=0;
	if(get<0>(followed) > get<0>(follower)) dx = 1;
	if(get<0>(followed) < get<0>(follower)) dx = -1;
	if(get<1>(followed) > get<1>(follower)) dy = 1;
	if(get<1>(followed) < get<1>(follower)) dy = -1;
	follower += {dx,dy};
}
struct Rope {
	ll N;
	vector<tuple<ll,ll>> A;
	Rope(ll _N) {
		N = _N;
		A.resize(N);
	}
	void advance(tuple<ll,ll> delta) {
		A.front() += delta;
		rep(i,1,N) {
			if(dist(A[i-1], A[i]) > 1) {
				follow(A[i], A[i-1]);
			}
		}
	}
};
int main() {
	ios_base::sync_with_stdio(0);
	map<string,tuple<ll,ll>> M({
		{"R", {0,1}},
		{"U", {1,0}},
		{"L", {0,-1}},
		{"D", {-1,0}}
	});
	string dir;
	ll cnt;
	set<tuple<ll,ll>> visited({{0,0}});
	Rope rope(10);
	while(cin>>dir>>cnt) {
		auto delta = M[dir];
		rep(i,0,cnt) {
			rope.advance(delta);
			visited.insert(rope.A.back());
		}
	}
	cout<<visited.size()<<"\n";
}
