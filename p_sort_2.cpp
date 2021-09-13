#include <string>
#include <vector>
#include<algorithm>

using namespace std;
string solution(vector<int> numbers) {
	vector<pair<string, int>> v;
	for (int i = 0; i < numbers.size(); i++) {
		string str = to_string(numbers[i]);
		int len = str.length();
		int idx = 0;
		for (int j = 0; j < 4 - len; j++) {
			str += str[(idx++)%len];
		}
		v.push_back({ str, len });
	}
	sort(v.begin(), v.end(), greater<>());

	string answer = "";
	for (int i = 0; i < v.size(); i++) {
		answer += v[i].first.substr(0, v[i].second);
	}
	int i = 0;
	for (i; i < answer.size(); i++) {
		if (answer[i] != '0') break;
	}
	if (i == answer.size()) return "0";
	return answer;
}

int main() {
	solution({ 12, 121 });
}
