#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
int main() {
	ios_base::sync_with_stdio(0);
	ll T = 0, X=1, ans=0;
	string inst;
	ll arg;
	auto check = [&]() {
		ll y = T%40;
		char c = abs(y-X) <= 1 ? '#' : '.';
		cout<<c;
		if(y == 39) cout<<"\n";
		T++;
	};
	while(cin>>inst) {
		if(inst == "noop") {
			check();
		} else {
			cin>>arg;
			check();
			check();
			X+=arg;
		}
	}
	cout<<ans<<"\n";

}
