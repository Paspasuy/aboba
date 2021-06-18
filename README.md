# aboba
#include "bits/stdc++.h"
using namespace std;
#define all(arr) (arr).begin(), (arr.end())
#define range(i, n) for (int i = 0; i < n; ++i)
#define sz(arr) int((arr).size())
using pii = pair<int, int>;
using ar3 = array<int, 3>;
using va3 = vector<ar3>;
using ld = long double;
#define F first
#define S second
#define pb push_back

const int Inf = 1e9+7;
const int MP = 21;

int pi, n, m;
int dist[MP][MP];

struct planet {
	int id, cnt, lvl, def;
};

ld kl = 0.85;

planet p[MP];

int upgc(int x) {
	if (p[x].lvl == 3)
		return Inf;
	return p[x].lvl * 100;
}

void read() {
	cin >> pi >> n >> m;
	--pi;
	range(i, m) {
		range(j, m) {
			cin >> dist[i][j];
		}
	}
}

int get_best() {
	if (n == 2) {
		return 1 ^ pi;
	}
	pii mx;
	range(i, n) {
		if (i == pi)
			continue;
		int score = 0;
		range(j, m) {
			if (p[j].id == j) {
				score += p[j].cnt + p[j].lvl * 10 + p[j].def;
			}
		}
		mx = max(mx, {score, i});
	}
	return mx.S;
}

int stod(int i) {
	int ans = p[i].cnt + p[i].def + 50;
	return ans;
}

int gwp(int pl) {
	pii pog = {Inf, -1};
	range(i, m) {
		if (p[i].id != pl)
			continue;
		pog = min(pog, {stod(i), pl});
	}
	return pog.S;
}

int get_fcs() {
	int cnt = 0;
	range(i, m) {
		if (p[i].id == pi) {
			cnt += int(p[i].cnt * kl);
		}
	}
	return cnt;
}

va3 moves;

void atk(int pl, int cnt) {
	range(i, m) {
		if (cnt == 0)
			return;
		if (i != pi)
			continue;
		int x = (int)(p[i].cnt) * kl;
		int nc = max(0, cnt - x);
		moves.pb(ar3{i, pl, cnt - nc});
		cnt = nc;
	}
}

void upg_self(int p) {
	moves.pb(ar3{p, p, upgc(p)});
}

signed main() {
	read();
	for (;;) {
		moves.clear();
		int x;
		cin >> x;
		if (x == -1)
			return 0;
		range(i, x) {
			int id, from, to, cnt;
			cin >> id >> from >> to >> cnt;
		}
		range(i, m) {
			cin >> p[i].id >> p[i].cnt >> p[i].lvl >> p[i].def;
			--p[i].id;
		}
		int best = get_best();
		int ma = get_fcs();
		int pli = gwp(best);
		if (stod(pli) < ma) {
			atk(pli, stod(pli));
		}
		range(i, m) {
			if (p[i].id == pi) {
				if (upgc(i) <= p[i].cnt) {
					upg_self(i);
				}
			}
		}
		cout << sz(moves) << endl;
		for (ar3 move: moves) {
			cout << move[0] + 1 << ' ' << move[1] + 1 << ' ' << move[2] << endl;
		}
	}
}
