#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int time = 0;
	queue<pair<int, int>> onTheBridge;
	int idx = 0;
	int tempWeight = weight;
	while (true) {
		time++;
		if (!onTheBridge.empty() && time - onTheBridge.front().second == bridge_length) {
			tempWeight += onTheBridge.front().first;
			onTheBridge.pop();
			if (idx == truck_weights.size() && onTheBridge.empty())
				return time;
		}
		if (idx < truck_weights.size() && tempWeight >= truck_weights[idx]) {
			onTheBridge.push({ truck_weights[idx],time });
			tempWeight -= truck_weights[idx];
			idx++;
		}
	}
	return time;
}

int main() {
	solution(100, 100, { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 });
}
