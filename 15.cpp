#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
pair<pair<ll,ll>,pair<ll,ll>> parse_line(const string &line) {
	const ll maxn = 100;
	ll sx,sy,bx,by;
	stringstream ss(line);
	ss.ignore(maxn, '=');
	ss>>sx;
	ss.ignore(maxn, '=');
	ss>>sy;
	ss.ignore(maxn, '=');
	ss>>bx;
	ss.ignore(maxn, '=');
	ss>>by;
	return make_pair(make_pair(sx,sy), make_pair(bx,by));
}
ll man_dist(const pair<ll,ll> &sensor, const pair<ll,ll> &beacon) {
	return abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
}
int main() {
	ios_base::sync_with_stdio(0);
	vector<pair<pair<ll,ll>,pair<ll,ll>>> A;
	string line;
	while(getline(cin, line)) {
		auto parsed = parse_line(line);
		A.push_back(parsed);
	}
	const ll lo = 0, hi = 4000000;
	ll xans, yans;
	rep(Y,lo,hi+1) {
		vector<tuple<ll,ll>> used;
		for(auto [sensor, beacon]: A) {
			ll D = man_dist(sensor,beacon);
			ll rank = abs(sensor.second - Y);
			if(rank > D) continue;
			ll l = sensor.first - D + rank;
			ll r = sensor.first + D - rank;
			used.push_back(make_pair(l,r));
		}
		sort(all(used));
		ll L = lo, R = L-1;
		optional<ll> non_beacon;
		for(auto [l,r]: used) {
			if(l > hi) break;
			r = min(r,hi);
			if(R+1<l) {
				non_beacon = R+1;
				L = l;
			}
			R = max(R,r);
		}
		if(non_beacon) {
			yans = Y;
			xans = *non_beacon;
		}
	}
	const ll B = 4000000;
	ll ans = xans * B + yans;
	cout<<ans<<"\n";
}
