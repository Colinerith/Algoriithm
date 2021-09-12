#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	int answer = n - lost.size();
	sort(reserve.begin(), reserve.end());
	sort(lost.begin(), lost.end());
	// 여벌만 남고 체육복 도난당한 경우 빌려줄 수 없음
	for (int j = 0; j < reserve.size(); j++) {
		for (int k = 0; k < lost.size(); k++) {
			if (lost[k] == reserve[j]) {
				answer++;
				lost.erase(lost.begin() + k);
				reserve.erase(reserve.begin() + j);
			}
		}
	}

	for (int j = 0; j < reserve.size(); j++) {
		for (int i = 0; i < lost.size(); i++) {
			if (lost[i] == reserve[j] || lost[i] == reserve[j] + 1 || lost[i] == reserve[j] - 1) {
				answer++;
				lost.erase(lost.begin() + i);
				break;
			}
		}
	}

	return answer;
}
