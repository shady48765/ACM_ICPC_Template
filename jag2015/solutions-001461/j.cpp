#include <stdio.h>
#include <stdlib.h>
/*
	Problem: Rough Minimum (Spring Contest 2015)
	Solution by: Fumiya Suto
	
	O(N log N)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

const int MAX_N = (1<<16);
const int INF = 2000000007;

pair<int, int> seg[2*MAX_N-1];
int visit[50000];
int eraserIdx[50000];
int rangeP[50000];
int rangeM[50000];

void init(){
	int idx = 0, interval = 1, add = MAX_N;
	while(idx < 2*MAX_N-1){
		for(int i=0,j=idx;j<idx+interval;i+=add,j++){
			seg[j] = make_pair(INF, i);
		}
		idx += interval;
		interval *= 2;
		add /= 2;
	}
}

void update(int val, int idx){
	int k = idx+MAX_N-1;
	seg[k] = make_pair(val, idx);
	while(k > 0){
		k = (k-1)/2;
		seg[k] = min(seg[2*k+1], seg[2*k+2]);
	}
}

pair<int, int> getMin(int a, int b, int k = 0, int l = 0, int r = MAX_N){
	if(r <= a || b <= l) return make_pair(INF, MAX_N);
	if(a <= l && r <= b) return seg[k]; 
	pair<int, int> vl = getMin(a, b, 2*k+1, l, (l+r)/2);
	pair<int, int> vr = getMin(a, b, 2*k+2, (l+r)/2, r);
	return min(vl, vr);
}

int getStartIdx(){
	if(seg[0].first == INF) return -1;
	int k = 0, l = 0, r = MAX_N;
	while(r-l > 1){
		if(seg[2*k+1].first != INF){
			k = 2*k+1;
			r = (l+r)/2;
		} else {
			k = 2*k+2;
			l = (l+r)/2;
		}
	}
	return l;
}

void initialize(const vector< pair<int, int> >& vp, int D){
	init();
	for(int i=0;i<vp.size();i++) update(vp[i].second, i);
	memset(visit, 0, sizeof(visit));
	memset(eraserIdx, -1, sizeof(eraserIdx));
	int idx = 0;
	for(int i=0;i<vp.size();i++){
		while(idx+1 < vp.size() && vp[idx+1].first <= vp[i].first+D) ++idx;
		rangeP[i] = idx;
	}
	idx = vp.size()-1;
	for(int i=vp.size()-1;i>=0;i--){
		while(idx-1 >= 0 && vp[idx-1].first >= vp[i].first-D) --idx;
		rangeM[i] = idx;
	}
	map< int, vector<int> >mp;
	for(int i=0;i<vp.size();i++){
		if(!mp.count(vp[i].second)){
			mp[vp[i].second] = vector<int>(1, i);
		} else {
			mp[vp[i].second].push_back(i);
		}
	}
	for(auto it=mp.begin();it!=mp.end();++it){
		const vector<int>& vi = it->second;
		idx = 0;
		for(int i=0;i<vi.size();i++){
			while(idx+1 < vi.size() && vp[vi[idx+1]].first <= vp[vi[i]].first+D) ++idx;
			if(i != idx) eraserIdx[vi[i]] = vi[idx];
		}
	}
}

bool updateVisit(int idx){
	bool res = false;
	if(visit[idx] == 2) res = true;
	int e = eraserIdx[idx];
	if(e == -1) res = true;
	else {
		if(visit[e] == 1) res = true;
		if(visit[e] == 0){
			visit[e] = 2;
		}
	}
	visit[idx] = 1;
	update(INF, idx);
	return res;
}

int main(){
	int N, D;
	while(cin >> N >> D && N){
		vector< pair<int, int> > vp(N);
		for(int i=0;i<N;i++){
			cin >> vp[i].first >> vp[i].second;
		}
		sort(vp.begin(), vp.end());
		initialize(vp, D);
		while(true){
			int start = getStartIdx();
			if(start == -1) break;
			start = getMin(start, rangeP[start]+1).second;
			bool end = false;
			queue<int> qu; qu.push(start);
			end |= updateVisit(start);
			while(!qu.empty()){
				int p = qu.front(); qu.pop();
				while(true){
					pair<int, int> pr = getMin(0, rangeM[p]);
					if(pr.first == INF) break;
					qu.push(pr.second);
					end |= updateVisit(pr.second);
				}
				while(true){
					pair<int, int> pr = getMin(rangeM[p], rangeP[p]+1);
					if(pr.first >= vp[p].second) break;
					qu.push(pr.second);
					end |= updateVisit(pr.second);
				}
			}
			if(end) break;
		}
		int res = 0;
		for(int i=0;i<N;i++){
			if(visit[i] == 1) ++res;
		}
		cout << res << endl;
	}
}
