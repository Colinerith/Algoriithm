#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;

	double s = speeds[0];
	int tmp = ceil((100 - progresses[0]) / s);
	int cnt = 1;
	for (register int i = 1; i < progresses.size(); i++) {
		s = speeds[i];
		int k = ceil((100 - progresses[i]) / s);
		if (k > tmp) {
			answer.push_back(cnt);
			cnt = 1;
			tmp = k;
		}
		else {
			cnt++;
		}
	}
	answer.push_back(cnt);
	return answer;
}

int main() {
	//vector<int> p = { 95, 90, 99, 99, 80, 70 };
	//vector<int> s = { 1, 1, 1, 1, 1, 1 };
	vector<int> p = { 55, 6, 65 };
	vector<int> s = { 5, 10, 7 };

	vector<int> a = solution(p, s);
}
