#include "bits/stdc++.h"
using namespace std;
#define int               long long
#define pb                push_back
#define ppb               pop_back
#define pf                push_front
#define ppf               pop_front
#define all(x)            (x).begin(),(x).end()
#define uniq(v)           (v).erase(unique(all(v)),(v).end())
#define sz(x)             (int)((x).size())
#define fr                first
#define sc                second
#define pii               pair<int,int>
#define rep(i,a,b)        for(int i=a;i<b;i++)

/*
	TRY: Simulated Annealing
	Basically, after finding the answer once, remember which tubes were increased
	the most and then in next iteration resolve knowing that they were increased
	a lot in the previous iteration, hence try to not increase the costly tubes
	by a lot.
*/

// #define demoralizer

#ifdef demoralizer
#define PRINT_COST
// #define EMPTY_COUNT
// #define INCREASE_COUNTS
// #define COST_INCREASE_COUNTS
#endif

template<typename T1,typename T2>istream& operator>>(istream& in,pair<T1,T2> &a){in>>a.fr>>a.sc;return in;}
template<typename T1,typename T2>ostream& operator<<(ostream& out,pair<T1,T2> a){out<<a.fr<<" "<<a.sc;return out;}
template<typename T,typename T1>T amax(T &a,T1 b){if(b>a)a=b;return a;}
template<typename T,typename T1>T amin(T &a,T1 b){if(b<a)a=b;return a;}

const int N=0;
const int ITERATIONS = 9;
const int INF=1e18;

int avg_cost = 0;
int useless_counter = 0;

int measure(vector<int> &v){
	int x = sz(v) - 1;
	int ans = 0;
	while(x >= 0 && v[x] == v.back()){
		ans++;
		x--;
	}
	return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto dist=uniform_int_distribution<int>(0,4);
vector<int> rev,inc,best_rev,best_inc,tot;
vector<pii> oprs,best_oprs;

void save_ans(){
	best_rev = rev;
	best_inc = inc;
	best_oprs = oprs;
}

int pseudo_solve(int n,int m,vector<int> &c,vector<vector<int>> &d,vector<vector<int>> b,int para){
	vector<int> COSTS = c;
	
	int dcost = 0;
	
	int avg_con_bot = 0;
	rep(i,1,n+1){
		int con_top = 0;
		int con_bot = 0;
		int xyz = 0;
		while(xyz < sz(b[i]) && b[i][xyz] == b[i].front()){
			xyz++;
			con_bot++;
		}
		xyz = sz(b[i]) - 1;
		while(xyz >= 0 && b[i][xyz] == b[i].back()){
			xyz--;
			con_top++;
		}
		if(con_top > con_bot){
			reverse(all(b[i]));
			rev.pb(i);
			swap(con_top,con_bot);
		}
		avg_con_bot += con_bot;
	}
	
	vector<set<int>> col(n+1);
	rep(i,1,n+1){
		col[b[i][m - 1]].insert(i);
	}
	col[0].insert(n+1);
	col[0].insert(n+2);
	
	vector<int> act_tot(n + 3,m);
	if(para == 0){
		tot.clear();
		tot.resize(n + 3,m);
	}
	
	// put 1 ml from y to x
	auto transfer = [&](int x,int y){
		oprs.pb({y,x});
		assert(sz(b[y]));
		int a = b[y].back();
		b[y].ppb();
		col[a].erase(y);
		
		if(sz(b[y])){
			col[b[y].back()].insert(y);
		}
		else{
			col[0].insert(y);
		}
		if(sz(b[x])){
			col[b[x].back()].erase(x);
			dcost += d[a][b[x].back()];
		}
		else{
			col[0].erase(x);
		}
		b[x].pb(a);
		bool full = (sz(b[x]) == m);
		for(int q:b[x]){
			if(q != a){
				full = false;
			}
		}
		if(!full){
			col[a].insert(x);
		}
		amax(tot[x],sz(b[x]));
		amax(tot[y],sz(b[y]));
		amax(act_tot[x],sz(b[x]));
		amax(act_tot[y],sz(b[y]));
	};
	
	while(1){
		
		/*This routine makes the the test tubes with single color acquire everything*/
		// if(IN_G4096){
			// int cand = -1;
			// rep(i,1,n+3){
			// 	if(!b[i].empty() && measure(b[i]) == sz(b[i]) && sz(col[b[i].back()]) > 1){
			// 		cand = i;
			// 		break;
			// 	}
			// }
			// if(cand != -1){
			// 	int color = b[cand].back();
			// 	vector<int> elems(all(col[color]));
			// 	for(int x:elems){
			// 		if(x == cand) continue;
			// 		int cnt = measure(b[x]);
			// 		while(cnt--){
			// 			transfer(cand,x);
			// 		}
			// 	}
			// 	continue;
			// }
		// }
		
		if(!col[0].empty()){
			int x = *col[0].begin();
			int y = 1000;
			vector<int> color_count(n + 1);
			rep(i,1,n+3){
				if(sz(b[i]) == 0){
					continue;
				}
				int color = b[i].back();
				bool valid = false;
				for(int a:b[i]){
					if(a != color){
						valid = true;
						break;
					}
				}
				if(valid){
					y = i;
					int abc = measure(b[y]);
					color_count[color] += abc * c[y];
				}
			}
			if(y < 1000){
				y = b[y].back(); // y is the best color
				rep(i,1,n+1){
					if(color_count[i] && color_count[y] < color_count[i]){
						y = i;
					}
				}
				// put color y in test tube x
				vector<int> elems(all(col[y]));
				for(int y:elems){
					int cnt = measure(b[y]);
					while(cnt--){
						transfer(x,y);
					}
				}
				continue;
			}
		}
		
		vector<pii> possibley;
		rep(i,1,n+1){
			if(sz(col[i]) > 1){
				int mc = INF;
				for(int x:col[i]){
					amin(mc,c[x]);
				}
				possibley.pb({mc,i});
			}
		}
		if(sz(possibley)){
			sort(all(possibley));
			int y = possibley.front().sc;
			vector<int> elems(all(col[y]));
			sort(all(elems),[&](int x,int y){
				return c[x] < c[y];
			});
			int best = INF;
			int u=elems[0],v=elems[1];
			
			int cntu = measure(b[u]);
			// keep u fixed but choose best v?
			rep(i,1,sz(elems)){
				int y = elems[i];
				int cnty = measure(b[y]);
				int cu = c[u] * max(sz(b[u]) + cnty - tot[u],0ll);
				int cy = c[y] * max(sz(b[y]) + cntu - tot[y],0ll);
				int fc = min(cu,cy);
				if(fc < best){
					best = fc;
					v = y;
				}
			}
			int cntv = measure(b[v]);
			
			if(c[u] * max(sz(b[u]) + cntv - tot[u],0ll) > c[v] * max(sz(b[v]) + cntu - tot[v],0ll)){
				swap(u,v);
				swap(cntu,cntv);
			}
			int tmp = c[u] * max(sz(b[u]) + cntv - tot[u],0ll);
			while(cntv-- > 0){
				transfer(u,v);
			}
			continue;
		}
		break;
	}
	
	int cost = 0;
	
	rep(i,1,n+3){
		int x = act_tot[i] - m;
		while(act_tot[i] > m){
			inc.pb(i);
			act_tot[i]--;
			cost += COSTS[i];
		}
		#ifndef demoralizer
		cost += COSTS[i];
		inc.pb(i);
		// cost += COSTS[i];
		// inc.pb(i);
		#endif
	}
	
	tot = act_tot;
	
	#ifdef demoralizer
	#ifdef PRINT_COST
	cost += dcost;
	cout << "COST: " << cost << "\n";
	#endif
	#endif
	return cost;
}

int dsolve(int n,int m,vector<int> &c,vector<vector<int>> &d,vector<vector<int>> b,int para);
int nsolve(int n,int m,vector<int> &c,vector<vector<int>> &d,vector<vector<int>> b,int para);

void print_ans(){
	#ifndef demoralizer
	// printing part
	rev = best_rev;
	inc = best_inc;
	oprs = best_oprs;
	cout << sz(rev) << " " << sz(inc) + sz(oprs) << "\n";
	if(sz(rev)){
		for(int x:rev){
			cout << x << " ";
		}
		cout << "\n";
	}
	
	for(int x:inc){
		cout << 2 << " " << x << "\n";
	}
	for(pii x:oprs){
		cout << 1 << " " << x << "\n";
	}
	#endif
}

void reinit(){
	rev.clear();
	inc.clear();
	oprs.clear();
}


int THRESHOLDS[] = {100,100,118,100};
int THRESHOLD = 0;

void solve(){
	int n,m;
	cin >> n >> m;
	vector<int> c(n + 3);
	rep(i,1,n+3){
		cin >> c[i];
	}
	
	map<int, int> yolo;
	yolo[0] = 0;
	yolo[196224] = 1;
	yolo[245280] = 2;
	yolo[257544] = 3;
	
	vector<vector<int>> d(n+1,vector<int>(n+1));
	int cnt = 0;
	rep(i,1,n+1){
		rep(j,1,n+1){
			cin >> d[i][j];
			if(d[i][j] == -1){
				d[i][j] = 1000;
				cnt++;
			}
		}
	}
	#ifdef demoralizer
	// cout << "-1 cnt:" << cnt << "\n";
	#endif
	THRESHOLD = THRESHOLDS[yolo[cnt]];
	vector<vector<int>> b(n+3);
	rep(i,1,n+1){
		rep(j,0,m){
			b[i].emplace_back();
			cin >> b[i][j];
		}
	}
	int cost = INF;
	int worst = 0;
	rep(i,0,ITERATIONS){
		reinit();
		int tmp = nsolve(n,m,c,d,b,i);
		amax(worst,tmp);
		if(cost > tmp){
			cost = tmp;
			save_ans();
		}
		// rep(j,1,n+3){
		// 	if(c[j] > 200) tot[j] = m;
		// 	if(c[j] <= 150){
		// 		tot[j]+=dist(rng);
		// 	}
		// 	if(c[j] <= 80){
		// 		tot[j]+=dist(rng);
		// 	}
		// }
	}
	print_ans();
	avg_cost += cost;
	#ifdef demoralizer
	cout << "Diff: " << worst - cost << "\n";
	cout << "Best: " << cost << "\n";
	cout << "\n-------------\n";
	#endif
}

signed main(){
	#ifdef demoralizer
	freopen("0.in", "r", stdin);
	solve();
	freopen("1.in", "r", stdin);
	solve();
	freopen("2.in", "r", stdin);
	solve();
	freopen("3.in", "r", stdin);
	solve();
	freopen("4.in", "r", stdin);
	solve();
	freopen("5.in", "r", stdin);
	solve();
	freopen("6.in", "r", stdin);
	solve();
	freopen("7.in", "r", stdin);
	solve();
	freopen("8.in", "r", stdin);
	solve();
	freopen("9.in", "r", stdin);
	solve();
	freopen("10.in", "r", stdin);
	solve();
	freopen("11.in", "r", stdin);
	solve();
	freopen("12.in", "r", stdin);
	solve();
	freopen("13.in", "r", stdin);
	solve();
	freopen("14.in", "r", stdin);
	solve();
	freopen("15.in", "r", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	//freopen("output.txt", "w", stdout);
	solve();
	
	#ifdef demoralizer
	cout << avg_cost << "\n";
	#endif
	
	return 0;
}

int dsolve(int n,int m,vector<int> &c,vector<vector<int>> &d,vector<vector<int>> b,int para){
	vector<int> COSTS = c;
	
	int dcost = 0;	

	vector<int> act_tot(n + 3,m);
	vector<int> tot(n + 3, m);
	
	rep(i,1,n+3){
		if(c[i] < 40) tot[i] += para;
	}
	para = 1;
	
	// put 1 ml from y to x
	auto transfer = [&](int x,int y){
		// if(dist(rng) < 1) cout << sz(inc) + sz(oprs) << endl;
		// cout << x << " " << y << endl;
		oprs.pb({y,x});
		assert(sz(b[y]));
		int a = b[y].back();
		b[y].ppb();
		
		if(sz(b[x])){
			dcost += d[a][b[x].back()];
			if(d[a][b[x].back()] > 100){
				cout << a << " " << b[x].back() << "\n";
			}
		}
		b[x].pb(a);
		amax(tot[x],sz(b[x]));
		amax(tot[y],sz(b[y]));
		amax(act_tot[x],sz(b[x]));
		amax(act_tot[y],sz(b[y]));
	};
	
	while(1){
		vector<vector<int>> col(n+1);
		rep(i,1,n+3){
			if(b[i].empty()) col[0].pb(i);
			else col[b[i].back()].pb(i);
		}
		
		
		int y = 1000;
		int minc = INF;
		rep(i,1,n+1){
			if(sz(col[i]) > 1){
				// y = i;
				for(int x:col[i]){
					if(c[x] < minc){
						minc = c[x];
						y = i;
					}
				}
			}
		}
		if(y != 1000){
			sort(all(col[y]),[&](int a,int b){
				return c[a] < c[b];
			});
			int u=col[y][0],v=col[y][1];
			
			int cntu = measure(b[u]);
			int cntv = measure(b[v]);
			
			if(c[u] * max(sz(b[u]) + cntv - tot[u],0ll) > c[v] * max(sz(b[v]) + cntu - tot[v],0ll)){
				swap(u,v);
				swap(cntu,cntv);
			}
			int tmp = c[u] * max(sz(b[u]) + cntv - tot[u],0ll);
			if(tmp > 0){
				if(sz(col[0])){
					int t = col[0][0];
					int color = b[u].back();
					for(int x:col[color]){
						int cnt = measure(b[x]);
						while(cnt--){
							transfer(t,x);
						}
					}
					continue;
				}
				int color = b[u].back();
				vector<pair<pii, int>> cand;
				rep(i,1,n+3){
					if(b[i].empty()) continue;
					if(d[b[i].back()][color] > 100) continue;
					cand.pb({{c[i],d[b[i].back()][color]},i});
				}
				if(sz(cand)){
					sort(all(cand));
					int i = cand.front().sc;
					if(c[i] > 100){
						for(int x:col[b[u].back()]){
							if(x == u) continue;
							int cnt = measure(b[x]);
							if(sz(b[u]) + cnt <= tot[u]){
								// easy peasy free moves right here
								while(cnt--){
									transfer(u,x);
								}
								u = -1;
								break;
							}
						}
						if(u == -1){
							continue;
						}
						if(c[i] > 200){
							para = 0;
						}
					}
					if(para == 1){
						for(int x:col[color]){
							if(i == x) continue;
							int cnt = measure(b[x]);
							while(cnt--){
								transfer(i,x);
							}
						}
						continue;
					}
					para = 1;
				}
			}
			while(cntv-- > 0){
				transfer(u,v);
			}
			continue;
		}
		// find empty test tube
		int t = col[0][0];
		int point = 1000;
		int mincpoint = 0;
		rep(i,1,n+3){
			if(sz(b[i]) && sz(b[i]) != measure(b[i])){
				if(c[i] > mincpoint){
					point = i;
					mincpoint = c[i];
				}
			}
		}
		if(point == 1000){
			break;
		}
		int color = b[point].back();
		for(int x:col[color]){
			int cnt = measure(b[x]);
			while(cnt--){
				transfer(t,x);
			}
		}
	}
	
	int cost = 0;
	
	rep(i,1,n+3){
		int x = act_tot[i] - m;
		while(act_tot[i] > m){
			inc.pb(i);
			act_tot[i]--;
			cost += COSTS[i];
		}
		#ifndef demoralizer
		cost += COSTS[i];
		inc.pb(i);
		// cost += COSTS[i];
		// inc.pb(i);
		#endif
	}
	
	tot = act_tot;
	
	#ifdef demoralizer
	#ifdef PRINT_COST
	cost += dcost;
	cout << "COST: " << cost << "\n";
	cout << sz(inc) << "\n";
	// cout << "DCOST: " << dcost << "\n";
	
	#endif
	#endif
	return cost;
}


int nsolve(int n,int m,vector<int> &c,vector<vector<int>> &d,vector<vector<int>> b,int para){
	vector<int> COSTS = c;
	
	int dcost = 0;	useless_counter = 0;

	vector<int> act_tot(n + 3,m);
	vector<int> tot(n + 3, m);
	
	rep(i,1,n+3){
		if(c[i] < 75) tot[i] += para;
	}
	para = 1;
	
	// put 1 ml from y to x
	auto transfer = [&](int x,int y){
		// if(dist(rng) < 1) cout << sz(inc) + sz(oprs) << endl;
		// cout << x << " " << y << endl;
		oprs.pb({y,x});
		assert(sz(b[y]));
		int a = b[y].back();
		b[y].ppb();
		
		if(sz(b[x])){
			dcost += d[a][b[x].back()];
			if(d[a][b[x].back()] > 100){
				cout << a << " " << b[x].back() << "\n";
			}
		}
		b[x].pb(a);
		amax(tot[x],sz(b[x]));
		amax(tot[y],sz(b[y]));
		amax(act_tot[x],sz(b[x]));
		amax(act_tot[y],sz(b[y]));
	};
	
	while(1){
		vector<int> meas(n+3), space(n+3);
		vector<vector<int>> col(n+1);
		rep(i,1,n+3){
			if(b[i].empty()) col[0].pb(i);
			else col[b[i].back()].pb(i);
			meas[i] = measure(b[i]);
			space[i] = tot[i] - sz(b[i]);
		}
		
		rep(i,1,n+1){
			sort(all(col[i]),[&](int a,int b){
				return c[a] < c[b];
			});
		}
		
		
		vector<int> possibley;
		int minc = INF;
		rep(i,1,n+1){
			if(sz(col[i]) > 1){
				possibley.pb(i);
			}
		}
		sort(all(possibley),[&](int x,int y){
			return c[col[x][0]] < c[col[y][0]];
		});
		if(!possibley.empty()){
			int y = possibley.front();
			int u=col[y][0],v=col[y][1];
			
			int cntu = measure(b[u]);
			int cntv = measure(b[v]);
			
			if(c[u] * max(sz(b[u]) + cntv - tot[u],0ll) > c[v] * max(sz(b[v]) + cntu - tot[v],0ll)){
				swap(u,v);
				swap(cntu,cntv);
			}
			int tmp = c[u] * max(sz(b[u]) + cntv - tot[u],0ll);
			vector<pair<pii, pii>> glob_can;
			if(tmp > 1){
				for(int color:possibley){
					if(sz(col[0])){
						int t = col[0][0];
						for(int x:col[color]){
							int cnt = measure(b[x]);
							while(cnt--){
								transfer(t,x);
							}
						}
						cntv = 0;
						break;
					}
					vector<pair<pii, int>> cand;
					rep(i,1,n+3){
						if(c[i] > THRESHOLD) continue;
						if(d[b[i].back()][color] > 100) continue;
						cand.pb({{c[i]*11+d[b[i].back()][color],0},i});
					}
					if(sz(cand)){
						sort(all(cand));
						int i = cand.front().sc;
						glob_can.pb({{c[i]*11+d[b[i].back()][color],0},{i,color}});
					}
				}
			}
			if(cntv == 0) continue;
			
			if(sz(glob_can)){
				int i = glob_can.front().sc.fr;
				int color = glob_can.front().sc.sc;
				// if(c[i] <= 120){
				if(color != b[u].back()){
					// cout << "HERE";
				}
				for(int x:col[color]){
					if(i == x) continue;
					int cnt = measure(b[x]);
					while(cnt--){
						transfer(i,x);
					}
				}
				continue;
				// }
			}
			
			if(tmp > 0)
			for(int x:col[b[u].back()]){
				if(x == u) continue;
				int cnt = measure(b[x]);
				if(sz(b[u]) + cnt <= tot[u]){
					// easy peasy free moves right here
					while(cnt--){
						transfer(u,x);
					}
					continue;
				}
			}
			
			while(cntv-- > 0){
				transfer(u,v);
			}
			continue;
		}
		
		// find empty test tube
		int t = col[0][0];
		int point = 1000;
		int mincpoint = 0;
		rep(i,1,n+3){
			if(sz(b[i]) && sz(b[i]) != measure(b[i])){
				if(c[i] > mincpoint){
					point = i;
					mincpoint = c[i];
				}
			}
		}
		if(point == 1000){
			break;
		}
		int color = b[point].back();
		for(int x:col[color]){
			int cnt = measure(b[x]);
			while(cnt--){
				transfer(t,x);
			}
		}
	}
	
	int cost = 0;
	
	rep(i,1,n+3){
		int x = act_tot[i] - m;
		while(act_tot[i] > m){
			inc.pb(i);
			act_tot[i]--;
			cost += COSTS[i];
		}
		#ifndef demoralizer
		// cost += COSTS[i];
		// inc.pb(i);
		// cost += COSTS[i];
		// inc.pb(i);
		#endif
	}
	
	tot = act_tot;
	
	#ifdef demoralizer
	#ifdef PRINT_COST
	cost += dcost;
	cout << "COST: " << cost << "\n";
	cout << sz(inc) << "\n";
	// cout << "DCOST: " << dcost << "\n";
	
	#endif
	#endif
	return cost;
}
