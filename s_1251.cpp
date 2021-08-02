// 그래프 #6: 하나로
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
#define INF 9223372036854775807

int T, test_case, n;
long long cost;
double e;
long long map[1000][1000];
pair<long long, long long> island[1000];
bool connected[1000];
vector<int> v;

void prim() {
	connected[0] = true;
	int connectedCnt = 1;
	v.push_back(0);
	
	while (connectedCnt < n) {
		int minIdx1 = -1;
		int minIdx2 = -1;
		long long int minCost = INF;
		for (int i : v) {
			for (int j = 1; j < n; j++) {
				if (map[i][j] < minCost && !connected[j]) {
					minCost = map[i][j];
					minIdx1 = i;
					minIdx2 = j;
				}
			}
		}
		connected[minIdx2] = true;
		cost += map[minIdx1][minIdx2];
		connectedCnt++;
		v.push_back(minIdx2);
	}
}

long long int dist(int i, long long x, long long y) {
	long long x2 = island[i].first;
	long long y2 = island[i].second;
	return (x2 - x)*(x2 - x) + (y2 - y)*(y2 - y);
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n;
		long long x, y;
		while (!v.empty())
			v.pop_back();
		for (int i = 0; i < n; i++)
			connected[i] = false;
		cost = 0;

		for (int i = 0; i < n; i++) {
			cin >> x;
			island[i].first = x;
		}
		for (int i = 0; i < n; i++) {
			cin >> y;
			island[i].second = y;
			for (int j = 0; j < i; j++) {
				long long distance = dist(j, island[i].first, y);
				map[j][i] = distance;
				map[i][j] = distance;
			}
		}
		cin >> e;

		prim();
		printf("#%d %.0lf\n", test_case, cost*e);
	}
	return 0;
}
