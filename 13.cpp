#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
struct Signal {
	variant<ll,vector<Signal>> content;
	Signal(ll val) : content(val) { }
	Signal(const vector<Signal> &list) : content(list) { }
	Signal(const Signal &rhs) : content(rhs.content) { }
	bool is_list() const {
		return content.index() == 1;
	}
	const vector<Signal>& get_list() const {
		return get<vector<Signal>>(content);
	}
	const ll& get_ll() const {
		return get<ll>(content);
	}
	
};
Signal parse(string:: iterator &it);
ll val(char c) { return c-'0'; }
ll parse_ll(string::iterator &it) {
	ll num = 0;
	for(; isdigit(*it); it++) {
		num = num*10 + val(*it);
	}
	return num;
}
vector<Signal> parse_list(string::iterator &it) {
	it++;
	vector<Signal> childs;
	while(*it != ']') {
		if(*it == ',') {
			it++;
		}
		auto child = parse(it);
		childs.push_back(child);
	}
	it++;
	return childs;
}
Signal parse(string::iterator &it) {
	return *it == '[' ?
		Signal(parse_list(it)) :
		Signal(parse_ll(it));
}
ostream& operator <<(ostream& os, const Signal &A) {
	if(A.is_list()) {
		os<<"[";
		for(auto child: A.get_list()) os<<child<<",";
		os<<"]";
	} else {
		os<<A.get_ll();
	}
	return os;
}
bool operator <(const Signal &lhs, const Signal &rhs) {
	if(lhs.is_list()) {
		auto &lhs_content = lhs.get_list();
		if(rhs.is_list()) {
			auto &rhs_content = rhs.get_list();
			return lhs_content < rhs_content;
		} else {
			vector<Signal> wrapper{rhs};
			return lhs_content < wrapper;
		}
	} else {
		if(rhs.is_list()) {
			vector<Signal> wrapper{lhs};
			auto &rhs_content = rhs.get_list();
			return wrapper < rhs_content;
		} else {
			return lhs.get_ll() < rhs.get_ll();
		}
	}
}
bool operator ==(const Signal &lhs, const Signal &rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}
int main() {
	ios_base::sync_with_stdio(0);
	string signal_str;
	vector<Signal> signals;
	while(cin>>signal_str) {
		auto it = begin(signal_str);
		Signal signal = parse(it);
		signals.push_back(signal);
	}
	Signal diva(vector<Signal>{Signal(vector<Signal>{Signal(2ll)})});
	Signal divb(vector<Signal>{Signal(vector<Signal>{Signal(6ll)})});
	signals.push_back(diva);
	signals.push_back(divb);
	sort(all(signals));
	ll posa = find(all(signals), diva) - begin(signals) + 1;
	ll posb = find(all(signals), divb) - begin(signals) + 1;
	cout<<posa * posb<<"\n";
}
