#include <string>
#include <vector>
#include<iostream>

using namespace std;
int a[5] = { 1,2,3,4,5 };
int b[8] = { 2,1,2,3,2,4,2,5 };
int c[10] = { 3,3,1,1,2,2,4,4,5,5 };

vector<int> solution(vector<int> answers) {
	vector<int> answer;
	int aCnt=0, bCnt=0, cCnt = 0;
	int ai=0, bi=0, ci = 0;
	for (int ans : answers) {
		if (a[ai++] == ans) aCnt++;
		if (b[bi++] == ans) bCnt++;
		if (c[ci++] == ans) cCnt++;
		ai %= 5; bi %= 8; ci %= 10;
	}
	if (aCnt >= bCnt && aCnt >= cCnt) {
		answer.push_back(1);
		if (aCnt == bCnt)
			answer.push_back(2);
		if (aCnt == cCnt)
			answer.push_back(3);
	}
	else if (bCnt >= aCnt && bCnt >= cCnt) {
		if (bCnt == aCnt)
			answer.push_back(1);
		answer.push_back(2);
		if (bCnt == cCnt)
			answer.push_back(3);
	}
	else if (cCnt >= aCnt && cCnt >= bCnt) {
		if (aCnt == cCnt)
			answer.push_back(1);
		if (bCnt == cCnt)
			answer.push_back(2);
		answer.push_back(3);
	}

	return answer;
}

int main() {
	vector<int> answers = { 1,3,2,4,2 };
	solution(answers);

}
