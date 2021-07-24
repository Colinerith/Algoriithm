#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<string>
using namespace std;

int T, cnt;
int test_case;
string num, maxNum;
queue<string> q;
bool flag;

void findMax() {
	priority_queue<char, vector<char>> pq;
	for (int i = 0; i < num.length(); i++)
		pq.push(num[i]);
	while (!pq.empty()) {
		maxNum += pq.top();
		pq.pop();
	}
}

int run() {
	for (int i = 0; i < num.length(); i++) {
		if (cnt == 0)
			return 0;
		string str = q.front();
		if (maxNum[i] == str[i]) // 바꾸지 않는게 최선이면
			continue;
		cnt--;

		int qSize = q.size();
		while (qSize--) {
			string str = q.front();
			q.pop();

			for (int j = i + 1; j < num.length(); j++) {
				if (str[j] == maxNum[i]) {
					string temp = str;
					char a = temp[i];
					temp[i] = temp[j];
					temp[j] = a;
					if (temp == maxNum) {
						flag = true;
						return cnt;
					}
					q.push(temp);
				}
			}
		}
	}
	return cnt; 
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		while (!q.empty())
			q.pop();
		maxNum = "";
		flag = false;

		cin >> num >> cnt;
		findMax();
		q.push(num);

		int left = run(); // 남은 교환 횟수
		
		if (left == 0 && !flag) {
			int maxPrize = 0; // 큐에 있는 것들 중 최대 찾기
			while (!q.empty()) {
				int t = stoi(q.front());
				q.pop();
				if (t > maxPrize)
					maxPrize = t;
			}
			printf("#%d %d\n", test_case, maxPrize);
		}
		else if (left & 1) { // 홀수
			// 홀수인데 같은수가 존재하면 짝수와 같음
			int len = num.length();
			bool sameFlag = false;
			for (int i = 0; i < len; i++) {
				for (int j = i + 1; j < len; j++) {
					if (num[i] == num[j])
						sameFlag = true;
				}
			}
			if (!sameFlag) {
				char a = maxNum[len - 1];
				maxNum[len - 1] = maxNum[len - 2];
				maxNum[len - 2] = a;
			}
			printf("#%d %d\n", test_case, stoi(maxNum));
		}
		else { // 짝수
			printf("#%d %d\n", test_case, stoi(maxNum));
		}
	}
	return 0;
}
