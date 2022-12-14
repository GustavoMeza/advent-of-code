#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
ll MOD;
struct Monkey {
	vector<ll> q;
	ll op_type, op_val, test_val;
	ll monkey_true_id, monkey_false_id;
	Monkey *monkey_true, *monkey_false;
	ll n_inspects=0;
	void inspect(ll x) {
		if(op_type == 0) {
			x+=op_val;
		} else if(op_type == 1){
			x*=op_val;
		} else {
			x*=x;
		}
		x%=MOD;
		if(x%test_val == 0) monkey_true->q.push_back(x);
		else monkey_false->q.push_back(x);
	}
	void turn() {
		for(ll x: q) inspect(x);
		n_inspects+=q.size();
		q.clear();
	}
};
vector<string> split(string line) {
	stringstream ss(line);
	vector<string> words;
	string word;
	while(ss>>word) words.push_back(word);
	return words;
}
vector<Monkey*> read() {
	string line;
	vector<string> words;
	vector<Monkey*> monkeys;
	while(getline(cin, line)) {
		Monkey *m = new Monkey();

		getline(cin,line);
		line.erase(remove(all(line), ','), end(line));
		words = split(line);
		rep(i,2,words.size()) m->q.push_back(stoll(words[i]));

		getline(cin,line);
		words = split(line);
		if(words[4] == "+") {
			m->op_type = 0;
			m->op_val = stoll(words[5]);
		} else if(words[5] != "old") {
			m->op_type = 1;
			m->op_val = stoll(words[5]);
		} else {
			m->op_type = 2;
		}

		getline(cin,line);
		words = split(line);
		m->test_val = stoll(words[3]);

		getline(cin,line);
		words = split(line);
		m->monkey_true_id = stoll(words[5]);

		getline(cin,line);
		words = split(line);
		m->monkey_false_id = stoll(words[5]);

		monkeys.push_back(m);
		
		getline(cin,line);
	}
	for(auto m: monkeys) {
		m->monkey_true = monkeys[m->monkey_true_id];
		m->monkey_false = monkeys[m->monkey_false_id];
	}
	MOD = 1;
	for(auto m: monkeys) MOD = MOD * m->test_val;
	return monkeys;
}
int main() {
	ios_base::sync_with_stdio(0);
	vector<Monkey*> monkeys = read();
	ll N = monkeys.size();
	ll n_rounds = 1e4;
	rep(t,0,n_rounds) {
		for(auto m : monkeys) m->turn();
	}
	vector<ll> n_inspects(N);
	rep(i,0,N) n_inspects[i] = monkeys[i]->n_inspects;
	sort(all(n_inspects));
	cout<<n_inspects[N-2] * n_inspects[N-1]<<"\n";
}
