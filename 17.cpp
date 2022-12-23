#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
using Shape = vector<string>;
template <typename T>
struct InfiniteSequence {
	vector<T> pattern;
	ll turn = 0;
	InfiniteSequence(const vector<T> &_pattern) {
		pattern = _pattern;
	}
	const T& next() {
		T &val = pattern[turn];
		turn++;
		if(turn == pattern.size()) turn = 0;
		return val;
	}
};
struct World {
	static const ll width = 7;
	vector<string> A;
	InfiniteSequence<ll> commands;
	World(const InfiniteSequence<ll> &_commands) : commands(_commands) { }
	char get(ll x, ll y) {
		if(x < 0 || y < 0 || width <= y)
			return '#';
		if(A.size() <= x)
			return '.';
		return A[x][y];
	}
	void put(const Shape &s, ll x, ll y) {
		if(A.size() < x+s.size()) {
			A.resize(x+s.size(),string(width,'.'));
		}
		rep(i,0,s.size()) rep(j,0,s[i].size())
			if(s[i][j] == '#')
				A[x+i][y+j] = '#';
	}
	bool intersec(const Shape &s, ll x, ll y) {
		rep(i,0,s.size()) rep(j,0,s[i].size())
			if(get(x+i, y+j) == '#' && s[i][j] == '#')
				return true;
		return false;
	}
	tuple<ll,ll> make_fall(const Shape &s) {
		ll x = A.size() + 3, y = 2;
		while(1) {
			ll delta_y = commands.next();
			if(!intersec(s,x,y+delta_y)) {
				y += delta_y;
			}
			if(!intersec(s,x-1,y)) {
				x -= 1;
			} else {
				break;
			}
		}
		put(s,x,y);
		return {x,y};
	}
};
ll calc_sum(const vector<ll> &A, ll begin_cycle, ll niter) {
	if(niter < A.size()) return accumulate(begin(A), begin(A) + niter,0);
	ll len_tail = begin_cycle;
	ll sum_tail = accumulate(begin(A), begin(A) + len_tail,0);
	ll len_cycle = A.size() - begin_cycle;
	ll sum_cycle = accumulate(begin(A) + len_tail, end(A),0);
	ll rem = (niter - len_tail) % len_cycle;
	ll sum_rem = accumulate(begin(A) + begin_cycle, begin(A) + begin_cycle + rem,0);
	return sum_tail + (niter - len_tail) / len_cycle * sum_cycle + sum_rem;
}
int main() {
	ios_base::sync_with_stdio(0);

	Shape horizontal_line{
		"####"
	};
	Shape cross{
		".#.",
		"###",
		".#."
	};
	Shape angle{
		"###",
		"..#",
		"..#"
	};
	Shape vertical_line{
		"#",
		"#",
		"#",
		"#"
	};
	Shape square{
		"##",
		"##"
	};
	vector<Shape> shape_pattern{
		horizontal_line,
		cross,
		angle,
		vertical_line,
		square
	};
	InfiniteSequence<Shape> shapes(shape_pattern);

	string in;
	cin>>in;
	vector<ll> command_pattern(in.size());	
	rep(i,0,in.size()) command_pattern[i] = in[i] == '<' ? -1 : 1;
	InfiniteSequence<ll> commands(command_pattern);

	World world(commands);
	const ll niter = 1e12;
	ll xprev = 0, yprev = 0, hprev = 0;
	// key = shape turn, command turn, dx, dy
	// heuristic: cycle of keys = true cyclye
	map<tuple<ll,ll,ll,ll>,ll> memo;
	vector<ll> dhs;
	ll begin_cycle = -1, len = 0;
	rep(i,0,niter) {
		ll shape_turn = shapes.turn;
		ll command_turn = world.commands.turn;
		const Shape &shape = shapes.next();
		auto [x,y] = world.make_fall(shape);
		ll h = world.A.size();
		ll dh = h - hprev;
		dhs.push_back(dh);
		ll dx = x-xprev, dy = y-yprev;
		auto key = make_tuple(shape_turn, command_turn, dx, dy);
		if(len == 0) {
			if(memo.count(key)) {
				len = i - memo[key];
				begin_cycle = memo[key];
			}
		} else {
			if(!memo.count(key)) {
				len = 0;
			} else if(memo[key] != i-len) {
				len = i - memo[key];
				begin_cycle = memo[key];
			} else if(i+1 == begin_cycle + 2*len) {
				break;
			}	
		}
		memo[key] = i;
		xprev = x, yprev = y;
		hprev = h;
	}
	dhs.erase(end(dhs) - len, end(dhs));
	ll ans = calc_sum(dhs, begin_cycle,niter);
	cout<<ans<<"\n";
}
