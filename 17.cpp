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
	void make_fall(const Shape &s) {
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
	}
};
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
	const ll niter = 2022;
	rep(i,0,niter) {
		const Shape &shape = shapes.next();
		world.make_fall(shape);
	}
	cout<<world.A.size()<<"\n";
}
