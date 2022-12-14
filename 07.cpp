#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (ll i = (a); i < (b); i++)
#define per(i, a, b) for (ll i = (b)-1; i >= (a); i--)
#define all(x) begin(x), end(x)
using ll = long long;
struct Folder {
	map<string, Folder*> childs;
	Folder* parent;
	map<string, ll> files;
	ll size;
	Folder(Folder *_parent) {
		parent = _parent;
	}
	void add_folder(const string &name) {
		if(childs.count(name) == 0) {
			childs[name] = new Folder(this);
		}
	}
	void add_file(const string &name, ll size) {
		files[name] = size;
	}

};
Folder* cd(Folder* cwd, const string& name) {
	cwd->add_folder(name);
	return cwd->childs[name];
}
void calc_size(Folder *cwd) {
	cwd->size = 0;
	for(auto [name, folder]: cwd->childs) {
		calc_size(folder);
		cwd->size += folder->size;
	}
	for(auto [name, size]: cwd->files) {
		cwd->size += size;
	}
}
const ll inf = 9e18;
ll find_deletable(Folder *cwd, ll threshold) {
	ll ans = inf;
	if(cwd->size >= threshold) ans=cwd->size;
	for(auto [name, folder]: cwd->childs) {
		ll _ans = find_deletable(folder, threshold);
		ans = min(ans, _ans);
	}
	return ans;
}
vector<string> split(const string &line) {
	vector<string> tokens;
	stringstream ss(line);
	string token;
	while(ss>>token) tokens.push_back(token);
	return tokens;
}
int main() {
	ios_base::sync_with_stdio(0);
	Folder *root = new Folder(0);
	string line;
	Folder *cwd;
	while(getline(cin,line)) {
		vector<string> tokens = split(line);
		if(tokens[0] == "$") {
			if(tokens[1] == "cd") {
				if(tokens[2] == "..") {
					cwd = cwd->parent;
				} else if(tokens[2] == "/") {
					cwd = root;
				} else {
					cwd = cd(cwd,tokens[2]);
				}
			}
		} else if(tokens[0] == "dir") {
			cwd->add_folder(tokens[1]);
		} else {
			cwd->add_file(tokens[1], stoll(tokens[0]));
		}
	}
	calc_size(root);
	ll threshold = root->size - 40000000;
	ll ans = find_deletable(root, threshold);
	cout<<ans<<"\n";
}
