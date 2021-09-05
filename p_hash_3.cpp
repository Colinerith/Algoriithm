#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

int solution(vector<vector<string>> clothes) {
	int answer = 0;
	unordered_map<string, int> m;
	for (int i = 0; i < clothes.size(); i++)
		m[clothes[i][1]]++;

	for (auto i : m)
		answer = answer + i.second + answer * i.second;

	return answer;
}

int main() {
	vector<vector<string>> clothes =
			{{"yellowhat", "headgear"},
			{"bluesunglasses", "eyewear"},
			{ "green_turban", "headgear" }};
	cout << solution(clothes);
}
