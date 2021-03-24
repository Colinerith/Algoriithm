//단지 번호 붙이기
/*
첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고,
그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.
첫 번째 줄에는 총 단지수를 출력하시오.
그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

int n, tmp;
string s;
bool graph[25][25];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
vector<int> num;
int tempnum;
int sum;

void dfs(int x, int y) {
	graph[x][y] = 0;
	tempnum++;
	for (int i = 0; i < 4; i++) {
		if ((x + dx[i]) >= 0 && (y + dy[i]) >= 0 && (x + dx[i]) < n && (y + dy[i]) < n && graph[x + dx[i]][y + dy[i]] == 1) {
			dfs(x + dx[i], y + dy[i]);
		}
	}
}
int main() {
	cin >> n;
	sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < n; j++) {
			graph[i][j] = s.at(j) - '0';
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == 1) {
				tempnum = 0;
				dfs(i, j);
				num.push_back(tempnum);
				sum++;
			}
		}
	}
	cout << sum << "\n";
	sort(num.begin(), num.end());
	for (int i:num) {
		cout << i << "\n";
	}
}
